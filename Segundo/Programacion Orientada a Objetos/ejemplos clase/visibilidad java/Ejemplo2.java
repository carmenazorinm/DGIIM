package otropaquete;

/**
 *
 * @author adria
 */

public class Padre {
    
    private privado(){
        
    }

    protected void protegido(){
        
    }

    public void publico(){

    }
    
    void metodo(){ //paquete
        
    }
    
    void procesa(){ //paquete
        System.out.println("Procesando en Padre");
    }
    
    public void tarea(){
        procesa();
        System.out.println("Terminando tarea en Padre");
    }
    
}

////////////////////////////////////////////////////////////

package examen;
import otropaquete.Padre;
import java.util.ArrayList;


class Hija extends Padre{
    
    void publico(){ //ERROR no se puede dar permisos mas restrictivos

    }
    
    
    public void privado(){ 
        super.privado(); //ERROR pq no estamos en el mismo codigo
    }

    private void procesa(){ //no error pq esta definiendo un nuevo metodo
        System.out.println("Procesando en Hija");
    }

    void test1(){
        protegido(); //bien pq es hiaj es subclase
        tarea(); //bien pq es publico
    }

    void test2(Padre p){
        p.protegido(); //ERROR pq p no es-un yo++
        p.tarea(); //bien pq tarea es publico
    }

    void test3(Nieta n){
        n.metodoNieta(); //bien pq estamos en el mismo paquete
        n.protegido(); //bien pq n es-un yo y protegido esta definido en superclase
    }
    
    void test4(Hija h){
        h.protegido(); //bien
        h.procesa(); //bien pq estamos en el mismo codigo
    }
}

class Nieta extends Hija implements Examen{
    
    //ERROR falta @Override
    public void procesa(){ 
        System.out.println("Procesando en Nieta");
    }

    protected void metodoNieta(){
        
    }
    
    void test5(){ //error segun adri----------------
        tarea();
        privado(); //bien pq privado es publico
    }
}


interface Examen{
    void test5();
}


public class Pruebas {

    public static void main(String[] args) {
        
        Hija p = new Padre(); //ERROR pq Padre no es-un Hija
        Hija h = new Hija();
        Nieta n = new Nieta();

        ((Hija) n).tarea(); //si pq es publico

        ArrayList<Examen> examenes = new ArrayList<>(); //bien

        examenes.add(h); //ERROR de compilacion
        examenes.add(n); //no da error pq n es un examen

        h = (Hija)(Padre)(Object) n; //bien
        ArrayList<Hija> hijas = (ArrayList<Hija>)(Object) n; //error de ejecucion
        
        ArrayList<Hija> lista = new ArrayList<>(); //bien

        Hija hija = new Hija();
        Nieta nieta = new Nieta();
        
        lista.add(hija); //bien
        lista.add(nieta); //bien pq nieta es una Hija

        ((Padre) lista.get(1)).tarea(); //bien
        ((Padre) lista.get(1)).metodo(); //ERROR pq metodo es de paquete

    }   
}
