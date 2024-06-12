/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ej2;

/**
 *
 * @author mariacribi
 */
public class punto2D {
    double x;
    double y;

    public punto2D (double yi, double yj){
        x=yi;
        y=yj;
    }

    public double getX(){
        return x; 
    }
    public double getY(){
        return y;
    }
    /*public void setX(double){
        x= 
    }
    public void setY(){
        return y;
    }*/
    @Override
    public String toString(){
        String s= "("+x+","+y+")";
        return s; 
    }
    
     
}
