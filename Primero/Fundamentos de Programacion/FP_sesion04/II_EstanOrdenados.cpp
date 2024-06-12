/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 3: el programa lee 3 numeros y muestra si están ordenados o no.
*/

#include<iostream> //inclusion de recursos E/S

using namespace std;

int main(){
	
	int numero1;
	int numero2;
	int numero3;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca un numero: ";
	cin>> numero1;
	cout<< " Introduzca otro numero: ";
	cin>> numero2;
	cout<< " Introduzca otro numero: ";
	cin>> numero3;
	
	//calculos
	
	bool estan_ordenados = (((numero1 < numero2) && (numero2 < numero3)) 
						|| ((numero1 > numero2) && (numero2 > numero3)));
						
	if (estan_ordenados) {
		
		cout<< endl;
		cout<< " Estan ordenados" << endl << endl;
		
	}
	
	else {
		
		cout<< endl;
		cout<< " No estan ordenados" << endl << endl;
		
	}
	
	return 0;
}
