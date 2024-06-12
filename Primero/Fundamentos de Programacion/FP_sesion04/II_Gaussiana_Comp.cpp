/* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 24: funcion Gaussiana donde el valor de la desviacion tipica debe 
	ser mayor que 0.	
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	double media;
	double desviacion_tipica;
	double x;
	double exponente;
	const double PI = asin(0.5)*6;
	double fdex;
	
	//entrada de datos
	
	cout<< endl;
	cout<< "Introduce un valor de abscisas x: ";
	cin>> x;
	
	cout<< "Introduce un valor para la media: ";
	cin>> media;
	
	cout<< "Introduce un valor para la desviacion tipica: ";
	cin>> desviacion_tipica;
	
	if (desviacion_tipica > 0){
	
		//calculos
	
		exponente = -0.5 * pow(((x-media)/desviacion_tipica),2);
	
		fdex = (1/(desviacion_tipica*sqrt(2*PI)))*exp(exponente);
	
		//salida
	
		cout<< endl;
		cout<< "El valor que toma la función en x es: "<< fdex << endl << endl;
	
	}
	
	else {
		
		//salida
		
		cout<< endl;
		cout<< " La desviacion tipica debe ser mayor que 0.";
		cout<< endl << endl;
	}
	
	return(0);
}
