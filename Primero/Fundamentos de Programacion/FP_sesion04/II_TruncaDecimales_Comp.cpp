/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 36: el programa va a separar la parte entera de r y la parte 
	decimal. La parte decimal que sobra de r, la abandonar� pasando a entero
	los decimales �tiles de r. Volveremos a pasar a decimal �stos decimales 
	�tiles y los sumaremos a la parte entera de r. Finalmente, el programa
	mostrar� �nicamente los decimales de r correspondientes.
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos

using namespace std;

int main(){
	
	double r;
	int r_entero;
	double solo_decimales;
	int solo_decimales_entero;
	int n;
	double resultado;
	
	//entrada de datos
	
	cout<< endl << " Introduce un numero real a truncar: ";
	cin>> r;
	
	cout<< " Introduce el numero de digitos en la parte decimal: ";
	cin>> n;
	
	//calculos
	
	if (n>=0){
	
	r_entero = r; //nos quedamos con la parte entera de r
	
	solo_decimales = r - r_entero; //nos quedamos solo con la parte decimal de r
	
	solo_decimales = solo_decimales * pow(10,n); //pasamos a entero la parte 
	                                             //decimal con la que queremos 
												 //quedarnos
												 
	solo_decimales_entero = solo_decimales; //borramos el resto de decimales que 
	                                    	//no queremos
	                                    	
	solo_decimales = solo_decimales_entero * pow(10,-n); //volvemos a pasar a 
														 //decimal
														 
	resultado = solo_decimales + r_entero; //sumamos los decimales a la parte 
										   //entera de r
	
	//salidas
	
	cout<< endl << " El numero truncado es: " << resultado << endl << endl;
	
	}
	else{
		
		cout<< " No es posible truncar con ese numero de digitos en";
		cout<< " la parte decimal"<< endl << endl;
	}
	
	return{0};
	
}
