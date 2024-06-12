/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 28: El programa leerá una letra mayuscula que corresponde con un 
	numero en la tabla ASCII y a este numero se le sumará la clave. Para hacer 
	la rotacion utilizaremos el resto de la division del numero entre el
	intervalo [65,90], para poder sumarselo a 65. Finalmente se mostrará el 
	numero final como un caracter.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main() {
	
	int clave;
	char letra_mayuscula;
	const int letra_a = 65;
	const int letra_z = 90;
	
	//entrada de datos
	
	cout<< endl << " Introduzca una letra mayuscula: ";
	cin>> letra_mayuscula;
	
	cout<< " Introduzca una clave: ";
	cin>> clave;
	
	//calculos
	
	const int diferencia = letra_z - letra_a;
	
	letra_mayuscula = letra_mayuscula + clave;
	letra_mayuscula = (letra_mayuscula - letra_a)%(diferencia+1);
	letra_mayuscula = letra_mayuscula + letra_a;
	
	//salida
	
	cout<< endl;
	cout<< " El caracter codificado es: " << letra_mayuscula << endl << endl;
	
	return{0};
}
