/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 30: el programa leer� un capital inicial y un inter�s. Con la 
	formula del interes propuesta por el banco, el programa dir� cuantos a�os
	debe reinvertirse el dinero para poder duplicar la cifra inicial. 
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	double capital_inicial;
	double interes;
	
	//entrada de datos 
	
	do{

	cout<< endl;
	cout<< " Introduzca un valor para el capital: ";
	cin>> capital_inicial;
	
	}while(capital_inicial<0);
	
	do{
		
	cout<< " Introduzca un valor para el inter�s entre 0 y 100: ";
	cin>>interes;
	
	}while((interes<=0)||(interes>100));
	
	//calculos
	
	double total = capital_inicial;
	int anios = 0;
	
	while(total <= (capital_inicial*2)){
	
	double interes_calculado = total*(interes/100);
	total = total + interes_calculado;
	
	anios++;

	}
	
	//salida
	
	cout<< endl;
	cout<< " Se tardan " << anios << " a�os en duplicar ";
	cout<< capital_inicial<< " euros." << endl;
	cout<< " Se queda un total de "<<total<< " euros";
	cout<< endl << endl;
	

	return 0;
}
