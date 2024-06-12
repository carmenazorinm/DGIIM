/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 25: el programa va a leer un literal de caracter y va a guardar su
	correspondiente numero de la tabla ASCII. A este numero se le suma la 
	equivalencia y el resultado ser� el numero que le corresponde a la letra 
	minuscula en la tabla ASCII. Por eso, a la hora de mostrar la variable 
	letra_minuscula pondremos que se comporte como un caracter. 
*/

#include<iostream> //inclusi�n de recursos de E/S

using namespace std;

int main(){ //funcion principal
	
	char letra_mayuscula; 
	char letra_minuscula;
	const int equivalencia = 32; //por la tabla de c�digo ASCII sabemos que la 
	                             //diferencia entre la A (65) y la a (97) es 32
	                           
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca una letra mayuscula: ";
	cin>> letra_mayuscula;
	
	//calculos
	
	letra_minuscula = equivalencia + letra_mayuscula;
	
	//salida
	
	cout<< endl;
	cout<< " El caracter en minuscula es: " << letra_minuscula;
	cout << endl << endl;
	
	return{0};
}
