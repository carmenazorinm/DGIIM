* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 20: En atletismo se expresa la rapidez de un atleta en t�rminos de
	ritmo (minutos y segundos por kil�metro) m�s que en unidades de velocidad 
	(kil�metros por hora).
	Escribid dos programas para convertir entre estas dos medidas:
		a) El primero leer� el ritmo (minutos y segundos, por separado) y
		mostrar� la velocidad (kil�metros por hora).
		b) El segundo leer� la velocidad (kil�metros por hora) y mostrar� el 
		ritmo (minutos y segundos).
*/

#include <iostream> //inclusion de recursos de E/S
#include <cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	int minutos;
	int segundos;
	double kilometros;
	
	//entrada de datos
	
	cout<< endl<< "Introduzca los minutos tardados en hacer un kil�metro: ";
	cin>> minutos;
	cout<< endl;
	
	cout<< "Introduzca los segundos tardados en hacer un kilometro: ";
	cin>> segundos;
	cout<< endl;
	
	//calculos
	
	segundos = segundos + minutos*60;
	kilometros = 3600.0/segundos;
	
	//salida
	
	cout<< "El atleta corre con una velocidad de " << kilometros << " km/h";
	cout<< endl << endl;
	
	return(0);

}
