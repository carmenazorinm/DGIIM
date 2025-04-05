package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

import ontology.Types;
import java.util.HashSet;
import java.util.Set;
import java.util.AbstractMap;
import java.util.AbstractMap.SimpleEntry;
import serialization.Vector2d;
import ontology.Types.ACTIONS;

public class Nodo implements Comparable<Nodo>{
	public float g;
	public float h;
	public double x;
	public double y;
	public int antiguedad;
	public ACTIONS accion;
	public Nodo padre;
	boolean capa_azul;
	boolean capa_roja;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasAzules;
	Set<AbstractMap.SimpleEntry<Integer, Integer>> capasRojas;
	
	public Nodo(double x, double y, ACTIONS a, Nodo p) {
		this.x = x;
		this.y = y;
		g = Integer.MAX_VALUE;
		h = 0; 
		antiguedad = 0;
		accion = a;
		padre = p;
		if(p != null && p.capa_azul) capa_azul = true;
		else capa_azul = false;
		if(p != null && p.capa_roja) capa_roja = true;
		else capa_roja = false;
		// añadir capas
		anadirCapas();
	}
	
	public Nodo(Vector2d v, ACTIONS a, Nodo p) {
		this.x = v.x;
		this.y = v.y;
		g = Integer.MAX_VALUE;
		h = 0; 
		antiguedad = 0;
		accion = a;
		padre = p;
		if(p != null && p.capa_azul) capa_azul = true;
		else capa_azul = false;
		if(p != null && p.capa_roja) capa_roja = true;
		else capa_roja = false;
		// añadir capas
		anadirCapas();
	}
	
	private void anadirCapas() {
		if(padre != null) {
			capasAzules = new HashSet<>(padre.capasAzules);
		    capasRojas = new HashSet<>(padre.capasRojas);
		
		    AbstractMap.SimpleEntry<Integer,Integer> par = new AbstractMap.SimpleEntry<>((int)x,(int) y);
		    // si el padre no tenía capa azul y el hijo si que la tiene, eso es que la casilla del hijo tenía una capa
			if (!padre.capa_azul && capa_azul && capasAzules.contains(par)) {
				capasAzules.remove(par);
			} else if(!padre.capa_roja && capa_roja && capasRojas.contains(par)) {
				capasRojas.remove(par);
			}
		} else {
			capasAzules = new HashSet<>();
		    capasRojas = new HashSet<>();
		}
	}
	
	public boolean hayCapaAzul(double a, double b) {
		AbstractMap.SimpleEntry<Integer,Integer> par = new AbstractMap.SimpleEntry<>((int)a,(int) b);
		if(capasAzules.contains(par)) return true;
		else return false;
	}
	
	public boolean hayCapaRoja(double a, double b) {
		AbstractMap.SimpleEntry<Integer,Integer> par = new AbstractMap.SimpleEntry<>((int)a,(int) b);
		if(capasRojas.contains(par)) return true;
		else return false;
	}
	
	@Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Nodo nodo = (Nodo) o;
        return x == nodo.x && y == nodo.y && capa_azul == nodo.capa_azul && capa_roja == nodo.capa_roja && capasAzules.equals(nodo.capasAzules) && capasRojas.equals(nodo.capasRojas);
    }

	
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
		} else {
			return 1;
		}
	}

	
}
