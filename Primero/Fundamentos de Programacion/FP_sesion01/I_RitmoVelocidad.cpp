* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 20: En atletismo se expresa la rapidez de un atleta en términos de
	ritmo (minutos y segundos por kilómetro) más que en unidades de velocidad 
	(kilómetros por hora).
	Escribid dos programas para convertir entre estas dos medidas:
		a) El primero leerá el ritmo (minutos y segundos, por separado) y
		mostrará la velocidad (kilómetros por hora).
		b) El segundo leerá la velocidad (kilómetros por hora) y mostrará el 
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
	
	cout<< endl<< "Introduzca los minutos tardados en hacer un kilómetro: ";
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
