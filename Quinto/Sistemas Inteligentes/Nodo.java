package tracks.singlePlayer.evaluacion.src_azorinmarticarmen;

import ontology.Types;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.AbstractMap;
import java.util.AbstractMap.SimpleEntry;
import serialization.Vector2d;
import ontology.Types.ACTIONS;

public class Nodo implements Comparable<Nodo>{
	public static int MAX_ANCHO;
	public float g;
	public float h;
	public int x;
	public int y;
	public int antiguedad;
	public ACTIONS accion;
	public Nodo padre;
	boolean capa_azul;
	boolean capa_roja;
	Set<Integer> capasAzules;
	Set<Integer> capasRojas;
	
	public Nodo(int x, int y, ACTIONS a, Nodo p) {
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
		if(p != null && p.capa_azul) capa_azul = true;
		else capa_azul = false;
		if(p != null && p.capa_roja) capa_roja = true;
		else capa_roja = false;
		// actualizar capas recogidas
		anadirCapas();
	}
	
	private void anadirCapas() {
		if(padre != null) {
			capasAzules = new HashSet<>(padre.capasAzules);
		    capasRojas = new HashSet<>(padre.capasRojas);
		
		    //AbstractMap.SimpleEntry<Integer,Integer> par = new AbstractMap.SimpleEntry<>((int)x,(int) y);
			int par = x*MAX_ANCHO +y;
		    if (capasAzules.remove(par)) {
				capa_azul = true;
				capa_roja = false;
			} else if(capasRojas.remove(par)) {
				capa_roja = true;
				capa_azul = false;
			}
		} else {
			capasAzules = new HashSet<>();
		    capasRojas = new HashSet<>();
		}
	}
	
	
	@Override
	public boolean equals(Object o) {
        Nodo otro = (Nodo) o;
        return this.x == otro.x && this.y == otro.y &&
               this.capa_azul == otro.capa_azul &&
               this.capa_roja == otro.capa_roja &&
               this.capasAzules.equals(otro.capasAzules) &&
               this.capasRojas.equals(otro.capasRojas);
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
	
	@Override
	public int hashCode() {
	    return Objects.hash(x, y, capa_azul, capa_roja, capasAzules, capasRojas);
	}

	
}