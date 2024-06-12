/* FUNDAMENTOS DE LA PROGRAMACI�N
	
	Carmen Azor�n Mart�. Grupo 2,2.
	
	Ejercicio 14: Escriba un programa que lea un distancia en millas (como un 
	real) y muestre la cantidad equivalente en kil�metros. A continuaci�n leer� 
	una distancia en kil�metros (como un real) y mostrar� la cantidad 
	equivalente en millas. Debe tener en cuenta que 1 milla equivale a 1.609 
	kil�metros.
*/

#include<iostream> //inclusi�n de los recursos pra E/S
#include<cmath> //inclusi�n de los recursos matem�ticos

using namespace std;

int main() //funci�n principal
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
	
	cout<< "Introduzca una distancia en kil�metros: ";
	cin>> kilometros;
	cout<< endl;
	
	//calculos
	
	millas = equivalencia * kilometros;
	
	//salida
	
	cout<< kilometros << " kilometros equivalen a " <<millas << " millas";
	cout << endl << endl;
	
	return(0); 
}
