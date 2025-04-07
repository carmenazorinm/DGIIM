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
		
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for(int i = 0; i < immovable.length; i++) {
			for (int j = 0; j < immovable[i].size(); j++) {
				Observation obs = immovable[i].get(j);
				int x = (int) Math.floor(obs.position.x / fescala.x );
				int y = (int) Math.floor(obs.position.y / fescala.y );
		        // System.out.println("Inmovable iType: " + obs.itype + " at grid (" + x + "," + y + ")");
				switch(obs.itype) {
		            case 5: mapa[x][y] = 0; break;  // Muro gris
		            case 7: mapa[x][y] = 1; break;  // Muro azul
		            case 6: mapa[x][y] = 2; break;  // Muro marrón
		            case 3: mapa[x][y] = 4; break;  // Pinchos
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
		
//		for(int i = 0; i < mapa.length; i++) {
//			for(int j = 0; j < mapa[0].length; j++) {
//				System.out.print("["+ mapa[i][j] + "]");
//			}
//			System.out.println();
//		}
		
		
		ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions();
		portal = posiciones[0].get(0).position;
		portal.x = (int)(portal.x / fescala.x); // Cast directo en lugar de Math.floor
		portal.y = (int)(portal.y / fescala.y);
		
		nodos_expandidos = 0;
		pos_siguiente_accion = 0;
	}
	
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
	
	private void aumentarAntiguedad(TreeSet<Nodo> a) {
		for (Nodo n: a) {
			n.antiguedad++;
		}
	}
	
	private String calcularClave(Nodo nodo) {
		return String.format("%d,%d,%b,%b,%s,%s", 
			    (int)nodo.x, (int)nodo.y, 
			    nodo.capa_azul, nodo.capa_roja,
			    nodo.capasAzules.toString(), 
			    nodo.capasRojas.toString()
			);
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
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// en el primer paso, se calcula la ruta
		if(ruta_calculada) {
			pos_siguiente_accion++;
			return acciones.get(pos_siguiente_accion);
		} else {
			Set<Nodo> visitados = new HashSet<>();
			PriorityQueue<Nodo> nodos_por_visitar = new PriorityQueue<>();
			Nodo nodo_actual = new Nodo(stateObs.getAvatarPosition().x / fescala.x, 
					stateObs.getAvatarPosition().y / fescala.y, ACTIONS.ACTION_NIL, null);
			nodo_actual.capasAzules = capasAzules;
			nodo_actual.capasRojas = capasRojas;
			nodo_actual.g = 0;
			nodos_por_visitar.add(nodo_actual); // nodos_por_visitar = A, 
			
			while(nodos_por_visitar.size() > 0) {
				// escogemos el siguiente nodo a visitar
				// aumentarAntiguedad(nodos_por_visitar);
				nodo_actual = nodos_por_visitar.poll();
				
				//nodos_por_visitar.remove(nodo_actual);
				nodos_expandidos++;
				if(nodo_actual.x == portal.x && nodo_actual.y == portal.y) {
					// System.out.println("Ruta calculada");
					calcularRuta(nodo_actual);
					ruta_calculada = true;
					System.out.println("Nodos expandidos: " + nodos_expandidos);
					return acciones.get(pos_siguiente_accion);
				} 
				visitados.add(nodo_actual);
				for (Nodo sucesor: getVecinos(stateObs, nodo_actual)) {
					if (!visitados.contains(sucesor) && sucesor.g > nodo_actual.g + 1) {
						if(nodos_por_visitar.contains(sucesor)) {
							nodos_por_visitar.remove(sucesor);
						}
						nodos_por_visitar.add(sucesor);
						sucesor.g = nodo_actual.g + 1;
						sucesor.padre = nodo_actual;
					}
				}
				
			}
		}
		
		return ACTIONS.ACTION_NIL;
	}
	
	private int prioridadAccion(ACTIONS a, ACTIONS b) {
        // Derecha > Izquierda > Arriba > Abajo
        if (a == ACTIONS.ACTION_RIGHT && b != ACTIONS.ACTION_RIGHT) return -1;
        if (b == ACTIONS.ACTION_RIGHT && a != ACTIONS.ACTION_RIGHT) return 1;
        if (a == ACTIONS.ACTION_LEFT && b != ACTIONS.ACTION_LEFT) return -1;
        if (b == ACTIONS.ACTION_LEFT && a != ACTIONS.ACTION_LEFT) return 1;
        if (a == ACTIONS.ACTION_UP && b != ACTIONS.ACTION_UP) return -1;
        if (b == ACTIONS.ACTION_UP && a != ACTIONS.ACTION_UP) return 1;
        if (a == ACTIONS.ACTION_DOWN && b != ACTIONS.ACTION_DOWN) return -1;
        return 1;
    }
	
}
