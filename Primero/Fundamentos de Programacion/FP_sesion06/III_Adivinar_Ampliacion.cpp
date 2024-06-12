/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 22: el programa crea una incognita que esté entre MAX y MIN,
	va leyendo valores y dice si el valor es menor o mayor que la incognita. 
	Cuando se haya acabado el juego será porque se ha introducido el valor del
	terminador o porque se ha adivinado la incognita. Para mostrarlo se 
	utilizará la función Acaba_el_juego.
	El juego se volveráa iniciar hasta que el usuario responda 'n' o 'N' a la 
	pregunta realizada al llamar a la funcion LeeOpcion2Alternativas.
*/

#include<iostream> //inclusion de recursos de E/S
#include<ctime>
#include <cstdlib> //inclusion numero aleatorio

using namespace std;

void Acaba_el_juego (int valor, int TERMINADOR){
	
	if (valor == TERMINADOR){
		
		cout<< endl;
		cout<< " Abandonaste el juego.";
		cout<< endl;
		
	}else{
		
		cout<< endl;
		cout<< " ¡Has acertado!";
		cout<< endl;
	}
}

bool LeeOpcion2Alternativas(){
	
	char respuesta;
	
	do{
		cout<<endl;
		cout<< " ¿Desea volver a iniciar el juego? ";
		cin>>respuesta;
		
	}while(respuesta != 'S' && respuesta != 's' && respuesta != 'n' 
		&& respuesta != 'N');
	
	bool seguir_jugando = (respuesta == 's') || (respuesta == 'S');
	
	return seguir_jugando;
}

int main(){
	
	//establecemos el máximo y el mínimo de la incógnita
	
	const int MIN = 1;
	const int MAX = 10;
	const int NUM_VALORES = MAX-MIN +1;
	
	time_t t;
	srand(time(&t));
	
	int valor_jugador;
	const int TERMINADOR = 0;
	string respuesta;
	
	bool seguir_jugando;
	
	do{ //bucle principal
	
		cout<< endl;
		cout<< " Cuando se quiera abandonar el juego, introduzca |0|"<< endl;
	
		//se va a pedir que el usuario introduzca el dato. En caso de que el 
		//dato no se adecue a los requisitos pedidos, se volverá a pedir de 
		//nuevo.
	
		//bucle secuandario para pedir el primer numero correctamente
	
		bool datos_ok; 
	
		do{
		
		cout<< " Introduzca un numero entre 1 y 10: ";
		cin>> valor_jugador;		
		
		datos_ok = 
		(valor_jugador>=MIN && valor_jugador<=MAX)||(valor_jugador==TERMINADOR);
		
		}while(!datos_ok);
	
		//calculos
	
		int incognita = (rand()%NUM_VALORES) + MIN;	
	
		//bucle secuandario para mostrar si el valor_jugador es mayor o menor 
		//que la incógnita
	
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
		
		Acaba_el_juego(valor_jugador, TERMINADOR);//si el bucle anterior ha  
						 						  //parado es porque va a 
												  //finalizar el juego.
		
		cout<< " La incognita era: " << incognita;
	
		seguir_jugando = LeeOpcion2Alternativas();//llamar a la función 
												  //para que pregunte si 
								  				  //se quiere seguir jugando.
	
	}while(seguir_jugando);
	
	return 0;
}
