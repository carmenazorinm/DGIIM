/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 52: el programa lee un tope y se debe hacer el sumatorio de la 
	formula del matemático indio Madhava de Sangamagrama tantas veces como diga
	el tope. Así conseguiremos aproximar pi.
*/

#include<iostream> //inclusion de recursos de E/S
#include <cmath> //inclusion de recursos matematicos
#include<iomanip>

using namespace std;

int main(){
	
	cout.setf(ios::showpoint);
	
	int tope;
	double pi_final;
	double pi = 0;
	int suma = 0;
	double potencia;
	const double BASE = 1/sqrt(3);
	int numero_decimales;

	int signo_uno;
	
	//entrada de datos 
	
	do{
		cout<< endl;
		cout<< " Introduzca un tope: ";
		cin>>tope;
		
	}while (tope<1 || tope>100000);
	
	do{
		
		cout<<" Introduzca el numero de decimales que necesita: ";
		cin>>numero_decimales;
	
	}while (numero_decimales<0);
	
	//calculos
	
	for (int i=0; i<=tope; i++){
		
		double base = 1/sqrt(3);
		signo_uno = 1;
		potencia = 2*i+1;
		
		for(int x=1; x<potencia; x++){
			
			base = base*BASE;
		}
		for(int n=0; n<i%2 ; n++){
			
			signo_uno = -1;
		}
		pi = pi + ((signo_uno*base)/potencia);
		suma++;
	}
	pi_final = pi*6;
	
	//salida
	
	cout<< endl;
	cout<<" La aproximacion de pi es ";
	cout<<setprecision(numero_decimales +1) << pi_final;
	cout<<endl << endl;

	return 0;
}
