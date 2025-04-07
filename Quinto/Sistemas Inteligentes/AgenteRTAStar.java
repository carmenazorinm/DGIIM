package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import serialization.Vector2d;
import tools.ElapsedCpuTimer;

public class AgenteRTAStar extends AbstractPlayer{
	Vector2d fescala;
	Nodo actual;
	int[][] mapa;
	tools.Vector2d portal;
	int nodos_expandidos;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasAzules;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasRojas;
	private HashMap<String, Float> tablaHeuristica = new HashMap<>();
	
	
	public AgenteRTAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length, 
				stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
		nodos_expandidos = 0;
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
		
		ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions();
		portal = posiciones[0].get(0).position;
		portal.x = (int)(portal.x / fescala.x); // Cast directo en lugar de Math.floor
		portal.y = (int)(portal.y / fescala.y);
		
		inicializarHeuristicas(stateObs);
		
		
		actual = new Nodo((int)(stateObs.getAvatarPosition().x / fescala.x),
                (int)(stateObs.getAvatarPosition().y / fescala.y),
                ACTIONS.ACTION_NIL, null);
//		AbstractMap.SimpleEntry<Integer, Integer>pos = new AbstractMap.SimpleEntry<>((int)actual.x, (int)actual.y);
//		if(capasAzules.remove(pos)) {
//			actual.capa_azul = true;
//			actual.capa_roja = false;
//		} else if(capasRojas.remove(pos)) {
//			actual.capa_roja = true;
//			actual.capa_azul = false;
//		}
		actual.capasAzules = new HashSet<>(capasAzules);
		actual.capasRojas = new HashSet<>(capasRojas);
	}
	
	private List<Nodo> getVecinos(StateObservation stateObs, Nodo nodo) {
	    List<Nodo> vecinos = new ArrayList<>(4); // Capacidad fija para 4 direcciones
	    int x = (int)nodo.x;
	    int y = (int)nodo.y;

	    if (x + 1 < mapa.length) {
	    	Nodo vecino = new Nodo(x+1, y, ACTIONS.ACTION_RIGHT, nodo);
	    	if(esMovimientoValido(mapa[x+1][y], nodo))
	    		vecinos.add(vecino);
	    }
	    
	    if (x - 1 >= 0) {
	        Nodo vecino = new Nodo(x-1, y, ACTIONS.ACTION_LEFT, nodo);
	    	if(esMovimientoValido(mapa[x-1][y], nodo))
	    		vecinos.add(vecino);
	    }
	    
	    if (y - 1 >= 0) {
	        Nodo vecino = new Nodo(x, y-1, ACTIONS.ACTION_UP, nodo);
	    	if(esMovimientoValido(mapa[x][y-1], nodo))
	    		vecinos.add(vecino);
	    }
	    
	    if (y + 1 < mapa[0].length) {
	        Nodo vecino = new Nodo(x, y+1, ACTIONS.ACTION_DOWN, nodo);
	    	if(esMovimientoValido(mapa[x][y+1], nodo))
	    		vecinos.add(vecino);
	    }
	    
	    return vecinos;
	}

	private boolean esMovimientoValido(int tipoCelda, Nodo actual) {
	    // 0: Pared sólida | 4: Obstáculo (no transitable)
	    if (tipoCelda == 0 || tipoCelda == 4) return false;
	    
	    // 1: Pared azul (requiere capa azul)
	    else if (tipoCelda == 1 && !actual.capa_azul) return false;
	    
	    // 2: Pared roja (requiere capa roja)
	    else if (tipoCelda == 2 && !actual.capa_roja) return false;
	    
	    return true;
	}
	
	private String generarClave(Nodo n) {
	    return String.format("%d,%d,%b,%b", (int)n.x, (int)n.y,n.capa_azul, n.capa_roja);
	}
	
	private String generarClave(int x, int y, boolean capaAzul, boolean capaRoja) {
	    return String.format("%d,%d,%b,%b", x, y, capaAzul,capaRoja);
	}
	
	private void inicializarHeuristicas(StateObservation stateObs) {
	    // Inicializar todas las heuristicas con distancia Manhattan
	    for (int x = 0; x < mapa.length; x++) {
	        for (int y = 0; y < mapa[0].length; y++) {
	        	float h = (float) (Math.abs(x - portal.x) + Math.abs(y - portal.y));
	        	if(mapa[x][y] == 0 || mapa[x][y] == 4) {
	        		tablaHeuristica.put(generarClave(x, y, false, false), Float.MAX_VALUE);
	        		tablaHeuristica.put(generarClave(x, y, true, false), Float.MAX_VALUE);
	        		tablaHeuristica.put(generarClave(x, y, false, true), Float.MAX_VALUE);
	        	} if (mapa[x][y] == 1) {
	        		tablaHeuristica.put(generarClave(x, y, true, false), h);
	        		tablaHeuristica.put(generarClave(x, y, false, false), Float.MAX_VALUE);
	        		tablaHeuristica.put(generarClave(x, y, false, true), Float.MAX_VALUE);
	        	} else if(mapa[x][y] == 2) {
	        		tablaHeuristica.put(generarClave(x, y, false, true), h);
	        		tablaHeuristica.put(generarClave(x, y, false, false), Float.MAX_VALUE);
	        		tablaHeuristica.put(generarClave(x, y, true, false), Float.MAX_VALUE);
	        	}else {
		            tablaHeuristica.put(generarClave(x, y, false, false), h);
		            tablaHeuristica.put(generarClave(x, y, true, false), h);
		            tablaHeuristica.put(generarClave(x, y, false, true), h);
	        	}
	        	
	        }
	    }
	}
	
	
	private float obtenerHeuristica(Nodo n) {
	    String clave = generarClave(n);
	    return tablaHeuristica.get(clave);
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
	    // 2. Actualizar las capas
		AbstractMap.SimpleEntry<Integer, Integer>pos = new AbstractMap.SimpleEntry<>((int)actual.x, (int)actual.y);
		capasAzules.remove(pos);
		capasRojas.remove(pos);
//		if (capasAzules.contains(pos)) {
//		    actual.capa_azul = true;
//		    actual.capa_roja = false;
//		    actual.capasAzules.remove(pos);
//		}
//		if (capasRojas.contains(pos)) {
//		    actual.capa_roja = true;
//		    actual.capa_azul = false;
//		    actual.capasRojas.remove(pos);
//		}


	    // 3. Verificación de objetivo
		nodos_expandidos++;

	    // 4. Espacio local de búsqueda (vecinos)
	    List<Nodo> vecinos = getVecinos(stateObs, actual);

	    // 5. Estrategia de movimiento: calcular f(y) = h(y) + c(actual,y)
	    Nodo mejorVecino = null;
	    float mejorValor = Float.MAX_VALUE;
	    float segundoMejor = Float.MAX_VALUE;

	    for (Nodo vecino : vecinos) {
	        float coste = 1; // c(actual,vecino) - asumimos coste uniforme 1
	        float h = obtenerHeuristica(vecino);
	        float f = coste + h;

	        // Actualizar mejor y segundo mejor
	        if (f < mejorValor) {
	            segundoMejor = mejorValor;
	            mejorValor = f;
	            mejorVecino = vecino;
	        } else if (f < segundoMejor) {
	            segundoMejor = f;
	        }
	    }

	    // 6. Regla de aprendizaje (actualizar heurística del nodo actual)
	    
	    if (segundoMejor != Float.MAX_VALUE) {
    		tablaHeuristica.put(generarClave(actual), Math.max(
    	            obtenerHeuristica(actual),
    	            segundoMejor
    	        ));
	    } else {	    	
	    	tablaHeuristica.put(generarClave(actual), Math.max(
		            obtenerHeuristica(actual),
		            mejorValor
		        ));
	    }

	    // 7. Devolver acción correspondiente al mejor vecino
	    actual = mejorVecino;
	    if (actual.x == portal.x && actual.y == portal.y) {
	        System.out.println("Nodos expandidos: " + nodos_expandidos); // Llegamos al objetivo
	    }
	    return mejorVecino != null ? mejorVecino.accion : ACTIONS.ACTION_NIL;
	}

}
