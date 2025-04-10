package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

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

public class AgenteAStar extends AbstractPlayer {
	Vector2d fescala;
	ArrayList<ACTIONS> acciones;
	boolean ruta_calculada;
	int[][] mapa;
	tools.Vector2d portal;
	int nodos_expandidos;
	int pos_siguiente_accion;
	Set<Integer> capasAzules;
	Set<Integer> capasRojas;
	final int MAX_ANCHO;
	
	
	public AgenteAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		Dimension world = stateObs.getWorldDimension();
		ArrayList<Observation>[][] grid = stateObs.getObservationGrid();
		MAX_ANCHO = grid[0].length;
		Nodo.MAX_ANCHO = MAX_ANCHO;
		fescala = new Vector2d(world.width / grid.length, 
				world.height / grid[0].length);
		acciones = new ArrayList<ACTIONS>();
		ruta_calculada = false;

		mapa = new int[grid.length][grid[0].length];
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
		                capasRojas.add(x*MAX_ANCHO +y);
		            } else if (obs.itype == 9) { // Capa azul
		                mapa[x][y] = 6;
		                capasAzules.add(x*MAX_ANCHO+y);
		            }
		        }
		    }
		}
		
		
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
	
	private void aumentarAntiguedad(PriorityQueue<Nodo> a) {
		for (Nodo n: a) {	
			n.antiguedad++;
		}
	}
	
	private Nodo inicializarNodo(StateObservation stateObs) {
		Nodo nodo_actual = new Nodo((int)(stateObs.getAvatarPosition().x / fescala.x), 
				(int)(stateObs.getAvatarPosition().y / fescala.y), ACTIONS.ACTION_NIL, null);
		nodo_actual.capasAzules = new HashSet<>(capasAzules);
		nodo_actual.capasRojas = new HashSet<>(capasRojas);
		nodo_actual.g = 0;
		nodo_actual.h = distanciaManhattan(nodo_actual);
		return nodo_actual;
	}
	
	private int distanciaManhattan(Nodo n) {
		return (int) (Math.abs(n.x - portal.x) + Math.abs(n.y - portal.y));
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
	    if (ruta_calculada) {
	        pos_siguiente_accion++;
	        return acciones.get(pos_siguiente_accion);
	    } else {
	        Set<Nodo> cerrados = new HashSet<>();
	        PriorityQueue<Nodo> abiertos = new PriorityQueue<>();
	        Nodo nodo_actual = inicializarNodo(stateObs);
	        
	        abiertos.add(nodo_actual);

	        while (!abiertos.isEmpty()) {
	            aumentarAntiguedad(abiertos);
	            nodo_actual = abiertos.poll();

	            nodos_expandidos++;
	            // ¿Es el objetivo?
	            if (nodo_actual.x == portal.x && nodo_actual.y == portal.y) {
	                calcularRuta(nodo_actual);
	                ruta_calculada = true;
	                System.out.println("Nodos expandidos: " + nodos_expandidos);
	                System.out.println("Tamaño ruta: " + acciones.size());
	                return acciones.get(pos_siguiente_accion);
	            }

	            cerrados.add(nodo_actual);
	            
	            for (Nodo sucesor : getVecinos(stateObs, nodo_actual)) {	            	
	                // Calcular coste temporal para este camino
	                float nuevoG = nodo_actual.g + 1;
                	float antiguoG = Float.MAX_VALUE; // el g del sucesor en cerrados

	                // Si ya está en cerrados pero encontramos un mejor camino
	                if (cerrados.contains(sucesor)) {
	                	for (Nodo obj : cerrados) {
	                        if (obj.equals(sucesor))
	                        	antiguoG = obj.g;
	                        continue;
	                    }
	                    if (nuevoG < antiguoG) {
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
	                
	                
	                // Si ya está en abiertos pero encontramos un mejor camino
	                else if (abiertos.contains(sucesor)) {
	                	for (Nodo obj : abiertos) {
	                        if (obj.equals(sucesor))
	                        	antiguoG = obj.g;
	                        continue;
	                    }
	                	if(nuevoG < antiguoG) {
	                		abiertos.remove(sucesor);
		                    sucesor.g = nuevoG;
		                    sucesor.h = distanciaManhattan(sucesor);
		                    abiertos.add(sucesor);
	                	}
	                }
	            }
	        }
	    }

	    return ACTIONS.ACTION_NIL;
	}

	
}
