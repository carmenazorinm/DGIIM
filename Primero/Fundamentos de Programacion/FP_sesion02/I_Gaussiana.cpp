/* FUNDAMENTOS DE LA PROGRAMACION

	Carmen Azorín Martí Grupo 2,2

	Ejercicio 24
	
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	double mu;
	double s;
	double x;
	double exponente;
	double pi = asin(0.5)*6;
	double e = 2.71828;
	double fdex;
	
	//entrada de datos
	
	cout<< "Introduce un valor de abscisas x: ";
	cin>> x;
	cout<< endl;
	
	cout<< "Introduce un valor para µ: ";
	cin>> mu;
	cout<< endl;
	
	cout<< "Introduce un valor para s: ";
	cin>> s;
	cout<< endl;
	
	//calculos
	
	exponente = -0.5 * pow(((x-mu)/s),2);
	
	fdex = (1/(s*sqrt(2*pi)))*pow(e,exponente);
	
	//salida
	
	cout<< "El valor que toma la función en x es: "<< fdex << endl << endl;
	
	return(0);
}
