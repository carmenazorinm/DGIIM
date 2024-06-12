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
	
	cout<< "Introduzca la velocidad en km/h: ";
	cin>> kilometros;
	cout<< endl;
	
	//calculos
	
	segundos = 3600/kilometros;
	minutos = segundos/60;
	segundos = segundos%60;
	
	//salida
	
	cout<< "El atleta tiene un ritmo de " << minutos << " minutos y ";
	cout<< segundos << " segundos por kilometro."<< endl << endl;
	
	return(0);

}
