/* FUNDAMENTOS DE LA PROGRAMACION

	Carmen Azorín Martí Grupo 2,2

	Ejercicio 19: Calcular el número de segundos que hay entre dos instantes del
	mismo día. Cada instante se caracteriza por la hora (entre 0 y 23), minuto 
	(entre 0 y 59) y segundo (entre 0 y 59).
	El programa leerá la hora, minuto y segundo del instante inicial, y la hora,
	minuto y segundo del instante final (supondremos que los valores 
	introducidos son correctos) y mostrará el número de segundos entre ambos 
	instantes.
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	int hora_inicial;
	int minuto_inicial;
	int segundo_inicial;
	
	int hora_final;
	int minuto_final;
	int segundo_final;
	
	int resultado;
	
	//entrada de datos
	
	cout<< endl << "Introduzca la hora inicial: ";
	cin>> hora_inicial;
	cout<< endl << "Itroduzca el minuto inicial: ";
	cin>> minuto_inicial;
	cout<< endl << "Introduzca el segundo inicial: ";
	cin>> segundo_inicial;
	cout<< endl << endl;
	
	cout<< endl << "Introduzca la hora final: ";
	cin>> hora_final;
	cout<< endl << "Itroduzca el minuto final: ";
	cin>> minuto_final;
	cout<< endl << "Introduzca el segundo final: ";
	cin>> segundo_final;
	cout<< endl << endl;
	
	//calculos
	
	minuto_inicial = minuto_inicial + hora_inicial*60;
	segundo_inicial = segundo_inicial + minuto_inicial*60;
	
	minuto_final = minuto_final + hora_final*60;
	segundo_final = segundo_final + minuto_final*60;
	
	resultado = segundo_final - segundo_inicial;
	
	//salida
	
	cout<< "El numero de segundos que hay entre los dos instantes es ";
	cout<< resultado << endl << endl;
	
	return(0);

}
