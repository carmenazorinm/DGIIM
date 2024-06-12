/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 5: este programa pide los kilometros recorridos por un avion y
	los puntoa acumulados en la tarjetade fidelizacion. A partir de ahi, hace 
	un descuento si se recorren mas de 700km y otro descuento si se tienen mas
	de 100 puntos o mas de 200 puntos.
*/

#include<iostream> //inclusion recursos de E/S

using namespace std;

int main(){
	
	const int TARIFA_BASE = 150;
	const double PRECIO_POR_KM = 0.1;
	const int DESDE_TRESCIENTOS = 300;
	const int DESDE_SETECIENTOS = 700;
	int puntos;
	int kilometros;
	double precio;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca el numero de kilometros recorridos: ";
	cin>> kilometros;
	cout<< " Introduzca el l número de puntos de la tarjeta de fidelización: ";
	cin>> puntos;
	
	//calculos
	
	if (kilometros < 0){
		
		cout<< endl;
		cout<< " No se puede calcular una tarifa para esos kilometros.";
		cout<< endl << endl;
	}
	
	if (kilometros >= 0){
	if (kilometros < DESDE_TRESCIENTOS){
		
		kilometros = DESDE_TRESCIENTOS; //para que en la siguiente operacion 
										//kilometros-desde_trescientos = 0
	}
	
	precio = TARIFA_BASE+(PRECIO_POR_KM*(kilometros-DESDE_TRESCIENTOS));
	
	if (kilometros > DESDE_SETECIENTOS){
		
		const double DESCUENTO_2PORCIENTO = 0.2;
		precio = precio - (precio*DESCUENTO_2PORCIENTO);
	}
	
	const int CIEN_PUNTOS = 100;
	const int DOSCIENTOS_PUNTOS = 200;
	
	if (puntos > CIEN_PUNTOS && puntos < DOSCIENTOS_PUNTOS){
		
		const double DESCUENTO_3PORCIENTO = 0.3;
		precio = precio - (precio*DESCUENTO_3PORCIENTO);
	}
	
	else {
		
		if (puntos > DOSCIENTOS_PUNTOS){
		
		const double DESCUENTO_4PORCIENTO = 0.4;
		precio = precio - (precio*DESCUENTO_4PORCIENTO);
		
		}
	}
	
	//salida
	
	cout<< endl;
	cout<< " El precio del vuelo es de " << precio << " euros" << endl << endl;
	
	}
	
	return 0; 
}
