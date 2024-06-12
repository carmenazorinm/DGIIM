/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 9: El programa leerá una letra mayuscula a la que le sumará una 
	clave para que esta letra inicial quede codificada
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main() {
	
	int clave;
	char letra_mayuscula;
	char letra_codificada;
	
	//entrada de datos
	
	cout<< endl << " Introduzca una letra mayuscula: ";
	cin>> letra_mayuscula;
	
	cout<< " Introduzca una clave: ";
	cin>> clave;
	
	//calculos
	
	letra_codificada = letra_mayuscula + clave;
	
	bool numero_mayor = (letra_codificada > 'Z');
	
	if (numero_mayor)
		
		letra_codificada = letra_codificada - 'Z' + 'A' -1;
		
	bool numero_menor = (letra_codificada < 'A');
	
	if (numero_menor)
			
		letra_codificada = 'Z'- 'A' + letra_codificada +1;
		
	
	//salida
	
	cout<< endl;
	cout<< " El caracter codificado es: " << letra_codificada << endl << endl;
	
	
	return{0};
}
