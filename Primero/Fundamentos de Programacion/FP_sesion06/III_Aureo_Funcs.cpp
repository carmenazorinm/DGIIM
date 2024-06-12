/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 6: el programa lee la maxima diferencia que puede haber entre
	el numero aureo y la aproximación. A partir de ahi, va pasando por cada 
	valor de an, que es fn_mas_1/fn, hasta encontrar aquel fn de posición n
	tal que, el numero aureo - an <= diferencia. 

*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

double valor_absoluto(double numero){
	
	if(numero<0)
		numero = (-1)*numero;
		
	return numero;
}

//la siguiente funcion lee un numero y devuelve el siguiente numero de la 
//sucesión de fibonacci. Para ello va calculando todos los numeros de la 
//sucesión hasta llegar a aquel que sea mayor que el numero leído.

int siguiente_numero_fibonacci(int numero){
	
	int numero1 = 1;
	int numero2 = 1;
	int siguiente_numero;
	
	do{
		siguiente_numero = numero1 + numero2;
		numero1 = numero2;
		numero2 = siguiente_numero;
	}while(numero>=siguiente_numero);
	
	return siguiente_numero;
}

int main(){
	
	const double NUMERO_AUREO = (1+sqrt(5))/2;
	double diferencia;
	
	//entrada de datos
	
	cout<< endl;
	
	do{
	cout<< " Introduzca la diferencia";
	cout<<" entre la aproximacion y el numero aureo: ";
	cin>>diferencia;
	}while(diferencia<=0);
	
	//calculos
	
	int posicion = 1; //empezamos por la posicion 1, porque el numero 1 se  
				      //repite dos veces.
	double fn = 1.0;
	double fn_mas_1;
	double an;
	
	do{
		fn_mas_1 = siguiente_numero_fibonacci(fn);
		posicion++;
		an = fn_mas_1/fn;
		fn = fn_mas_1;
	}while(diferencia < valor_absoluto(NUMERO_AUREO-an));
	
	//salida
	
	cout<< " La posicion del numero presente en la serie de fibonacci es: ";
	cout<< posicion;
	cout<<endl<<endl;
	
	return 0;	
}

