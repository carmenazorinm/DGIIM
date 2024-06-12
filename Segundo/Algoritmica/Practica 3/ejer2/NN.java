import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Stack;
import java.util.Random;
 

public class NN{
    private int nNodos;
    private Stack<Integer> pila;

    public NN(){
        pila = new Stack<Integer>();
    }

    public void CalcularRecorrido(int matriz[][]){

        Random rand = new Random();
        int int_random = rand.nextInt(matriz[1].length-1)+1;

        nNodos = matriz[1].length - 1;
        int[] ciudadesVisitadas = new int[nNodos + 1];
        ciudadesVisitadas[int_random] = 1;
        pila.push(int_random);
        int element, dst = 0, i;
        int min = Integer.MAX_VALUE;
        boolean minFlag = false;
        int suma = 0;
        System.out.print(int_random + "\t");

        while (!pila.isEmpty()){

            element = pila.peek();
            i = 1;
            min = Integer.MAX_VALUE;

            while (i <= nNodos){

                if (element!=i && ciudadesVisitadas[i] == 0){

                    if (min > matriz[element][i]){

                        min = matriz[element][i];
                        dst = i;
                        minFlag = true;
                    }
                }
                i++;
            }

            if(min==matriz[element][dst]){
                suma += min;
            }else{
                if(element == dst)
                    suma += matriz[element][int_random];
            }

            if (minFlag){

                ciudadesVisitadas[dst] = 1;
                pila.push(dst);
                System.out.print(dst + "\t");
                minFlag = false;
                continue;
            }
            pila.pop();
        }

        System.out.print("Distancia recorrida: " + suma + "\n");
    }

 

    public static void main(String... arg)
    {
        int number_of_nodes;
        Scanner scanner = null;
        try{

            scanner = new Scanner(System.in);
            number_of_nodes = scanner.nextInt();
            int adjacency_matrix[][] = new int[number_of_nodes + 1][number_of_nodes + 1];

            for (int i = 1; i <= number_of_nodes; i++){
                for (int j = 1; j <= number_of_nodes; j++){
                    adjacency_matrix[i][j] = scanner.nextInt();
                }
            }

            for (int i = 1; i <= number_of_nodes; i++){
                for (int j = 1; j <= number_of_nodes; j++){
                    if (adjacency_matrix[i][j] == 1 && adjacency_matrix[j][i] == 0){
                        adjacency_matrix[j][i] = 1;
                    }
                }
            }

            System.out.println("Recorrido de 16 ciudades con Vecino más cercano");
            NN tspNearestNeighbour = new NN();

            long start1 = System.nanoTime();
            tspNearestNeighbour.CalcularRecorrido(adjacency_matrix);
            long end1 = System.nanoTime();

            System.out.println("Elapsed Time in nano seconds: "+ (end1-start1));

        } catch (InputMismatchException inputMismatch){
             System.out.println("Wrong Input format");
        }
        scanner.close();
    }
}