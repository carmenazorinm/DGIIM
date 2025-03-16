/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Prueba 2
*/
#include<iostream>
#include <iomanip>
#include <string>
#include<ctime>
#include<cstdlib>
#include<cctype>
using namespace std;
	
/*********/
/*********/

int main()
{		
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	
    //.......................................................................
	// Para generar números aleatorios

	const int NUM_FILAS = 5;  // Núm. valores posibles
	const int NUM_COLS  = 5;  // Núm. valores posibles
	
	const int NUM_DATOS_LINEA = 10; // Para la presentación de datos
	
	
	// COMPLETAR
	

	// Inicializa el generador de números aleatorios con el reloj del 
	// sistema  (hora actual)
	time_t t;
	srand ((int) time(&t)); 
	
	// RELLENAR MATRIZ
	
	int matriz[NUM_FILAS][NUM_COLS] = {0};
	
	/* 
		Recuerde que la ejecución de
		
			int valor = rand() % NUM; 

	  	genera un num. aleatorio   0 <= valor < NUM
	*/
	const int NUMEROS = NUM_FILAS*NUM_COLS;
	int contador[NUMEROS] = {0};
	
	for(int i = 1; i <= NUM_FILAS*NUM_COLS; i++){
		int fila;
        int columna;
        do{
			fila = rand() % NUM_FILAS;
			columna = rand() % NUM_COLS;
			contador[i] ++;
		}while( matriz[fila][columna] != 0);
		matriz[fila][columna] = i;
	}
			
				
	// MOSTRAR INTENTOS
	int intentos_totales = 0;
	

	cout << "Intentos para alojar los valores: " << endl; 
	for(int i = 0; i < NUMEROS; i++){
        cout<<setw(5)<<contador[i];
        if(i% NUM_DATOS_LINEA == 0){ 
            cout<<endl;
        }
		intentos_totales = intentos_totales + contador[i];
	}
	cout << endl; 
	
	double media = intentos_totales/NUMEROS;

	//.............. COMPLETAR
	

	// MOSTRAR RESUMEN
	
	cout << endl; 
	cout << "Intentos totales  " << setw(5) << intentos_totales << endl; 
	cout << "Media: " << setw(6) << setprecision(2) << media << endl; 
	cout << endl; 

	//.............. COMPLETAR
	

	// MOSTRAR MATRIZ

	cout << endl; 
	cout << "Matriz de valores: " << endl; 
	for(int i = 0; i < NUM_FILAS; i++){
		cout<<endl;
		for(int j = 0; j< NUM_COLS; j++){
			cout<<setw(3)<<matriz[i][j];
		}
	}
	cout << endl; 
	
	//.............. COMPLETAR

	return 0;	
}

/*********/
/*****/
