#include<iostream>
#include<algorithm>
#define MAXN 1000005
using namespace std;

// Para compilar: g++ maxToneladas.cpp -o maxToneladas -std=gnu++0x

// Método ordenacion de mayor a menor
bool mayor (int a, int b){
	return a>b;
}


/*
  Se tiene un buque mercante con capacidad c de carga y un conjunto de n contenedores wi
  con sus pesos respectivos pi. Todos estos datos se le piden al usuario. Este algoritmo
  maximiza el número de toneladas cargadas.
*/

int main()
{
	// Declaración de datos
	int w[MAXN];
	int c,n;
	int suma_toneladas = 0;
	
	// Pedimos los datos de los pesos al usuario
    	cout << "Capacidad contenedora: ";
    	cin >> c;
    	cout << endl << "Numero contenedores: ";
	cin >> n;
    	cout << endl;	 
	
	for(int i= 0; i < n; ++i){
		cout << "Peso del contenedor " << (i+1) << ": ";
        	cin >> w[i];
        	cout << endl;
    	}
	
	// Ordenamos los pesos de los contenedores de mayor a menor
	sort(w,w+n,mayor);
	
	// Imprimimos el array ordenado
	for (int i=0; i<n; ++i){
		cout << " " << w[i];
	}
	cout << endl;
	
	// Aplicamos la técnica Greedy
	for(int i = 0; ((i<n)&&(suma_toneladas <= c)); ++i){
		if (w[i]<=c){
			if (w[i]+suma_toneladas <= c)
				suma_toneladas += w[i];
			else
				break;
		}
	}
	
	// Mostramos la solución obtenida, no siempre será la óptima
	cout << "Número de toneladas cargadas: "<< suma_toneladas << endl;
	return 0;
}
