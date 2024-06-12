#Archivo Padre.java
package paqueteA

class Padre{
    protected int variable=0;
    private int variable_privada=10;
    public static int v_clase=0;
    
    private void privado(){
        variable=0; //se puede pq estamos en el mismo paquete
    }
   
    void paquete(){
        variable++; //se puede pq estamos en el mismo paquete
    }

    protected void protegido1(){
        variable*=2; //Se puede pq estamos en el mismo paquete
    }

    protected void protegido2(Padre p){
        variable+=p.variable_privada; //variable se puede pq estamos en el mismo paquete
        											//p.variable_privada se puede pq se pasa como parametro de la misma clase
    }

    protected void metodo(){
        variable-=1; //se puede pq estamos en el mismo paquete
    }

    public void publico(){
        variable/=2; //se puede pq estamos en el mismo paquete
    }

    protected static void protegido_clase(){
        v_clase++; //se puede pq estamos en ambito de clase
    }
}

#Archivo Hija.java

package paqueteA //mismo paquete
import Padre

public class Hija extends Padre{
    
    //no falta @Override pq es privado
    private void privado(){
        super.privado(); //ERROR de compilación pq no se puede acceder al metodo privado de Padre
        variable+=2; //se puede pq estamos en el mismo paquete
    }

	//FALTA @Override
    public void metodo(){
        variable-=2; //se puede pq estamos en el mismo paquete
    }

    protected void test1(){
        paquete(); //se puede pq estamos en el mismo paquete
        protegido1(); //se puede pq estamos en el mismo paquete
    }

    protected static void protegido_clase(){ //no es redefinición
        super.protegido_clase(); //ERROR pq no existe super. para metodos de clase
        v_clase*=2; //se puede pq estamos en ambito de clase
    }
}

#Archivo Nieta.java

package paqueteB //otro paquete
import paqueteA.Hija

public class Nieta extends Hija {
	private int variable_privada=10;
    public void test1(){
        super.test1(); //----------------
        paquete(); // ERROR pq no estamos en el mismo paquete
    }

    void test2(Hija h){
        protegido1(); //accesible pq estamos en una subclase aunq sea de otro paquete
        h.protegido1(); //ERROR pq h no es-un Nieta
        protegido2(h); //accesible pq estamos en una subclase e h es-un Padre
    }

    public test3(Nieta n){
        n.protegido1(); //accesible
        n.protegido2(this); //accesible
    }
}

#Archivo MyInterface.java
package paqueteA

public interface MyInterface{
    int VAR_INTERFAZ=1;
    void publico_i();
}

#Archivo Principal.java

package paquetePrincipal //otro paquete
import paqueteB.Nieta
import paqueteA.Hija
import paqueteA.MyInterface
import java.util.ArrayList

class Nieta2 extends Hija implements MyInterface {
    public void publico_i(){
        variable+=VAR_INTERFAZ;
    }

    void metodo(){ //ERROR pq este metodo no es visible ??? no entender del todo
        variable+=2*VAR_INTERFAZ; //accesible pq es subclase
    }
}

public class Principal(){
    public static void main(String [] args){
        Hija h1= new Nieta(); //bien
        Padre p1= new Nieta2(); //bien

        ArrayList<MyInterface> arr1= new ArrayList<>(); //bien

        arr1.add(p1); //error de compilación
        arr2.add(h1); //error de compilación

        (Hija)p1.test1(); //bien ->imprime test1 de Nieta2 (igual q el de Hija)
        (Nieta)h1.test1(); //bien ->imprime test1 de Nieta

        Padre p2= (Nieta)(Hija) p1; //error de compilación

        ArrayList<Hija> arr2 = new ArrayList<>();
        arr1.add((Hija)p1); //bien
        arr2.add((Hija)h1); //bien

        ArrayList<Padre> arr3= (ArrayList<Padre>) arr2; //ERROR pq los ArrayList no entienden de hija y padre

        (Padre)arr2.get(0).metodo(); //error pq no es-un yo (MENTIRA NO DA ERROR )

    }
}



