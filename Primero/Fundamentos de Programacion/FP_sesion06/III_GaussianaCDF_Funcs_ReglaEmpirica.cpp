/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 30: el programa lee los parámetros de una distribucion gaussiana
	(esperanza, desviación tipica y x de abscisas), y calcular mediante la 
	funcion calcular_g_de_x el valor de la gaussiana, mediante la funcion
	calcular_cdf calcula CDF desde µ - 3s y con la funcion 
	calcular_cdf_2 calcula CDF a partir de la fórmula.
*/

#include <iostream>
#include <cmath>

using namespace std;

double valor_absoluto(double numero){
	
	if(numero<0)
		numero = (-1)*numero;
		
	return numero;
}

double calcular_g_de_x(double esperanza, double desviacion, double x){
	
	double y; 
	const double PI = 6*asin(0.5);

	y = exp (-0.5 * pow ((x - esperanza)/desviacion, 2)) / 
		(desviacion * sqrt(2*PI));
		
	return y;
}

double calcular_cdf(double esperanza, double desviacion){
	
	const double PI = 6*asin(0.5);

	double valor_inicial = esperanza-(3*desviacion);
	double valor_final = esperanza+(3*desviacion);
	double const SALTO = 0.25;
	double cdf = 0;
	double gaussiana;
	
	while(valor_final>=valor_inicial){
		
		double area = 
				calcular_g_de_x(esperanza, desviacion, valor_inicial)*SALTO;
		cdf=cdf+area;
		valor_inicial = valor_inicial + SALTO;
	}
	
	return cdf;
}

double calcular_cdf_2(double esperanza, double desviacion, double x){
	
	double esperanza_estandar = 0;
	double desviacion_estandar = 1;
	
	const double B0 = 0.2316419;
	const double B1 = 0.319381530;
	const double B2 = -0.356563782;
	const double B3 =  1.781477937;
	const double B4 = -1.821255978;
	const double B5 = 1.330274429;
	
	double cdf;
	double w;
	double x_estandarizada = valor_absoluto((x-esperanza)/desviacion);
	const double T = 1/(1+B0*valor_absoluto(x));
	
	w = (1-
	calcular_g_de_x(esperanza_estandar, desviacion_estandar, x_estandarizada))
	*(B1*T+B2*T*T+B3*T*T*T+B4*T*T*T*T+B5*T*T*T*T*T);
	
	if(x>=0)
		cdf = w;
	else
		cdf = 1-w;
	
	return cdf;	
}

int main(){
	
	const double PI = 6 * asin(0.5);
	double esperanza, desviacion, x;
   
	// Entrada 
   
   	cout << endl;
	cout << " Introduzca el valor de la esperanza: ";
	cin >> esperanza;

	do{
		cout << " Introduzca el valor de la desviacion: ";
		cin >> desviacion;
	}while(desviacion<=0);
	
	cout<< " Introduzca el valor de x: ";
	cin>>x;
	
	//calculos
	
	cout<<endl;
	cout<< " g("<<x<<") = ";
	cout<< calcular_g_de_x(esperanza, desviacion,x);
	cout<<endl;
	cout<< " 1. CDF("<<x<<") = ";
	cout<< calcular_cdf(esperanza, desviacion);
	cout<<endl;
	cout<< " 2. CDF("<<x<<") = ";
	cout<< calcular_cdf_2(esperanza, desviacion, x);
	
	return 0;
}
