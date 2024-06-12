/* FUNDAMENTOS DE LA PROGRAMACIÓN

	Ejercicio 15: Realizar un programa que nos pida una longitud cualquiera 
	dada en metros. El programa deberá calcular el equivalente de dicha 
	longitud en pulgadas, pies, yardas y millas, y mostrarnos los resultados en 
	pantalla. Para el cálculo, utilice la siguiente tabla de conversión del 
	sistema métrico:
		1 pulgada= 25,4 milímetros 
		1 yarda = 0,9144 metros
		1 pie = 30,48 centímetros 
		1 milla = 1609,344 metros
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	double metros; 
	
	double pulgada;
	double equivalencia_pulgada = 0.0254;
	
	double yarda;
	double equivalencia_yarda = 0.9144;
	
	double pie;
	double equivalencia_pie = 0.3048;
	
	double milla;
	double equivalencia_milla = 1609.344;
	
	//entrada de datos 
	
	cout<< endl << "Introduzca una longitud en metros: ";
	cin>> metros;
	cout<< endl;
	
	//calculos
	
	pulgada = metros / equivalencia_pulgada;
	yarda = metros / equivalencia_yarda;
	pie = metros / equivalencia_pie;
	milla = metros / equivalencia_milla;
	
	//salidas
	
	cout<<metros<< " metros equivalen a " <<pulgada<< " pulgadas" <<endl <<endl;
	cout<< metros << " metros equivalen a " << yarda << " yardas"<< endl <<endl;
	cout<< metros << " metros equivalen a " << pie << " pies" << endl << endl;
	cout<< metros << " metros equivalen a " << milla << " millas" << endl<<endl;
	
	return(0);
}
		
	
