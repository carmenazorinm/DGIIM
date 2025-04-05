package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

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
		for(int i = 0; i < mapa.length; i++) {
			for(int j = 0; j < mapa[0].length; j++) {
				mapa[i][j] = 7;
			}
		}
		
		ArrayList<Observation>[] immovable = stateObs.getImmovablePositions();
		for(int i = 0; i < immovable.length; i++) {
			for (int j = 0; j < immovable[i].size(); j++) {
				Observation obs = immovable[i].get(j);
				int x = (int) Math.floor(obs.position.x / fescala.x );
				int y = (int) Math.floor(obs.position.y / fescala.y );
		        // System.out.println("Inmovable iType: " + obs.itype + " at grid (" + x + "," + y + ")");
		        if (obs.itype == 5) { // muro gris
		            mapa[x][y] = 0;
		        } else if (obs.itype == 7) { // muro azul -> necesita capa azul
		            mapa[x][y] = 1;
		        } else if (obs.itype == 6) { // muro marron -> necesita capa roja
		            mapa[x][y] = 2;
		        } else if (obs.itype == 3) { // pinchos
		        	mapa[x][y] = 4;
		        }
			}
		}
		
		capasAzules = new HashSet<>();
	    capasRojas = new HashSet<>();
		ArrayList<Observation>[] recursos = stateObs.getResourcesPositions();
		if(recursos != null) {
			for (int i = 0; i < recursos.length; i++) {
			    for (Observation obs : recursos[i]) {
			        int x = (int) Math.floor(obs.position.x / fescala.x);
			        int y = (int) Math.floor(obs.position.y / fescala.y);
			        // System.out.println("Capa roja iType: " + obs.itype + " at grid (" + x + "," + y + ")");
			        if (obs.itype == 8) { // capa roja
			            mapa[x][y] = 5; 
			            capasRojas.add(new AbstractMap.SimpleEntry<>(x,y));
			        } else if (obs.itype == 9) { // capa azul
			            mapa[x][y] = 6;
			            capasAzules.add(new AbstractMap.SimpleEntry<>(x,y));
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
		portal.x = Math.floor(portal.x / fescala.x);
		portal.y = Math.floor(portal.y / fescala.y);
		
		nodos_expandidos = 0;
		pos_siguiente_accion = 0;
	}
	
	private boolean nodoExpandible(Nodo n) {
		int x = (int) n.x; 
		int y = (int) n.y;
		if(mapa[x][y] == 0 || mapa[x][y] == 4) return false;
		else if(mapa[x][y] == 1 && !n.capa_azul) return false;
		else if(mapa[x][y] == 2 && !n.capa_roja) return false;
		else return true;
	}

	private ArrayList<Nodo> getVecinos(StateObservation stateObs, Nodo nodo) {
		ArrayList<Nodo> vecinos = new ArrayList<>();
		
		Vector2d avatar = new Vector2d(nodo.x, nodo.y);
		Vector2d newPos_right = avatar, newPos_left = avatar, newPos_up = avatar, newPos_down = avatar;
		
		if (avatar.x +1 <= stateObs.getObservationGrid().length -1) {
			newPos_right = new Vector2d(avatar.x+1, avatar.y);
			Nodo hijo = new Nodo(newPos_right, ACTIONS.ACTION_RIGHT, nodo);
			if(nodoExpandible(hijo)) {
				vecinos.add(hijo);
			}
		}
		if (avatar.x -1 >= 0) {
			newPos_left = new Vector2d(avatar.x-1, avatar.y);
			Nodo hijo = new Nodo(newPos_left, ACTIONS.ACTION_LEFT, nodo);
			if(nodoExpandible(hijo)) {
				vecinos.add(hijo);
			}
		}
		
		if (avatar.y -1 >= 0) {
			newPos_up = new Vector2d(avatar.x, avatar.y-1);
			Nodo hijo = new Nodo(newPos_up, ACTIONS.ACTION_UP, nodo);
			if(nodoExpandible(hijo)) {
				vecinos.add(hijo);
			}
		}
		
		if (avatar.y +1 <= stateObs.getObservationGrid()[0].length -1) {
			newPos_down = new Vector2d(avatar.x, avatar.y+1);
			Nodo hijo = new Nodo(newPos_down, ACTIONS.ACTION_DOWN, nodo);
			if(nodoExpandible(hijo)) {
				vecinos.add(hijo);
			}
		}
		return vecinos;
	}
	
//	private boolean enVisitados(Nodo nodo, ArrayList<Nodo> visitados) {
//		for(Nodo n: visitados) {
//			if(n.x == nodo.x && n.y == nodo.y && n.capa_azul == nodo.capa_azul && n.capa_roja == nodo.capa_roja) {
//				return true;
//			}
//		}
//		return false;
//	}
	
	private void aumentarAntiguedad(ArrayList<Nodo> a) {
		for (Nodo n: a) {
			n.antiguedad++;
		}
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
			ArrayList<Nodo> visitados = new ArrayList<>();
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
	
}
