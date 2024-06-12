/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 35: el programa recibirá un numero del que tiene que averiguar el 
	numero de bits necesarios para representarlo en binario. Sabemos que con n
	bits, se pueden representar 2^n numeros, contando el 0. Por eso, el
	programa sumara 1 unidad al numero de bits necesarios. Así, al truncarlo, 
	dará el numero exacto de bits.
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion recursos matematicos

using namespace std;

int main(){
	
	int n;
	int potencia;
	int resultado;
	
	//entrada de datos
	
	cout<< endl << " Introduce un entero positivo: ";
	cin>> n;
	cout<< endl;
	
	//calculos
	
	bool numero_natural = (n>=0);
	
	if (numero_natural) {
	
		bool distinto_cero = (n!=0);
		potencia = log2(n);
		resultado = (distinto_cero*potencia) + 1;
	
		//salidas
	
		cout<< " Se necesitan " << resultado << " bits para representar " << n;
		cout<< endl << endl;
	}
	
	else {
		
		cout<< " El numero escrito no es ni un entero positivo ni el 0.";
	}
	
	return 0;
}
