/* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 18: Leed desde teclado tres variables correspondientes a un número
	de horas, minutos y segundos, respectivamente. Diseñar un algoritmo que 
	calcule las horas, minutos y segundos dentro de su rango correspondiente. 
	Por ejemplo, dadas 10 horas, 119minutos y 280 segundos, debería dar como 
	resultado 12 horas, 3 minutos y 40 segundos. En el caso de que nos salgan 
	más de 24 horas, daremos también los días correspondientes (pero ya no 
	pasamos a ver los meses, años, etc). Como consejo, utilizad los operadores: 
		/ (representa la división entera cuando los dosargumentos son enteros) 
		y % (representa el resto de la división entera).
*/

#include<iostream> //inclusion recursos de E/S
#include<cmath> //inclusion recursos matematicos

using namespace std;

int main() //funcion principal
{
	int segundos;
	int minutos;
	int horas;
	int dias;
	
	//entrada de datos
	
	cout<< endl << "Introduzca un número de horas: ";
	cin>> horas;
	cout<< endl;
	
	cout<< "Introduzca un número de minutos: ";
	cin>> minutos;
	cout<< endl;
	
	cout<< "Introduzca un número de segundos: ";
	cin>> segundos;
	cout<< endl;
	
	//calculos
	
	minutos = minutos + segundos/60;
	segundos = segundos%60;
	
	horas = horas + minutos/60;
	minutos = minutos%60;
	
	dias = horas/24;
	horas = horas%24;
	
	//salida
	
	cout<< "Usted ha introducido un total de " << segundos << " segundos, ";
	cout<< minutos << " minutos, " << horas << " horas y " << dias << " dias";
	cout<< endl << endl;

}
