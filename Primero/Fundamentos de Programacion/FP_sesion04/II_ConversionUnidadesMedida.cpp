/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 18: el programa lee un valor y lo debe transformar de una unidad
	de medida a otra. Debe encontrar todos los fallos del usuario al introducir
	los datos e informar de que existen fallos, en caso de que los haya.
	
*/

#include<iostream> //inclusion de recursos de E/S
#include<string> //inclusionde recursos matematicos

using namespace std;

int main(){
	
	double numero_inicial;
	string unidad_inicial;
	string unidad_final;
	char a;
	
	const double MM_A_M = 0.001;
	const double CM_A_M = 0.01;
	const double KM_A_M = 1000; 
	const double M_A_MM = 1000;
	const double M_A_CM = 100;
	const double M_A_KM = 0.001;
	
	//entrada de datos
	
	cout<< endl << " > ";
	cin>> numero_inicial;
	cin>> unidad_inicial;
	cin>> a;
	cin>> unidad_final;
	
	//calculos
	
	bool unidad_inicial_valida = 
					((unidad_inicial == "mm") || (unidad_inicial == "cm") ||
					(unidad_inicial == "m") || (unidad_inicial == "km"));
					
	bool unidad_final_valida = 
					((unidad_final == "mm") || (unidad_final == "cm") ||
					(unidad_final == "m") || (unidad_final == "km"));
					
	bool caracter_a_valido = (a =='a');
	
	if (unidad_inicial_valida + unidad_final_valida + caracter_a_valido == 3){
		
		double numero = numero_inicial;
		
		if (unidad_inicial== "mm"){
			
			numero = numero*MM_A_M;
		}
		if (unidad_inicial == "cm"){
			
			numero = numero*CM_A_M;
		}
		if (unidad_inicial == "km"){
			
			numero = numero*KM_A_M;
		}
		if (unidad_final == "mm"){
			
			numero = numero*M_A_MM;
		}
		if (unidad_final == "cm"){
			
			numero = numero*M_A_CM;
		}
		if (unidad_final == "km"){
			
			numero = numero*M_A_KM;
		}
		
		cout<< " "<< numero_inicial << " "<< unidad_inicial <<" = "<< numero;
		cout<< " "<< unidad_final; 
	}
	else{
		
		cout<< endl;
		cout<< " Se ha producido un error en la lectura de datos.";
	} 
	
	cout<< endl << endl;
	
	return 0;	
}
