import java.util.InputMismatchException;
//import java.io.FileNotFoundException;
import java.util.*;
//import java.io.File;
//import java.util.Stack;

public class InsercionLejana {
    private int east_city;
    private int west_city;
    private int north_city;
    private int suma;

    InsercionLejana(double matrix[][], double dim){
        suma=0;

        double ciudad_este=0;
        double ciudad_oeste=Integer.MAX_VALUE;
        double ciudad_norte=0;
        int index_este=0;
        int index_oeste=0;
        int index_norte=0;

        for(int i = 0; i < dim; i++){
            double lado=matrix[i][1];
            double altura=matrix[i][2];
            if(lado < ciudad_oeste){
                ciudad_oeste=matrix[i][1];
                index_oeste=i;
            }
            if(lado > ciudad_este){
                ciudad_este = matrix[i][1];
                index_este=i;
            }
            if(altura > ciudad_norte){
                ciudad_norte=matrix[i][2];
                index_norte=i;
            }

        }

        if(index_este != index_oeste){
            if(index_este != index_norte){
                east_city=index_este;
                //suma+=ciudad_este;
                if(index_norte != index_oeste){
                    west_city=index_oeste;
                    //suma+=ciudad_oeste;
                    north_city=index_norte;
                    //suma+=ciudad_norte;
                }else{
                    west_city=index_oeste;
                    //suma+=ciudad_oeste;
                    north_city=-1;
                }
            }else{
                east_city=index_este;
                //suma+=ciudad_este;
                north_city=-1;
                west_city=index_oeste;
                //suma+=ciudad_oeste;
            }
        }else{
            east_city=index_este;
            //suma+=ciudad_este;
            west_city=-1;
            if(index_este==index_norte){
                north_city=-1;
            }else{
                north_city=index_norte;
                //suma+=ciudad_norte;
            } 
        }
        // System.out.println("Ciudad más al este: "+east_city);
        // System.out.println("Ciudad más al oeste: "+west_city);
        // System.out.println("Ciudad más al norte: "+north_city);
    }

    void ComprobarLugar(int matrix[][], int dim){
        int[] recorrido=new int [dim];
        int[] visitado=new int [dim];

        for(int i=0; i < dim; i++)
            recorrido[i]=-1;
        for(int i=0; i < dim; i++)
            visitado[i]=0;

        int contr=0;
        int contv=0;
        recorrido[contr]=east_city;
        contr++;
        visitado[east_city]=1;
        contv++;
        if(west_city != -1){ 
            recorrido[contr]=west_city; 
            contr++;
            visitado[west_city]=1;
            contv++;
        }
        if(north_city != -1){ 
            recorrido[contr]=north_city; 
            contr++;
            visitado[north_city]=1;
            contv++;
        }

        for(int i =0; i < contr-1; i++){
            suma+=matrix[recorrido[i]][recorrido[i+1]];
        }
        suma+=matrix[recorrido[0]][recorrido[contr-1]];

        for(int i=0; i<dim; i++){
            if(visitado[i]!=1){
                int index_min = 0;
                int min_suma=suma;
                int suma_aux=0;

                int ps = matrix[recorrido[0]][i] + matrix[i][recorrido[1]];
                min_suma = min_suma - matrix[recorrido[0]][recorrido[1]] +ps;
                index_min=0;

                for(int k=1; k < contr-1; k++){
                    ps = matrix[recorrido[k]][i] + matrix[i][recorrido[k+1]];
                    suma_aux = suma - matrix[recorrido[k]][recorrido[k+1]] +ps;
                    if(suma_aux < min_suma){
                        index_min = k;
                        min_suma = suma_aux;
                    }
                }

                ps=matrix[recorrido[0]][i] + matrix[i][recorrido[contr-1]];
                suma_aux=suma - matrix[recorrido[0]][recorrido[contr-1]]+ps;
                if(suma_aux < min_suma){
                    index_min = contr-1;
                    min_suma = suma_aux;
                } 

                suma=min_suma;


                for(int j = contv; j > index_min; j--){
                    recorrido[j]=recorrido[j-1];
                }
                recorrido[index_min+1]=i;
                contr++;
                visitado[i]=1;
                contv++;
            }
        }

        System.out.println("Longitud ruta: " + suma);

        System.out.println("Ruta: ");
            for(int i = 0; i < dim; i++)
                System.out.print(recorrido[i]+1 + "\t");
        
    }

    public static void main(String... arg) {
        Scanner scanner = null;
        try{

            scanner = new Scanner(System.in);
            int dim = scanner.nextInt();
            int adjacency_matrix[][] = new int[dim][dim];

            for (int i = 0; i < dim; i++){
                for (int j = 0; j < dim; j++){
                    adjacency_matrix[i][j] = scanner.nextInt();
                }
            }

            

            double matriz[][] = new double[dim][3];
            for (int i = 0; i < dim; i++){
                for (int j = 0; j < 3; j++){
                    matriz[i][j] = scanner.nextDouble();
                }
            }

            InsercionLejana a=new InsercionLejana(matriz,dim);

            long start1 = System.nanoTime();
            a.ComprobarLugar(adjacency_matrix, dim);
            long end1 = System.nanoTime();

            System.out.println("Elapsed Time in nano seconds: "+ (end1-start1));


        }catch(InputMismatchException inputMismatch){
            System.out.println("Wrong Input format");
        }
        scanner.close();
    }
}
