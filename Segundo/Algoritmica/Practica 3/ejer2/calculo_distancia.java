/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ej2;
//import java.util.InputMismatchException;

//import java.util.Scanner;
//import java.math.*;
//import ej2.punto2D; 
/**
 *
 * @author mariacribi
 */
public class ejer2 {
     //atributos
    punto2D a;
    punto2D b;

    
    public ejer2(punto2D un_a, punto2D un_b){
        a=un_a;
        b=un_b;
    }

    public int DistanciaEuclidea (){  //les damos las coordenadas de dos puntos (xi,yi) y (xj,yj)
        double dist=0; 
        int dist_f=0; 
        
        dist= Math.sqrt( ((b.getX()-a.getX())*(b.getX()-a.getX())) + ((a.getY()-b.getY())*(a.getY()-b.getY())) );

        
        //truncamos la distancia
        dist_f=(int)(dist); 
    
        return dist_f; 
    }  

}
