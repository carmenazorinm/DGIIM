/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 30: el programa leerá un capital inicial y un interés. Con la 
	formula del interes propuesta por el banco, el programa dirá cuantos años
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
		
	cout<< " Introduzca un valor para el interés entre 0 y 100: ";
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
	cout<< " Se tardan " << anios << " años en duplicar ";
	cout<< capital_inicial<< " euros." << endl;
	cout<< " Se queda un total de "<<total<< " euros";
	cout<< endl << endl;
	

	return 0;
}
