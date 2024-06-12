/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 55: el programa creara una incognita y leerá un valor introducido 
	por el jugador. Mostrará si el valor es mayor o menor que la incognita hasta
	que se acierte. Una vez se haya ganado, volverá a empezar el juego. Si el
	numero introducido es -1, entonces el juego se acaba.
*/

#include<iostream> //inclusion de recursos de E/S
#include<ctime>
#include <cstdlib> //inclusion numero aleatorio
#include <string>

using namespace std;

int main(){
	
	const int MIN = 1;
	const int MAX = 10;
	const int NUM_VALORES = MAX-MIN +1;
	
	time_t t;
	srand(time(&t));
	
	int valor_jugador;
	const int TERMINADOR = 0;
	string respuesta;
	
	do{
	//entrada de datos 
	
	cout<< endl;
	cout<< " Cuando se quiera abandonar el juego, introduzca |0|"<< endl;
	
	bool datos_ok; 
	
	do{
		
		cout<< " Introduzca un numero entre 1 y 10: ";
		cin>> valor_jugador;		
		
		datos_ok = 
		(valor_jugador>=MIN && valor_jugador<=MAX)||(valor_jugador==TERMINADOR);
		
	}while(!datos_ok);
	
	//calculos
	
	int incognita = (rand()%NUM_VALORES) + MIN;	
	
	while (valor_jugador != TERMINADOR && incognita != valor_jugador){
			
			if (valor_jugador > incognita){
				
				cout<< endl;
				cout<< "   incognita < " << valor_jugador;
				cout<< endl;
				
				cout<< " Introduzca un nuevo numero: ";
				
			}
			if (valor_jugador < incognita){
				
				cout<< endl;
				cout<< "   " << valor_jugador << " < incognita";
				cout<< endl;
				
				cout<< " Introduzca un nuevo numero: ";
			}
			cin>> valor_jugador;
			cout<< endl;

	}
	if (valor_jugador == TERMINADOR){
		cout<< endl;
		cout<< " Abandonaste el juego. La incognita era "<< incognita;
		cout<< endl;
	}else{
		cout<< endl;
		cout<< " Has acertado! La incognita era " << incognita;
		cout<< endl;
	}
	cout<< " ¿Quiere volver a jugar? ";
	cin>> respuesta;
	
	}while(respuesta == "si" || respuesta == "SI");
	
	return 0;
}
