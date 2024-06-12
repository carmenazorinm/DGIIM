/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 27: el programa pide el numero de filas y el numero de columnas 
	de una matriz y pide los datos de cada una de las casillas. Una vez la
	matriz está completa, se buscan los mínimos de cada fila y se calcula el 
	maximo de entre todos los minimos.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

struct minimo{
	int fila;
	int columna;
	double valor;
};

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
		getline( cin, respuesta);
		es_valido = ComprobarQueEsPositivo(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}
/******************************************************************************/

int main(){
	
	int numero_filas;
	int numero_columnas;
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	
	do{
		numero_filas = 
					LeePositivo("Introduzca el numero de filas de la matriz: ");
	}while(numero_filas == 0);
	
	do{
		numero_columnas = 
				LeePositivo("Introduzca el numero de columnas de la matriz: ");
	}while(numero_columnas == 0);
			
	const int FILAS = numero_filas;
	const int COLUMNAS = numero_columnas;
	
	double matriz[FILAS][COLUMNAS];
	minimo minimo_de_fila[FILAS]; //un vector que contenga los datos del minimo
								  //de cada fila.
	
	for(int i = 0; i < FILAS; i++){
		
		cout<<endl;
		cout<<" Introduzca los valores de la fila "<< i+1 << ":"<< endl;
		
		for(int j = 0; j < COLUMNAS; j++){
			cout<< " Columna "<< j+1 << ": ";
			cin>>matriz[i][j];
		}
	}
				
	//CALCULOS
	
	//buscamos el minimo de cada fila. Para ello, suponemos que el minimo de 
	//cada fila es el valor de la primera columna. Por eso, añadimos todos los
	//datos de éste. Y cambiamos los datos del mínimo cada vez que se encuentre
	//un valor menor que el minimo asignado de esa fila.
	for(int i = 0; i < FILAS; i++){	
		minimo_de_fila[i].fila = i;	
		minimo_de_fila[i].columna = 0;
		minimo_de_fila[i].valor = matriz[i][0];
		
		for(int j = 0; j < COLUMNAS; j++){	
			if(matriz[i][j] < minimo_de_fila[i].valor){
				minimo_de_fila[i].valor = matriz[i][j];
				minimo_de_fila[i].columna = j;
			}
		}
	}
	
	//creamos un minimo que se denomine maximo. Para encontrar el maximo entre 
	//los minimos, suponemos que el maximo es el minimo de la posicion 0 en el 
	//vector minimo_de_fila. Por eso, añadimos todos sus datos al maximo. Cada 
	//vez que se encuentre un valor mayor que el maximo asignado, se cambiarán
	//todos sus datos. 
	minimo maximo = minimo_de_fila[0];
	
	for(int i = 0; i < FILAS; i++){
		if(minimo_de_fila[i].valor > maximo.valor){
			maximo = minimo_de_fila[i];
		}
	}
	
	//SALIDA
	
	cout<< endl;
	cout<< " El maximo entre los minimos de cada fila es: ";
	cout<< maximo.valor;
	cout<< ". Y se encuentra en la fila "<< maximo.fila+1;
	cout<< " y en la columna " << maximo.columna+1;
	cout<<endl <<endl;
	
	return 0;
}
