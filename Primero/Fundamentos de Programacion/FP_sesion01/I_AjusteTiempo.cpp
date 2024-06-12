/* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 18: Leed desde teclado tres variables correspondientes a un n�mero
	de horas, minutos y segundos, respectivamente. Dise�ar un algoritmo que 
	calcule las horas, minutos y segundos dentro de su rango correspondiente. 
	Por ejemplo, dadas 10 horas, 119minutos y 280 segundos, deber�a dar como 
	resultado 12 horas, 3 minutos y 40 segundos. En el caso de que nos salgan 
	m�s de 24 horas, daremos tambi�n los d�as correspondientes (pero ya no 
	pasamos a ver los meses, a�os, etc). Como consejo, utilizad los operadores: 
		/ (representa la divisi�n entera cuando los dosargumentos son enteros) 
		y % (representa el resto de la divisi�n entera).
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
	
	cout<< endl << "Introduzca un n�mero de horas: ";
	cin>> horas;
	cout<< endl;
	
	cout<< "Introduzca un n�mero de minutos: ";
	cin>> minutos;
	cout<< endl;
	
	cout<< "Introduzca un n�mero de segundos: ";
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
