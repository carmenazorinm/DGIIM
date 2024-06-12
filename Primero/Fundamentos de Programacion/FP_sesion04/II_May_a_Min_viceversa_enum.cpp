/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 21: 
	
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	
	char letra_original;
	char letra_convertida;
	const int EQUIVALENCIA = 'a'-'A';
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca una letra: ";
	cin>> letra_original;
	cout<< endl;
	
	//calculos
	
	enum class TipoCaracter 
				{mayuscula, minuscula, digito, otro};
	
	TipoCaracter tipo;
	
	bool es_mayuscula = ('A'<= letra_original) && (letra_original <='Z');
	bool es_minuscula = ('a'<= letra_original) && (letra_original <= 'z');
	bool es_numero = ('0'<= letra_original) && (letra_original<= '9');
	bool otro = (es_mayuscula + es_minuscula+es_numero)==0;
	
	if(es_mayuscula){
		
		tipo = TipoCaracter::mayuscula;
		letra_convertida = letra_original + EQUIVALENCIA;
	}
	
	if(es_minuscula){
		
		tipo = TipoCaracter::minuscula;
		letra_convertida = letra_original - EQUIVALENCIA;
	}
	
	if(es_numero){
		
		tipo = TipoCaracter::digito;
	}
	
	if (otro){
		
		tipo = TipoCaracter::otro;
	}
	
	switch (tipo){
		
		case (TipoCaracter::mayuscula):
			cout<< " La letra era una mayúscula. Una vez convertida es: ";
			cout<<letra_convertida;
			break;
		
		case(TipoCaracter::minuscula):
			cout<< " La letra era minuscula. Una vez convertida es: ";
			cout<< letra_convertida;
			break;
			
		case(TipoCaracter::digito):
			cout<< " El caracter introducido es un digito.";
			break;
			
		case(TipoCaracter::otro):
			cout<< " El caracter introducido no es una letra ni un numero.";
			break;
			 
	}
	
	cout<< endl<< endl;
	
	return 0;
}
