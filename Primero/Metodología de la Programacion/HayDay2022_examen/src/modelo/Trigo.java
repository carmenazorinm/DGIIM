/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

//he añadido extends cultivo
public class Trigo extends Cultivo{
    public static final String ICONO = "/img/trigo.png";

    
    // ----
    // EXAMEN
    public static final int PRECIO_VENTA = 2;
    public static final int EXPERIENCIA = 1;
    public static final int DURACION = 2;
    public static final int RIEGO = 10;

    
    
     public Trigo(){
        super(ICONO,DURACION,EXPERIENCIA,PRECIO_VENTA,RIEGO,TipoCultivo.TRIGO);
    }

    
    @Override
    public void enProduccion() {
        System.out.println("Cultivando Trigo"); //To change body of generated methods, choose Tools | Templates.
    }
    
    
    // FIN DE EXAMEN
    // ----

    @Override
    public void setRiego(int riego) {
        if(riego <= 10)
            super.setRiego(riego); //To change body of generated methods, choose Tools | Templates.
    }

    
}
