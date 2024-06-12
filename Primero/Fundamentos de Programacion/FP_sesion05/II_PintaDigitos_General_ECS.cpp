/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 28: el programa lee un string numero entero positivo, lo pasa a
	int y se asegura de que sea positivo. Posteriormente, se irá creando con 
	un for un nuevo string que separará cada digito del numero inicial con una |
*/

#include <iostream> //inclusion de recursos de E/S
#include <string> 
#include<cmath> //inclsuion de recursos matematicos

using namespace std;


int main(){
	
	string numero_cadena;
	int numero;
	
	//entrada de datos
	
	do{
		
		cout<< endl;
		cout<< " Introduzca un entero positivo: ";
		cin>> numero_cadena;
		cout<< endl;
		
		numero = stoi(numero_cadena);
	
	}while (numero<0);
	
	//calculos
	
	int longitud = numero_cadena.length();
	int numero_a_guardar;
	int aux = numero;
	int potencia = longitud - 1; //para quedarnos con la parte entera del numero
	string cad_resultado;
	
	for( int i=1; i<=longitud ; i++){
		
		numero_a_guardar = aux/pow(10,potencia);
		aux = aux - numero_a_guardar*pow(10,potencia);
		potencia = potencia -1;
		
		cad_resultado = cad_resultado + "|" + to_string(numero_a_guardar);
	}
	
	//salida
	
	cout<< cad_resultado << "|";
	cout<< endl << endl;
	
	return 0;
}
