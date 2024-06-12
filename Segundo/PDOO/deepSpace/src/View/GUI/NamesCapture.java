/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package View.GUI;


import java.util.ArrayList;
import javax.swing.JDialog;


import java.util.Scanner;

/**
 *
 * @author carmenc
 */
public class NamesCapture extends JDialog{
    
    //atributo privado Scanner para leer de consola
    private static final Scanner in = new Scanner(System.in);
    
    //el constructor no hace nada
    public NamesCapture(View.View view){}
    
    //muestra el mensaje
    private void showMessage(String string) {
        System.out.print (string);
    }
    
    //muestra el mensaje y salta de linea
    private void showMessageln(String string) {
        System.out.println (string);
    }
    
    //método para comprobar que se introduce un entero correcto
    private int readInt (String message, int min, int max) { 
        
        boolean valid;
        String input;
        int number = -1;
        do {
          valid = true;
          showMessage (message);
          input = in.nextLine();
          try {  
            number = Integer.parseInt(input);
            if (number<min || number>max) { // No es un entero entre los válidos
              showMessageln ("\nEl numero debe estar entre " + min + " y " + max);
              valid = false;
            }
          } catch (NumberFormatException e) { // No se ha introducido un entero
            showMessageln("\nDebes introducir un numero.");
            valid = false;  
          }
          if (!valid) {
            showMessage("\n\nInténtalo de nuevo.\n\n");
          }
        } while (!valid);
        return number;
  }
    
    public ArrayList<String> readNamePlayers(){
        ArrayList<String> names = new ArrayList<>();
        int nPlayers = readInt ("\n¿Cuántos jugadores participan (2-4)? ",2,4);
        for (int i = 0; i < nPlayers; i++) {
          showMessage ("Escribe el nombre del jugador " + (i+1) + ": ");
          names.add(in.nextLine());
        }
        return names;
    }

    
}
