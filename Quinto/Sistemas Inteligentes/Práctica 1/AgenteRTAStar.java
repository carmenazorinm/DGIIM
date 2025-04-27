package tracks.singlePlayer.evaluacion.src_AZORIN_MARTI_CARMEN;

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
	int[][] mapa; // guarda los muros grises, marrones y azules y los pinchos
	tools.Vector2d portal; // posicion del portal
	int nodos_expandidos;
	Set<Integer> capasAzules; // guarda las posiciones de las capas azules iniciales
	Set<Integer> capasRojas; // guarda las posiciones de las capas rojas iniciales
	private HashMap<Nodo, Float> tablaHeuristica; // guarda las heurísticas de cada nodo -> al principio vacía
	final int MAX_ANCHO; // ancho del mapa para calcular la clave de los nodos
	long tInit;
	long tFin;
	long tAcumulado; // para calcular el runtime de SOLAMENTE la busqueda de la ruta
	
	
	public AgenteRTAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length, 
				stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
		nodos_expandidos = 0;
		MAX_ANCHO = stateObs.getObservationGrid().length;
		Nodo.MAX_ANCHO = MAX_ANCHO; // el ancho del mapa servirá para calcular la clave de cada nodo
		mapa = new int[stateObs.getObservationGrid().length][stateObs.getObservationGrid()[0].length];
		Arrays.stream(mapa).forEach(row -> Arrays.fill(row, 7)); // Inicializa todo a 7 en una línea
		
		// rellenamos el mapa. Para eso usamos los itype de los immovable
				/*
				 * 7 -> cesped, se puede pasar sin problema
				 * 0 -> muro gris
				 * 1 -> muro azul
				 * 2 -> muro marrón
				 * 4 -> pinchos
		*/
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
		                mapa[x][y] = 5;
		                capasRojas.add(x*MAX_ANCHO +y);
		            } else if (obs.itype == 9) { // Capa azul
		                mapa[x][y] = 6;
		                capasAzules.add(x*MAX_ANCHO +y);
		            }
		        }
		    }
		}
		
		// calculamos la posicion del portal
		ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions();
		portal = posiciones[0].get(0).position;
		portal.x = (int)(portal.x / fescala.x); 
		portal.y = (int)(portal.y / fescala.y);
		
		// se inicializan a un HashSet vacío que se irá rellenando conforme se crean los nodos
		inicializarHeuristicas(stateObs);
		
		// inicializamos el nodo actual, por el que se empieza. Sus capas serán las iniciales del mapa
		actual = new Nodo((int)(stateObs.getAvatarPosition().x / fescala.x),
                (int)(stateObs.getAvatarPosition().y / fescala.y),
                ACTIONS.ACTION_NIL, null);

		actual.capasAzules = new HashSet<>(capasAzules);
		actual.capasRojas = new HashSet<>(capasRojas);
		tAcumulado = 0;
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
	    	Nodo n = new Nodo(x+1, y, ACTIONS.ACTION_RIGHT, nodo);
	        vecinos.add(n);
	        tablaHeuristica.put(n,obtenerHeuristica(n));
	    }
	    
	    // Izquierda (x-1)
	    if (x - 1 >= 0 && esMovimientoValido(mapa[x-1][y], nodo)) {
	    	Nodo n = new Nodo(x-1, y, ACTIONS.ACTION_LEFT, nodo);
	        vecinos.add(n);
	        tablaHeuristica.put(n,obtenerHeuristica(n));
	    }
	    
	    // Arriba (y-1)
	    if (y - 1 >= 0 && esMovimientoValido(mapa[x][y-1], nodo)) {
	    	Nodo n = new Nodo(x, y-1, ACTIONS.ACTION_UP, nodo);
	        vecinos.add(n);
	    	tablaHeuristica.put(n,obtenerHeuristica(n));
	    }
	    
	    // Abajo (y+1)
	    if (y + 1 < mapa[0].length && esMovimientoValido(mapa[x][y+1], nodo)) {
	    	Nodo n =  new Nodo(x, y+1, ACTIONS.ACTION_DOWN, nodo);
	        vecinos.add(n);
	        tablaHeuristica.put(n,obtenerHeuristica(n));
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
	
	// las heuristicas son vacias y se iran rellenando a medida que se creen los nodos. Ya que hay que crear
	// una heuristica por cada posible nodo (posicion, capa actual y capas restantes) y calcularlas por defecto
	// no es eficiente. Puede haber nodos que nunca se visiten y hayamos calculado su heurística en vano.
	private void inicializarHeuristicas(StateObservation stateObs) {
		tablaHeuristica = new HashMap<>();
	}
	
	// la heuristica del nodo
	private float distanciaManhattan(Nodo n) {
		return (float) (Math.abs(n.x - portal.x) + Math.abs(n.y - portal.y));
	}
	
	// la heuristica del nodo será la que este guardada en el hashset y, si no esta guardada en el hashset,
	// entonces es la distancia manhattan (es la primera vez que se calcula)
	private float obtenerHeuristica(Nodo n) {
		return tablaHeuristica.getOrDefault(n, distanciaManhattan(n));
	}
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		tInit = System.nanoTime();
	    // actualizamos las capas
		int pos = actual.x *MAX_ANCHO +actual.y;
		capasAzules.remove(pos);
		capasRojas.remove(pos);
		
		nodos_expandidos++;

	    // calculamos los vecinos
	    List<Nodo> vecinos = getVecinos(stateObs, actual);

	    // calculamos f(y) = h(y) + c(actual,y) = h(y) + 1
	    Nodo mejorVecino = null;
	    float mejorValor = Float.MAX_VALUE;
	    float segundoMejor = Float.MAX_VALUE;

	    // vamos a guardar el mejor vecino (para movernos) y la f del segundo mejor vecino (para actualizar la tabla) 
	    for (Nodo vecino : vecinos) {
	        float coste = 1; // c(actual,vecino) - asumimos coste uniforme 1
	        float h = obtenerHeuristica(vecino);
	        float f = coste + h;
	        vecino.g = coste;
	        vecino.h = h;

	        // Actualizar mejor y segundo mejor
	        if (f < mejorValor) {
	            segundoMejor = mejorValor;
	            mejorValor = f;
	            mejorVecino = vecino;
	        } else if (f < segundoMejor) {
	            segundoMejor = f;
	        }
	    }

	    // actualizamos la heuristica del nodo_actual. Si no hay segundo mejor vecino, se queda con el primero
	    if (segundoMejor != Float.MAX_VALUE) {
    		tablaHeuristica.put(actual, Math.max(
    	            obtenerHeuristica(actual),
    	            segundoMejor
    	        ));
	    } else {	    	
	    	tablaHeuristica.put(actual, Math.max(
		            obtenerHeuristica(actual),
		            mejorValor
		        ));
	    }

	    // comprobamos que el mejorVecino no sea el portal. Si lo es, ya hemos terminado.
	    actual = mejorVecino;
	    if (actual.x == portal.x && actual.y == portal.y) {
	    	tFin = System.nanoTime();
		    tAcumulado += (tFin - tInit);
	        System.out.println("Nodos expandidos: " + nodos_expandidos); 
	        System.out.println("Tiempo busqueda: " + tAcumulado/1000000);
	    }
	    
	    tFin = System.nanoTime();
	    tAcumulado += (tFin - tInit);
	    
	    // devolvemos la accion correspondiente al mejor vecino
	    return mejorVecino != null ? mejorVecino.accion : ACTIONS.ACTION_NIL;
	}

}
