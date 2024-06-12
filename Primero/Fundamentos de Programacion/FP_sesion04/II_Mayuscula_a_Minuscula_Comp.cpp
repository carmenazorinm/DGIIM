/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 25: el programa va a leer un literal de caracter y va a guardar su
	correspondiente numero de la tabla ASCII. A este numero se le suma la 
	equivalencia y el resultado será el numero que le corresponde a la letra 
	minuscula en la tabla ASCII. Por eso, a la hora de mostrar la variable 
	letra_minuscula pondremos que se comporte como un caracter. 
*/

#include<iostream> //inclusión de recursos de E/S

using namespace std;

int main(){ //funcion principal
	
	char letra_mayuscula; 
	char letra_minuscula;
	const int EQUIVALENCIA = 'a'-'A'; 
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca una letra mayuscula: ";
	cin>> letra_mayuscula;
	
	bool es_mayuscula = (letra_mayuscula >= 'A')&&(letra_mayuscula <= 'Z');
	
	if (es_mayuscula) {
		
		//calculos
	
		letra_minuscula = EQUIVALENCIA + letra_mayuscula;
	
		//salida
	
		cout<< endl;
		cout<< " El caracter en minuscula es: " << letra_minuscula;
		cout << endl << endl;
		
	}
	
	else {
		
		//salida 
		
		cout<< endl;
		cout<< " El caracter introducido no es una letra mayuscula.";
		cout<< endl << endl;
	}
	
	return 0;
}
