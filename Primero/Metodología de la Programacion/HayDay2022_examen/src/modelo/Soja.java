/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

//he añadido extends cultivo
public class Soja extends Cultivo{
    public static final String ICONO = "/img/soja.png";
    

    // ----
    // EXAMEN
    public static final int PRECIO_VENTA = 3;
    public static final int EXPERIENCIA = 2;
    public static final int DURACION = 5;
    public static final int RIEGO = 20;

    // TODO ...
    
     public Soja(){
        super(ICONO,DURACION,EXPERIENCIA,PRECIO_VENTA,RIEGO,TipoCultivo.SOJA);
    }
    
     @Override
    public void enProduccion() {
        System.out.println("Cultivando Soja"); //To change body of generated methods, choose Tools | Templates.
    }
     

    // FIN DE EXAMEN
    // ----
}
