/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 51: el programa leerá la desviacion tipica, la esperanza y el 
	valor de abscisas x. A continuacion, calculará el area de la funcion 
	Gaussiana, CDF(x).
*/

#include<iostream>
#include<cmath>

using namespace std;

int main(){

	double desviacion_tipica;
	double media;
	double abscisa_x;
	double cdf = 0;
	double funcion_gaussiana;	
	
	const double PI= asin(0.5)*6;
	const double SALTO = 0.0000001;
	
	//Entrada de datos
	
	cout << endl;
	cout <<" Introduce un valor de abscisas x: ";
	cin >> abscisa_x;
	
	cout << " Introduce un valor para la media:  ";
	cin >> media;
	
	do{
		cout <<" Introduce un valor para la desviacion tipica: ";
		cin >> desviacion_tipica;
	
	} while(desviacion_tipica <= 0);

	//Calculos
		
	double valor_inicial = media - 3*desviacion_tipica;
			
	for (double i = valor_inicial; i <= abscisa_x; i = i + SALTO){
		
		double parte_fija = 1 / (desviacion_tipica*(sqrt(2*PI)));
		double parte_variable = pow ((i - media) / desviacion_tipica,2);
		double integral;
		
		funcion_gaussiana = parte_fija*exp((-1.0/2)*parte_variable);
		integral = funcion_gaussiana*SALTO;  
		cdf = cdf + integral;
	}
	
	//Salida
	
	cout << endl;
    cout << " CDF(" << abscisa_x <<") = "<<cdf;
	cout << endl;
	
	return 0;
}


