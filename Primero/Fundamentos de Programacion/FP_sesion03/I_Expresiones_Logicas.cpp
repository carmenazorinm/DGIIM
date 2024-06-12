/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 32: 
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	//Programa 1
	
	char letra;
	bool es_mayuscula;
	
	//entrada de datos
	
	cout<< endl << " Introduce una letra: ";
	cin>> letra;
	
	//calculos
	
	es_mayuscula = 65 <= letra &&  letra <= 90;
	
	//salidas
	
	cout<<  " La letra " << letra<< " es mayuscula? " << es_mayuscula;
	cout << endl << endl;
	
/******************************************************************************
*******************************************************************************
*******************************************************************************/

	//Programa 2
	
	int edad;
	bool poblacion_activa;
	
	//entrada de datos
	
	cout << " Introduce una edad: ";
	cin>> edad;
	
	//calculos
	
	poblacion_activa = edad>=18 && edad<67;
	
	//salidas
	
	cout<<  " La edad " << edad<< " esta en la poblacion activa? ";
	cout<< poblacion_activa;
	cout << endl << endl;
	
/******************************************************************************
*******************************************************************************
*******************************************************************************/

	//Programa 3
	
	int ano;
	bool es_bisiesto;
	
	//entrada de datos 
	
	cout<< " Introduce un año: ";
	cin>> ano;
	
	//calculos
	
	es_bisiesto = ((ano%4 == 0) && (ano%100 != 0)) || (ano%400 == 0);
	
	//salidas
	
	cout<< " El año " << ano << " es bisiesto? " << es_bisiesto;
	cout << endl << endl;
	
/******************************************************************************
*******************************************************************************
*******************************************************************************/

	//Programa 4
	
	int limite;
	double distancia;
	bool es_menor;
	
	//entrada de datos
	
	cout<< " Introduce un limite: ";
	cin>> limite;
	//cout<< endl;
	
	cout<< " Introduce una distancia: ";
	cin>> distancia;
	
	//calculos
	
	es_menor = distancia<limite;
	
	//salidas
	
	cout<< " La distancia " << distancia << " es menor que el limite ";
	cout<< limite << "? " << es_menor;
	cout << endl << endl;
	
/******************************************************************************
*******************************************************************************
*******************************************************************************/

	//Programa 5
	
	int numero1;
	int numero2;
	bool mayor_que;
	bool menor_que;
	bool igual;
	
	//entrada de datos
	
	cout<< " Introduce un numero: ";
	cin>> numero1;
	
	cout<< " Introduce otro numero: ";
	cin>> numero2;
	
	//calculos
	
	mayor_que = numero1 > numero2;
	menor_que = numero1 < numero2;
	igual = numero1 == numero2;
	
	//salidas
	
	cout<< endl;
	cout<< " " << numero1 << " es mayor que " << numero2 << ": " << mayor_que;
	cout<< endl;
	cout<< " " << numero1 << " es menor que " << numero2 << ": " << menor_que;
	cout<< endl;
	cout<< " " << numero1 << " es igual que " << numero2 << ": " << igual;
	cout<< endl;
	cout<< endl;
	
	return{0};
}
