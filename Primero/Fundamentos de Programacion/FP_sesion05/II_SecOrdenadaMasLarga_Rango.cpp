/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 43: el programa leer� un intervalo de temperaturas y. adem�s, 
	leer� temperaturas de ese intervalo. Dir� cual es la secuencia m�s larga
	que contiene temperaturas cada una m�s alta que la anterior. 
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	int secuencia= 1;
	int secuencia_mas_larga = 0;
	double temperatura;
	double temperatura_ant;
	int posicion = 1;
	int posicion_donde_empieza;
	
	double MIN_RANGO;
	double MAX_RANGO;
	
	//entrada de datos 
	
	do{
	
		cout<< endl;
		cout<< " Introduzca un valor m�ximo del rango: ";
		cin>> MAX_RANGO;
		cout<< " Introduza un valor m�nimo del rango: ";
		cin>> MIN_RANGO;
		cout<< endl;
	
	}while (MAX_RANGO<MIN_RANGO);
	
	do{
		
		cout<< " Introduzca el valor de la primera temperatura: ";
		cin>> temperatura;
		
	}while(temperatura< MIN_RANGO || temperatura>MAX_RANGO);
	
	//calculos
	
	while (temperatura>= MIN_RANGO && temperatura<=MAX_RANGO){
		
		temperatura_ant = temperatura;
		
		cout<< " Introduzca el siguiente valor de temperatura: ";
		cin>>temperatura;
		
		while (temperatura_ant < temperatura && temperatura<=MAX_RANGO){
			
			secuencia++;
			posicion++;
			temperatura_ant = temperatura;
			
			cout<< " Introduzca el siguiente valor de temperatura: ";
			cin>>temperatura;
		}
		posicion++;
		
		if (secuencia_mas_larga < secuencia){
		
			secuencia_mas_larga = secuencia;
			posicion_donde_empieza = posicion - secuencia_mas_larga;
		}
		secuencia= 1;
	}
	
	//salida
		
	cout<<endl;	
	cout<<" La mayor subsecuencia empieza en la posicion ";
	cout<<posicion_donde_empieza<< " y tiene longitud " << secuencia_mas_larga;
	cout<<endl;
	

	
	return 0;
}
