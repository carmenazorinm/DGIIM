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
import java.util.Stack;
import java.util.TreeSet;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import serialization.Vector2d;
import tools.ElapsedCpuTimer;

public class AgenteAStar extends AbstractPlayer {
	public static int MAX_ANCHO; // ancho del grid para calcular la clave del nodo
	Vector2d fescala; 
	Stack<ACTIONS> pila_acciones; // pila acciones desde el inicial al portal
	boolean ruta_calculada; // al principio, no está calculada (FALSE)
	int[][] mapa; // mapa que guarda los muros grises, marrones y azules y los pinchos
	tools.Vector2d portal; // posición del portal
	int nodos_expandidos; // al principio, 0
	Set<Integer> capasAzules; // guarda las posiciones de las capas azules iniciales
	Set<Integer> capasRojas; // guarda las posiciones de las capas rojas iniciales
	long tInit; // para calcular runtime
	long tFin; // para calcular runtime
	
	
	public AgenteAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		ArrayList<Observation>[][] grid = stateObs.getObservationGrid(); // para evitar llamadas repetidas
		Dimension world = stateObs.getWorldDimension(); // para evitar llamadas repetidas
		MAX_ANCHO = grid[0].length;
		Nodo.MAX_ANCHO =MAX_ANCHO; // porque el nodo necesita el ancho del mapa para calcular su clave
		fescala = new Vector2d(world.width / grid.length,  world.height / grid[0].length);
		pila_acciones = new Stack<>();
		ruta_calculada = false;

		mapa = new int[grid.length][grid[0].length];
		Arrays.stream(mapa).forEach(row -> Arrays.fill(row, 7)); // Inicializa todo a 7 en una línea
		
		// rellenamos el mapa. Para eso usamos los itype de los immovable
				/*
				 * 7 -> cesped, se puede pasar sin problema
				 * 0 -> muro gris
				 * 1 -> muro azul
				 * 2 -> muro marrón
				 * 4 -> pinchos
		*/
		Map<Integer, Integer> tipoMapa = Map.of(5, 0, 7, 1, 6, 2, 3, 4);
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for (int i = 0; i < immovable.length; i++) {
		    ArrayList<Observation> list = immovable[i];
		    for (int j = 0; j < list.size(); j++) {
		        Observation obs = list.get(j);
		        int x = (int)(obs.position.x /fescala.x);
		        int y = (int)(obs.position.y /fescala.y);
		        Integer nuevoValor = tipoMapa.get(obs.itype);
		        if (nuevoValor != null) {
		            mapa[x][y] = nuevoValor;
		        }
		    }
		}
		
		// guardamos las capas azules y rojas iniciales
		// como tenemos el ancho del mapa, podemos calcular las posiciones como x*MAX_ANCHO+y 
		// y asegura biyectividad entre posicion y dicho valor
		capasAzules = new HashSet<>();
		capasRojas = new HashSet<>();
		ArrayList<Observation>[] recursos = stateObs.getResourcesPositions();
		if (recursos != null) {
		    for (ArrayList<Observation> resourceList : recursos) {
		        for (Observation obs : resourceList) {
		            int x = (int)(obs.position.x/fescala.x);
		            int y = (int)(obs.position.y/fescala.y);
		            
		            if (obs.itype == 8) { // Capa roja
		                capasRojas.add(x*MAX_ANCHO+y); 
		            } else if (obs.itype == 9) { // Capa azul
		                capasAzules.add(x*MAX_ANCHO+y);
		            }
		        }
		    }
		}
		
		
		// guardamos posición del portal
		ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions();
		portal = posiciones[0].get(0).position;
		portal.x = (int)(portal.x /fescala.x); 
		portal.y = (int)(portal.y/fescala.y);
		
		nodos_expandidos = 0;
	}
	
	// método optimizado por Chatgpt. Calculamos los vecinos según la capa del nodo actual
	// y el muro en la dirección que quiera traspasar. También evitamos que se creen vecinos
	// que se salen del mapa.
	private List<Nodo> getVecinos(StateObservation stateObs, Nodo nodo) {
	    List<Nodo> vecinos = new ArrayList<>(4); // Capacidad fija para 4 direcciones
	    int x = (int)nodo.x;
	    int y = (int)nodo.y;

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
				pila_acciones.add(accion);
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
		Nodo nodo_actual = new Nodo((int)(posicion.x / fescala.x), 
				(int)(posicion.y / fescala.y), ACTIONS.ACTION_NIL, null);
		nodo_actual.capasAzules = capasAzules;
		nodo_actual.capasRojas = capasRojas;
		nodo_actual.h = distanciaManhattan(nodo_actual);
		nodo_actual.g = 0;
		return nodo_actual;
	}
	
	// Heurística del A*
	private int distanciaManhattan(Nodo n) {
		return (int) (Math.abs(n.x - portal.x) + Math.abs(n.y - portal.y));
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// si la ruta ya se ha calculado, solo buscamos la siguiente posición
	    if (ruta_calculada) {
	        return pila_acciones.pop();
	    // si la ruta no se ha calculado, es porque acaba de empezar y ha que rellenar el array acciones
	    } else {
	    	tInit = System.nanoTime();
	        Set<Nodo> cerrados = new HashSet<>();
	        PriorityQueue<Nodo> abiertos = new PriorityQueue<>();
	        Nodo nodo_actual = inicializarNodo(stateObs);
	        
	        abiertos.add(nodo_actual);

	        while (!abiertos.isEmpty()) {
	            aumentarAntiguedad(abiertos); // llevamos la cuenta de cuantas iteraciones lleva cada nodo
	            nodo_actual = abiertos.poll(); // saca el nodo con menor valor y lo elimina de abiertos

	            nodos_expandidos++;
	            // ¿Es el objetivo?
	            if (nodo_actual.x == portal.x && nodo_actual.y == portal.y) {
	                calcularRuta(nodo_actual);
	                ruta_calculada = true;
	                tFin = System.nanoTime();
	                System.out.println("Nodos expandidos: " + nodos_expandidos);
	                System.out.println("Tamaño ruta: " + pila_acciones.size());
	                System.out.println("Tiempo ejecucion: "+ (tFin - tInit)/1000000);
	                System.out.println("Abiertos/Cerrados: " + abiertos.size() + " / " + cerrados.size());
	                return pila_acciones.pop();
	            }

	            cerrados.add(nodo_actual);
	            
	            for (Nodo sucesor : getVecinos(stateObs, nodo_actual)) {	            	
	                // Calcular coste temporal para este camino
	                float nuevoG = nodo_actual.g + 1;
                	float antiguoG = Float.MAX_VALUE; // el g del sucesor en cerrados

	                // Si ya está en cerrados pero encontramos un mejor camino
	                if (cerrados.contains(sucesor)) {
	                	for (Nodo obj : cerrados) { // calculamos la g del sucesor guardado en cerrados
	                        if (obj.equals(sucesor))
	                        	antiguoG = obj.g;
	                        continue;
	                    }
	                    if (nuevoG < antiguoG) { // comparamos la g del sucesor en cerrados y del sucesor recién creado
	                        cerrados.remove(sucesor);
	                        sucesor.g = nuevoG;
	                        sucesor.h = distanciaManhattan(sucesor);
	                        abiertos.add(sucesor);
	                    }
	                    continue;
	                }
	                
	                // Si no está en abiertos ni en cerrados
	                if (!abiertos.contains(sucesor) && !cerrados.contains(sucesor)) {
	                    sucesor.g = nuevoG;
	                    sucesor.h = distanciaManhattan(sucesor);
	                    abiertos.add(sucesor);
	                } 
	                
	                // Si ya está en abiertos pero encontramos un mejor camino -> como el coste de movimeinto es
	                // constante (siempre 1) y la cola de prioridad actualiza automáticamente las prioridades,
	                // nunca entrará en este if y podemos mejorar la eficiencia
//	                else if (abiertos.contains(sucesor)) {
//	                	for (Nodo obj : abiertos) {
//	                        if (obj.equals(sucesor))
//	                        	antiguoG = obj.g;
//	                        continue;
//	                    }
//	                	if(nuevoG < antiguoG) {
//	                		abiertos.remove(sucesor);
//		                    sucesor.g = nuevoG;
//		                    sucesor.h = distanciaManhattan(sucesor);
//		                    abiertos.add(sucesor);
//	                	}
//	                }
	            }
	        }
	    }

	    return ACTIONS.ACTION_NIL;
	}

	
}