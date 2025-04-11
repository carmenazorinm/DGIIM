package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

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
	Vector2d fescala;
	ArrayList<ACTIONS> acciones;
	boolean ruta_calculada;
	int[][] mapa;
	tools.Vector2d portal;
	int nodos_expandidos;
	int pos_siguiente_accion;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasAzules;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasRojas;
	
	
	public AgenteDijkstra(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length, 
				stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
		acciones = new ArrayList<ACTIONS>();
		ruta_calculada = false;

		mapa = new int[stateObs.getObservationGrid().length][stateObs.getObservationGrid()[0].length];
		Arrays.stream(mapa).forEach(row -> Arrays.fill(row, 7)); // Inicializa todo a 7 en una línea
		
    Map<Integer, Integer> tipoMapa = Map.of(5, 0, 7, 1, 6, 2, 3, 4);
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for (int i = 0; i < immovable.length; i++) {
		    ArrayList<Observation> list = immovable[i];
		    for (int j = 0; j < list.size(); j++) {
		        Observation obs = list.get(j);
		        int x = (int)(obs.position.x * inv_escala_x);
		        int y = (int)(obs.position.y * inv_escala_y);
		        Integer nuevoValor = tipoMapa.get(obs.itype);
		        if (nuevoValor != null) {
		            mapa[x][y] = nuevoValor;
		        }
		    }
		}


		capasAzules = new HashSet<>();
		capasRojas = new HashSet<>();
		ArrayList<Observation>[] recursos = stateObs.getResourcesPositions();
		if (recursos != null) {
		    for (ArrayList<Observation> resourceList : recursos) {
		        for (Observation obs : resourceList) {
		            int x = (int)(obs.position.x / fescala.x);
		            int y = (int)(obs.position.y / fescala.y);
		            
		            if (obs.itype == 8) { // Capa roja
		                mapa[x][y] = 5;
		                capasRojas.add(new AbstractMap.SimpleEntry<>(x, y));
		            } else if (obs.itype == 9) { // Capa azul
		                mapa[x][y] = 6;
		                capasAzules.add(new AbstractMap.SimpleEntry<>(x, y));
		            }

		        }
		    }
		}

		ArrayList<Observation> posiciones = stateObs.getPortalsPositions()[0];
		portal = posiciones.get(0).position;
		portal.x = (int)(portal.x * inv_escala_x);
		portal.y = (int)(portal.y * inv_escala_y);

		nodos_expandidos = 0;
		pos_siguiente_accion = 0;


	}
	
	private List<Nodo> getVecinos(StateObservation stateObs, Nodo nodo) {
	    List<Nodo> vecinos = new ArrayList<>(4); // Capacidad fija para 4 direcciones
	    int x = nodo.x;
	    int y = nodo.y;

	    // Derecha (x+1)
	    if (x + 1 < ancho_mapa && esMovimientoValido(mapa[x+1][y], nodo)) {
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
	    if (y + 1 < alto_mapa && esMovimientoValido(mapa[x][y+1], nodo)) {
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
	
	private void aumentarAntiguedad(PriorityQueue<Nodo> a) {
		for (Nodo n: a) {	
			n.antiguedad++;
		}
	}
	
	private Nodo inicializarNodo(StateObservation stateObs) {
		tools.Vector2d posicion = stateObs.getAvatarPosition();
		Nodo nodo_actual = new Nodo((int)(posicion.x / fescala.x), 
				(int)(posicion.y / fescala.y), ACTIONS.ACTION_NIL, null);
		nodo_actual.capasAzules = capasAzules;
		nodo_actual.capasRojas = capasRojas;
		nodo_actual.g = 0;
		return nodo_actual;
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
	    if (ruta_calculada) {
	        pos_siguiente_accion++;
	        return acciones.get(pos_siguiente_accion);
	    } else {
	        Set<Nodo> visitados = new HashSet<>();
	        PriorityQueue<Nodo> nodos_por_visitar = new PriorityQueue<>();
	        Nodo nodo_actual = inicializarNodo(stateObs);

	        nodos_por_visitar.add(nodo_actual);
	        
	        while (!nodos_por_visitar.isEmpty()) {
	        	aumentarAntiguedad(nodos_por_visitar);
	            nodo_actual = nodos_por_visitar.poll();

	            // Si ya lo visitamos, lo saltamos
	            if (visitados.contains(nodo_actual) || nodo_actual == null) continue;
	            
	            nodos_expandidos++;

	            // ¿Es el objetivo?
	            if (nodo_actual.x == portal.x && nodo_actual.y == portal.y) {
	            	
	                calcularRuta(nodo_actual);
	                ruta_calculada = true;
	                System.out.println("Nodos expandidos: " + nodos_expandidos);
	                System.out.println("Tamaño ruta: " + acciones.size());
	                return acciones.get(pos_siguiente_accion);
	            }

	            visitados.add(nodo_actual);
	            
	            for (Nodo sucesor : getVecinos(stateObs, nodo_actual)) {
	                if (!visitados.contains(sucesor)) {
	                    float nuevoG = nodo_actual.g + 1;
	                    if (nuevoG < sucesor.g) {
	                    	//nodos_por_visitar.remove(sucesor);
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
