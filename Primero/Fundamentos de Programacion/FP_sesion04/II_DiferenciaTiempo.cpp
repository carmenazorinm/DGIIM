/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 6:
	
*/

#include<iostream> // inclsuion de recursos de E/S

using namespace std;

int main() //funcion principal
{
	int hora_inicial;
	int minuto_inicial;
	int segundo_inicial;
	
	int hora_final;
	int minuto_final;
	int segundo_final;
	
	int resultado;
	
	//entrada de datos
	
	cout<< endl << " Introduzca la hora inicial: ";
	cin>> hora_inicial;
	cout << " Itroduzca el minuto inicial: ";
	cin>> minuto_inicial;
	cout<< " Introduzca el segundo inicial: ";
	cin>> segundo_inicial;
	cout<< endl;
	
	cout<< " Introduzca la hora final: ";
	cin>> hora_final;
	cout<< " Itroduzca el minuto final: ";
	cin>> minuto_final;
	cout<< " Introduzca el segundo final: ";
	cin>> segundo_final;
	cout<< endl;
	
/******************************************************************************/
 
// Programa 1
 	
 	bool diferente_dia = (hora_final < hora_inicial);
 	
 	if (diferente_dia){
 		
 		cout<< " Los instantes son de días diferentes"<< endl;
 		
 		minuto_inicial = minuto_inicial + hora_inicial*60;
		segundo_inicial = segundo_inicial + minuto_inicial*60;
	
		minuto_final = minuto_final + hora_final*60;
		segundo_final = segundo_final + minuto_final*60;
		
		int dia_a_seg = 24*3600;
		
		resultado = segundo_final + dia_a_seg - segundo_inicial;
 		
 		//salida
 		
 		cout<< " El numero de segundos que hay entre los dos instantes es ";
		cout<< resultado << endl << endl;
	 }
	else{
	
		minuto_inicial = minuto_inicial + hora_inicial*60;
		segundo_inicial = segundo_inicial + minuto_inicial*60;
	
		minuto_final = minuto_final + hora_final*60;
		segundo_final = segundo_final + minuto_final*60;
	
		resultado = segundo_final - segundo_inicial;
	
	//salida
	
	cout<< " El numero de segundos que hay entre los dos instantes es ";
	cout<< resultado << endl << endl;
	
	}
	
/******************************************************************************/
/*
//Programa 2

	const int EQUIVALENCIA_H_SEG = 3600;
	const int EQUIVALENCIA_MIN_SEG = 60;

 	bool diferente_dia = (hora_final < hora_inicial);
 	
 	if (diferente_dia){
 		
 		cout<< " Los instantes son de días diferentes"<< endl;
 		
 		hora_final = (24 + hora_final - hora_inicial)*EQUIVALENCIA_H_SEG;
 		minuto_final = (minuto_final - minuto_inicial)*EQUIVALENCIA_MIN_SEG;
 		segundo_final = segundo_final - segundo_inicial;
 		
 		resultado = hora_final + minuto_final + segundo_final;
 		
 		//salida
 		
 		cout<< " El numero de segundos que hay entre los dos instantes es ";
		cout<< resultado << endl << endl;
 		
	 }
	else{
		
		hora_final = (hora_final - hora_inicial)*EQUIVALENCIA_H_SEG;
		minuto_final = (minuto_final- minuto_inicial)*EQUIVALENCIA_MIN_SEG;
		segundo_final = segundo_final - segundo_inicial;
		
		resultado = hora_final + minuto_final + segundo_final;	
	
		//salida
	
		cout<< " El numero de segundos que hay entre los dos instantes es ";
		cout<< resultado << endl << endl;
	
	}
*/		
	
	return(0);

}
