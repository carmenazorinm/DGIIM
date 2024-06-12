/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package alg3;
//import java.util.InputMismatchException;
import ej2.punto2D; 
import ej2.ejer2; 
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author mariacribi
 */


public class Alg3 {
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException {
        //ej2 ej = new ej2();
        //double distancias[]=new double[dim]; 
        ArrayList <punto2D> puntos=new ArrayList <> (); //inicializamos  
        Scanner scanner = null;
        scanner=new Scanner (System.in);
        String cadena_dim=scanner.next();
        int dim=scanner.nextInt();//lee la dimension
        double num;
        
        for (int i=0; i<dim; i++){  //ya tenemos el arraylist de puntos
            num =scanner.nextDouble(); //numero de ciudad
            punto2D punto=new punto2D(scanner.nextDouble(), scanner.nextDouble()); //creamos un punto
            puntos.add(punto);    //lo insertamos en el arraylist de puntos creado
        }
        
        
        //creamos la matriz de adyaciencia e inicializamos
        int[][] adjacencyMatrix=new int [dim][dim];
        for (int i=0; i<dim; i++){
            for (int j=0;j<dim; j++ )
              adjacencyMatrix[i][j]=0;  
        }
        
        //ponemos la diagonal a 0
        /*for (int i=0; i<dim; i++){
            adjacencyMatrix[i][i]=0;
        }*/
        
        for (int i=0; i<dim; i++){
            for (int j=0; j<dim; j++){
                if (i==j){
                   adjacencyMatrix[i][j]=0;
                }else{
                    ejer2 ej = new ejer2(puntos.get(i), puntos.get(j));
                    adjacencyMatrix[i][j]=ej.DistanciaEuclidea();
                }
            }
            
        }
        
       PrintStream out = new PrintStream(new FileOutputStream("output.txt"));
       System.setOut(out);

        //enseñamos la matriz de adyacencia
        for(int x=0; x < adjacencyMatrix.length; x++) {
            
            out.print(" ");
            for (int y=0; y < adjacencyMatrix[x].length; y++) {
                out.print (adjacencyMatrix[x][y]);
                if (y!=adjacencyMatrix[x].length-1) System.out.print("\t");
            }
            
            out.println(" ");
        }
        
        if (out != null)
            out.close();
        
        scanner.close();


    }
    
}
