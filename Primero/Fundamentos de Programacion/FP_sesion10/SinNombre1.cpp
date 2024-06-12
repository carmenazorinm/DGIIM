#include<iostream>
#include<string>
#include <iomanip>

using namespace std;

bool ComprobarQueEsReal (string cadena){
	
	int j = 0;
	bool es_real = true;
	
	if(cadena.at(0) == '+' || cadena.at(0) == '-')
		j++;
	
	while(es_real && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_real = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == '.';
					
		j++;
	}
		
	return es_real; //true si es un positivo y false si no lo es.	
}

double LeeReal (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		getline( cin, respuesta);
		es_valido = ComprobarQueEsReal(respuesta);
	}while(!es_valido);
	
	double real = stod(respuesta); //convierte el string respuesta en un int
	return real;
}

int main(){
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);
	
	double caca;
	caca = LeeReal(" Introduzca caca ");
	cout<<setw(5)<<caca;
}
