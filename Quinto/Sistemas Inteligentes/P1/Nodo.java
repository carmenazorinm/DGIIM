package tracks.singlePlayer.evaluacion.src_AZORIN_MARTI_CARMEN;

import ontology.Types;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.AbstractMap;
import java.util.AbstractMap.SimpleEntry;
import serialization.Vector2d;
import ontology.Types.ACTIONS;

public class Nodo implements Comparable<Nodo>{
	public static int MAX_ANCHO; // ancho del mapa para calcular la clave del nodo
	public float g; // el coste desde el inicio
	public float h; // la heurístcia hasta el portal
	public int x; // coordenada x de la posicion
	public int y; // coordenada y de la posicion
	public int antiguedad; // antiguedad en la cola de prioridad de A* y Dijkstra
	public ACTIONS accion; // accion que ha hecho el padre para llegar al nodo
	public Nodo padre; // nodo padre
	boolean capa_azul; // false si no lleva la capa azul
	boolean capa_roja; // false si no lleva la capa roja
	Set<Integer> capasAzules; // capas azules que le quedan por recoger
	Set<Integer> capasRojas; // capas rojas que le quedan por recoger
	
	public Nodo(int x, int y, ACTIONS a, Nodo p) {
		this.x = x;
		this.y = y;
		g = Integer.MAX_VALUE;
		h = 0; 
		antiguedad = 0;
		accion = a;
		padre = p;
		// si el padre tiene capa, la hereda. Aunque puede cambiarla en el método anadirCapas()
		if(p != null && p.capa_azul) capa_azul = true; 
		else capa_azul = false;
		if(p != null && p.capa_roja) capa_roja = true;
		else capa_roja = false;
		// actualizar capas recogidas
		anadirCapas();
	}
	
	public Nodo(Vector2d v, ACTIONS a, Nodo p) {
		this.x = (int)v.x;
		this.y = (int)v.y;
		g = Integer.MAX_VALUE;
		h = 0; 
		antiguedad = 0;
		accion = a;
		padre = p;
		// si el padre tiene capa, la hereda. Aunque puede cambiarla en el método anadirCapas()
		if(p != null && p.capa_azul) capa_azul = true;
		else capa_azul = false;
		if(p != null && p.capa_roja) capa_roja = true;
		else capa_roja = false;
		// actualizar capas recogidas
		anadirCapas();
	}
	
	private void anadirCapas() {
		// si tiene padre, hereda sus capas restantes.
		if(padre != null) {
			capasAzules = new HashSet<>(padre.capasAzules);
		    capasRojas = new HashSet<>(padre.capasRojas);
		
		    // si está en una posición donde había una capa, la acaba de coger y actualiza el set
			int par = x*MAX_ANCHO +y; // clave del hashSet
		    if (capasAzules.remove(par)) {
				capa_azul = true;
				capa_roja = false;
			} else if(capasRojas.remove(par)) {
				capa_roja = true;
				capa_azul = false;
			}
		} else { // si no tiene padre, las capas restantes se le añadirán en el Agente
			capasAzules = new HashSet<>();
		    capasRojas = new HashSet<>();
		}
	}
	
	
	// el estado del nodo depende de la posicion, la capa actual y las cpas restantes
	@Override
	public boolean equals(Object o) {
        Nodo otro = (Nodo) o;
        return this.x == otro.x && this.y == otro.y &&
               this.capa_azul == otro.capa_azul &&
               this.capa_roja == otro.capa_roja &&
               this.capasAzules.equals(otro.capasAzules) &&
               this.capasRojas.equals(otro.capasRojas);
    }

	// el orden de los nodos depende de la f, después de la g, después de la antiguedad (a mayor antiguedad, menos valor)
	// y después de la accion (right, left, up, down)
	@Override
	public int compareTo(Nodo o) {
		// comparamos la f
		if(this.g + this.h > o.g + o.h) {
			return 1;
		} else if (this.g + this.h < o.g + o.h) {
			return -1;
		} else if(this.g > o.g) { // comparamos la g
			return 1;
		} else if(this.g < o.g) {
			return -1;
		} else if(this.antiguedad > o.antiguedad) { // comparamos la antiguedad
			return -1;
		}else if(this.antiguedad < o.antiguedad) { // comparamos la antiguedad
			return 1;
		} else if(this.accion == ACTIONS.ACTION_RIGHT && o.accion != ACTIONS.ACTION_RIGHT) {
			return -1;
		} else if (o.accion == ACTIONS.ACTION_RIGHT && this.accion != ACTIONS.ACTION_RIGHT) {
			return 1;
		} else if (this.accion == ACTIONS.ACTION_LEFT && o.accion != ACTIONS.ACTION_LEFT) {
			return -1;
		} else if(o.accion == ACTIONS.ACTION_LEFT && this.accion != ACTIONS.ACTION_LEFT) {
			return 1;
		} else if(this.accion == ACTIONS.ACTION_UP && o.accion != ACTIONS.ACTION_UP) {
			return -1;
		} else if(o.accion == ACTIONS.ACTION_UP && this.accion != ACTIONS.ACTION_UP) {
			return 1;
		} else if(this.accion == ACTIONS.ACTION_DOWN && o.accion != ACTIONS.ACTION_DOWN) {
			return -1;
		} else if(o.accion == ACTIONS.ACTION_DOWN && this.accion != ACTIONS.ACTION_DOWN){
			return 1;
		}
		return 0;
	}
	
	// para poder usar el hashSet en los agentes
	@Override
	public int hashCode() {
	    return Objects.hash(x, y, capa_azul, capa_roja, capasAzules, capasRojas);
	}

	
}