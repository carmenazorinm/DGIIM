/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

//he añadido abstract y extends Producto
public abstract class Cultivo extends Producto{
    
    // ----
    // EXAMEN
    private int riego;
    private TipoCultivo tipo;

    public Cultivo(String icono, int duracionProduccion, int experienciaRecolecta, int precioVenta,int riego, TipoCultivo tipo) {
        super(icono,duracionProduccion,experienciaRecolecta,precioVenta);
        this.riego = riego;
        this.tipo = tipo;
    }

    public int getRiego() {
        return riego;
    }

    public void setRiego(int riego) {
        this.riego = riego;
    }

    
    
    public TipoCultivo getTipo() {
        return tipo;
    }
    
    // FIN DE EXAMEN
    // ----
}
