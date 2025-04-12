package tracks.singlePlayer.evaluacion.src_AZORIN_MARTI_CARMEN;

import java.awt.Dimension;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.TreeSet;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import serialization.Vector2d;
import tools.ElapsedCpuTimer;

public class AgenteDijkstra extends AbstractPlayer {
	public static int MAX_ANCHO; // ancho del mapa
	Vector2d fescala; 
	ArrayList<ACTIONS> acciones; // array de las acciones desde el inicio al portal
	boolean ruta_calculada; // al principio, no está calculada (FALSE)
	int[][] mapa; // guarda los muros grises, marrones y azules y los pinchos
	tools.Vector2d portal; // posición del portal
	int nodos_expandidos; // al principio, 0
	int pos_siguiente_accion; // para seguir el array de acciones
	Set<Integer> capasAzules; // guarda las posiciones iniciales de todas las capas azules
	Set<Integer> capasRojas; // guarda las posiciones iniciales de todas las capas rojas
	long tInit; // para calcular el tiempo de ejecución
	long tFin; // para calcular el tiempo de ejecución
	
	// Constructor del Dijkstra
	public AgenteDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		ArrayList<Observation>[][] grid = stateObs.getObservationGrid(); // para evitar llamadas repetidas
		Dimension world = stateObs.getWorldDimension(); // para evitar llamadas repetidas
		
		MAX_ANCHO = grid[0].length;
		Nodo.MAX_ANCHO =MAX_ANCHO; // para calcular la clave de las capas de los nodos
		fescala = new Vector2d(world.width / grid.length, world.height / grid[0].length);
		acciones = new ArrayList<ACTIONS>();
		ruta_calculada = false;

		// rellenamos el mapa. Para eso usamos los itype de los immovable
		/*
		 * 7 -> cesped, se puede pasar sin problema
		 * 0 -> muro gris
		 * 1 -> muro azul
		 * 2 -> muro marrón
		 * 4 -> pinchos
		 */
		mapa = new int[grid.length][grid[0].length];
		Arrays.stream(mapa).forEach(row -> Arrays.fill(row, 7)); // Inicializa todo a 7 en una línea
		
	    Map<Integer, Integer> tipoMapa = Map.of(5, 0, 7, 1, 6, 2, 3, 4);
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for (int i = 0; i < immovable.length; i++) {
		    ArrayList<Observation> list = immovable[i];
		    for (int j = 0; j < list.size(); j++) {
		        Observation obs = list.get(j);
		        int x = (int)(obs.position.x/fescala.x);
		        int y = (int)(obs.position.y /fescala.y);
		        Integer nuevoValor = tipoMapa.get(obs.itype);
		        if (nuevoValor != null) {
		            mapa[x][y] = nuevoValor;
		        }
		    }
		}

		// inicializamos los sets que contendran las posiciones de las capas azules y rojas originales
		// como tenemos el ancho del mapa, podemos calcular las posiciones como x*MAX_ANCHO+y 
		// y asegura biyectividad entre posicion y dicho valor
		capasAzules = new HashSet<>();
		capasRojas = new HashSet<>();
		ArrayList<Observation>[] recursos = stateObs.getResourcesPositions();
		if (recursos != null) {
		    for (ArrayList<Observation> resourceList : recursos) {
		        for (Observation obs : resourceList) {
		            int x = (int)(obs.position.x / fescala.x);
		            int y = (int)(obs.position.y / fescala.y);
		            
		            if (obs.itype == 8) { // Capa roja
		                //mapa[x][y] = 5;
		                capasRojas.add(x*MAX_ANCHO+y);
		            } else if (obs.itype == 9) { // Capa azul
		                //mapa[x][y] = 6;
		                capasAzules.add(x*MAX_ANCHO+y);
		            }

		        }
		    }
		}
		
		// posicion del portal
		ArrayList<Observation> posiciones = stateObs.getPortalsPositions()[0];
		portal = posiciones.get(0).position;
		portal.x = (int)(portal.x /fescala.x);
		portal.y = (int)(portal.y /fescala.y);

		nodos_expandidos = 0;
		pos_siguiente_accion = 0;
	}
	
	// método optimizado por Chatgpt. Calculamos los vecinos según la capa del nodo actual
	// y el muro en la dirección que quiera traspasar. También evitamos que se creen vecinos
	// que se salen del mapa.
	private List<Nodo> getVecinos(StateObservation stateObs, Nodo nodo) {
	    List<Nodo> vecinos = new ArrayList<>(4); // Capacidad fija para 4 direcciones
	    int x = nodo.x;
	    int y = nodo.y;

	    // Derecha (x+1)
	    if (x + 1 < mapa.length && esMovimientoValido(mapa[x+1][y], nodo)) {
	        vecinos.add(new Nodo(x+1, y, ACTIONS.ACTION_RIGHT, nodo));
	    }
	    
	    // Izquierda (x-1)
	    if (x - 1 >= 0 && esMovimientoValido(mapa[x-1][y], nodo)) {
	        vecinos.add(new Nodo(x-1, y, ACTIONS.ACTION_LEFT, nodo));
	    }
	    
	    // Arriba (y-1)
	    if (y - 1 >= 0 && esMovimientoValido(mapa[x][y-1], nodo)) {
	        vecinos.add(new Nodo(x, y-1, ACTIONS.ACTION_UP, nodo));
	    }
	    
	    // Abajo (y+1)
	    if (y + 1 < mapa[0].length && esMovimientoValido(mapa[x][y+1], nodo)) {
	        vecinos.add(new Nodo(x, y+1, ACTIONS.ACTION_DOWN, nodo));
	    }
	    
	    return vecinos;
	}

	private boolean esMovimientoValido(int tipoCelda, Nodo actual) {
	    // 0: Pared sólida | 4: Obstáculo (no transitable)
	    if (tipoCelda == 0 || tipoCelda == 4) return false;
	    
	    // 1: Pared azul (requiere capa azul)
	    if (tipoCelda == 1 && !actual.capa_azul) return false;
	    
	    // 2: Pared roja (requiere capa roja)
	    if (tipoCelda == 2 && !actual.capa_roja) return false;
	    
	    return true;
	}
	
	/*
	 * Cada nodo guarda su padre y la accion que ha usado el padre para llegar al hijo.
	 * Se pasa como parámetro el último nodo que se visita, cuya posición coincide con el portal.
	 */
	private void calcularRuta(Nodo n) {
		Nodo actual = n;
		
		ACTIONS accion;
		while(actual != null) {
			accion = actual.accion;
			if(accion != ACTIONS.ACTION_NIL) {
				acciones.add(0,  accion);
			}
			actual = actual.padre;
		}
	}
	
	/*
	 * Llevamos la cuenta de cuantas iteraciones lleva cada nodo en la cola
	 */
	private void aumentarAntiguedad(PriorityQueue<Nodo> a) {
		for (Nodo n: a) {	
			n.antiguedad++;
		}
	}
	
	/*
	 * Inicializamos el primer nodo desde el que se empieza. Las capas que tiene son las 
	 * del mapa original, ya que todavía no se ha movido. En Dijkstra la heurística es 0
	 * para todos los nodos. El coste g es 0, porque se empieza desde esta posición.
	 */
	private Nodo inicializarNodo(StateObservation stateObs) {
		tools.Vector2d posicion = stateObs.getAvatarPosition();
		Nodo nodo_actual = new Nodo((int)(posicion.x / fescala.x), (int)(posicion.y / fescala.y), ACTIONS.ACTION_NIL, null);
		nodo_actual.capasAzules = capasAzules;
		nodo_actual.capasRojas = capasRojas;
		nodo_actual.g = 0;
		return nodo_actual;
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// cuando la ruta está calculada, solo tenemos que sacar la siguiente posición
	    if (ruta_calculada) {
	        pos_siguiente_accion++;
	        return acciones.get(pos_siguiente_accion);
	        
	    // si no se ha calculado la ruta, es que es la primera iteración y hay que calcularla.
	    } else {
	    	tInit = System.nanoTime();
	        Set<Nodo> visitados = new HashSet<>();
	        PriorityQueue<Nodo> nodos_por_visitar = new PriorityQueue<>();
	        Nodo nodo_actual = inicializarNodo(stateObs);

	        nodos_por_visitar.add(nodo_actual); // al principio, el nodo_actual es donde empieza
	        
	        while (!nodos_por_visitar.isEmpty()) {
	        	aumentarAntiguedad(nodos_por_visitar);
	            nodo_actual = nodos_por_visitar.poll(); // sacamos el nodo con menor valor y lo elimina

	            // Si ya lo visitamos, lo saltamos
	            if (visitados.contains(nodo_actual) || nodo_actual == null) continue;
	            
	            nodos_expandidos++;

	            // ¿Es el objetivo?
	            if (nodo_actual.x == portal.x && nodo_actual.y == portal.y) {
	            	
	                calcularRuta(nodo_actual);
	                ruta_calculada = true;
	                tFin = System.nanoTime();
	                System.out.println("Nodos expandidos: " + nodos_expandidos);
	                System.out.println("Tamaño ruta: " + acciones.size());
	                System.out.println("Tiempo ejecucion: "+ (tFin - tInit)/1000000);
	                return acciones.get(pos_siguiente_accion);
	            }

	            visitados.add(nodo_actual);
	            
	            for (Nodo sucesor : getVecinos(stateObs, nodo_actual)) {
	                if (!visitados.contains(sucesor)) {
	                    float nuevoG = nodo_actual.g + 1;
	                    if (nuevoG < sucesor.g) {
	                    	//nodos_por_visitar.remove(sucesor); // no hace falta porque la priority queue los ordena automáticamente
	                        sucesor.g = nuevoG;
	                        sucesor.padre = nodo_actual;
	                        nodos_por_visitar.add(sucesor);
	                    }
	                }
	            }
	        }
	        
	    }

	    return ACTIONS.ACTION_NIL;
	}

	
}