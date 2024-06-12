/* FUNDAMENTOS DE LA PROGRAMACIÓN
	
	Carmen Azorín Martí. Grupo 2,2.
	
	Ejercicio 14: Escriba un programa que lea un distancia en millas (como un 
	real) y muestre la cantidad equivalente en kilómetros. A continuación leerá 
	una distancia en kilómetros (como un real) y mostrará la cantidad 
	equivalente en millas. Debe tener en cuenta que 1 milla equivale a 1.609 
	kilómetros.
*/

#include<iostream> //inclusión de los recursos pra E/S
#include<cmath> //inclusión de los recursos matemáticos

using namespace std;

int main() //función principal
{
	double millas; 
	double kilometros;
	double equivalencia = 1.609;
	
	//entrada de datos
	
	cout<< endl << "Introduzca una distancia en millas: ";
	cin>> millas;
	cout<< endl;
	
	//calculos
	
	kilometros = equivalencia/millas; 
	
	//salida
	
	cout<< millas << " millas equivalen a " << kilometros << " kilometros";
	cout << endl << endl;
	
	//entrada de datos
	
	cout<< "Introduzca una distancia en kilómetros: ";
	cin>> kilometros;
	cout<< endl;
	
	//calculos
	
	millas = equivalencia * kilometros;
	
	//salida
	
	cout<< kilometros << " kilometros equivalen a " <<millas << " millas";
	cout << endl << endl;
	
	return(0); 
}
