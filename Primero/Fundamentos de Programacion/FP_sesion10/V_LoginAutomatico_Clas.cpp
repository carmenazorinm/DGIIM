/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 14: 
	
*/

#include<iostream>
#include<string>

using namespace std;

class Login{
	private:
		int num_caracteres_a_coger;
	public:
		Login (int n): //PRE: el numero debe ser un entero positivo
			num_caracteres_a_coger (n)
			{ }
		
		string Codifica(string nombre_completo){
			
		}
	
	private:
		string CogerNLetras(string nombre){
			int total_letras = nombre.length();
			int posicion = 0;
			string cadena = "";
			while(posicion<num_caracteres_a_coger && posicion<total_letras){
				char caracter_posicion = 	
			}
		}
		
		int CalcularNumeroNombres(string nombre){
			int contador_nombres = 1;
			for(int i = 0; i < nombre.length(); i++){
				
			}
		}
};

/*****************************************************************************/
bool ComprobarQueEsPositivo (string cadena){
	
	int j = 0;
	bool es_positivo = true;
	
	if(cadena.at(0) == '+')
		j++;
	
	while(es_positivo && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_positivo = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == ' ';
		j++;
	}
		
	return es_positivo; //true si es un positivo y false si no lo es.	
}

int LeePositivo (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		cin>>respuesta;
		es_valido = ComprobarQueEsPositivo(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}

/*****************************************************************************/

int main(){
	string nombre;
	string numero;
	
	//ENTRADA DE DATOS
	
	cout<< " Introduzca su nombre: ";
	getline(cin, nombre);
	numero = LeePositivo(" Introduzca el maximo de caracteres: ");
	
	//CALCULOS
	
	Login nombre_completo;
	nombre_completo.num_caracteres_a_coger = numero;
	
}
