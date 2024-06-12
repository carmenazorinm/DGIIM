/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 26: el programa lee un entero de tres digitos y separa los
	digitos por dos espacios.
*/

#include <iostream> //inclusion de recursos de E/S
#include <string> 

using namespace std;


int main(){
	
	string numero_cadena;
	int numero;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca un numero de tres digitos: ";
	cin>> numero_cadena;
	cout<< endl;
	
	//calculos
	
	numero = stoi(numero_cadena);
	
	if (((numero>=100)&&(numero<=999)) || ((numero>= -999)&&(numero<=-100))){
	
	int centenas = numero/100;
	int decenas = (numero - centenas*100)/10;
	int unidades = (numero - (centenas*100 + decenas*10));
	
	//salida
	
	cout<< " " << centenas << "  " << decenas << "  " << unidades;
	cout<<endl << endl;
	
	}
	
	else {
		
		cout<< " El numero introducido no tiene 3 cifras.";
		cout<< endl << endl;
	}

	return 0;
}
