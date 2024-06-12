/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package main; //carmen

import controlador.Controlador;
import java.util.ArrayList;
import modelo.Cultivo;
import modelo.Parcela;
import modelo.Soja;
import modelo.Trigo;
import vista.IVista;
import vista.VistaPrincipal;



/**
 *
 * @author Profe
 */
public class HayDay {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // ----
        // EXAMEN
                
           
        // a) Cree 2 parcelas nuevas 
        Parcela parcela1 = new Parcela();
        Parcela parcela2 = new Parcela();
        // b) Cree y 3 cultivos disponibles (2 trigos; 1 soja)
        Cultivo trigo1 = new Trigo();
        Cultivo trigo2 = new Trigo();
        Cultivo soja1 = new Soja();
        
        // c) Cree la vista e inica el controlador
        IVista vista = new VistaPrincipal();
        // llamar a start()
        ArrayList<Parcela> parcelas = new ArrayList<>();
        ArrayList<Cultivo> cultivos = new ArrayList<>();
        parcelas.add(parcela1);
        parcelas.add(parcela2);
        cultivos.add(soja1);
        cultivos.add(trigo1);
        cultivos.add(trigo2);
        
        Controlador.instancia.start(vista, parcelas, cultivos);
        // FIN DE EXAMEN
        // ----
    }
    
}
