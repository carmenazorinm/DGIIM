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
	
	do{
		
		cout<< endl;
		cout<< " Introduzca un numero positivo: ";
		cin>> numero_cadena;
		cout<< endl;
		
		numero = stoi(numero_cadena);
	
	}while (numero<0);
	
	//calculos
	
	int centenas = numero/100;
	int decenas = (numero - centenas*100)/10;
	int unidades = (numero - (centenas*100 + decenas*10));
	
	const string SEPARADOR = "|"; 
	string cad_resultado = " " + SEPARADOR + to_string(centenas) + SEPARADOR +
						   to_string(decenas) + SEPARADOR + 
	                       to_string(unidades) + SEPARADOR;
	
	
	//salida
	
	cout<< cad_resultado;
	cout<<endl << endl;

	return 0;
}
