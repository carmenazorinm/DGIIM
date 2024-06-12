/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 13: el programa leerá un numero decimal y el numero de decimales
	a los que quiere que sea redondeado. Para hacer el redondeo se irá a una
	función redondeo que calculará el redondeo mediante un cálculo en el que
	se utilizará la función potencia.

*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

double potencia(double x, int n){
	
	if(n<0) //si la potencia es negativa, se tiene que multiplicar por el 
		x = 1/x;	      //inverso de la base.
	
	const double X = x; //para guardar el valor de la base.
	
	if(n==0) //si el numero se va a elevar a 0, siempre es 1.
		x = 1;
	
	for(int i=1; i<abs(n); i++){
		
		x = x*X;
	}
	
	return x;
}

double redondeo (double x, int n){
	
	double aux = x*potencia(10,n);
	double resultado;
	
	if((aux-floor(aux))>=0.5)
		aux = floor(aux)+1;
	else
		aux = floor(aux);
		
	n = -1*n;
	resultado = aux*potencia(10,n);
	
	return resultado;
}

int main(){
	
	double numero;
	int numero_decimales;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Escriba el numero que se quiere redondear: ";
	cin>> numero;
	
	do{
		cout<< " Escriba a la cifra decimal a la que se quiere redondear: ";
		cin>> numero_decimales;
	}while(numero_decimales < 0);
	
	//salida
	
	cout<< endl;
	cout<< " El numero redondeado es: "<< redondeo(numero, numero_decimales);
	cout<< endl << endl;
	
	return 0;
}
