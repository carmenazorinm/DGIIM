/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 30: el programa lee una secuencia de caracteres hasta que se 
	introduzca un punto. Pide tabi�n el caracter que se quiere borrar de la
	secuencia le�da. Crea un objeto de la clase SecuenciaCaracteres y con
	el m�todo EliminaOcurrencias, elimina de la secuencia todas las apariciones
	del caracter que se quer�a borrar. 
*/

#include<iostream>

using namespace std;

class SecuenciaCaracteres {
	
private:
	static const int TAMANIO = 50; // N�m.casillas disponibles
	char vector_privado[TAMANIO];
	// PRE: 0<=total_utilizados<=TAMANIO
	int total_utilizados; // N�m.casillas ocupadas
	
public:
	/*********************************************************/
	// Constructor sin argumentos
	SecuenciaCaracteres (void) : 
		total_utilizados (0) 
		{}
		
	/*********************************************************/
	// Devuelve el n�mero de casillas ocupadas
	int TotalUtilizados (void){
		return (total_utilizados);
	}
	
	/*********************************************************/
	// Devuelve el n�mero de casillas disponibles
	int Capacidad (void){	
		return (TAMANIO);
	}
	
	/*********************************************************/
	// "Vac�a" completamente la secuencia
	void EliminaTodos (void){
		total_utilizados = 0;
	}
	
	/*********************************************************/
	// A�ade un elemento ("nuevo") al vector.
	// PRE: total_utilizados < TAMANIO
	// La adici�n se realiza si hay alguna casilla disponible.
	// El nuevo elemento se coloca al final del vector.
	// Si no hay espacio, no se hace nada.
	void Aniade (char nuevo){
		if (total_utilizados < TAMANIO){	
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}
	
	/*********************************************************/
	// Devuelve el elemento de la casilla "indice"
	// PRE: 0 <= indice < total_utilizados
	char Elemento (int indice){
		return (vector_privado[indice]);
	}
		
	/*********************************************************/
	// Cambia el contenido de la casilla "indice" por el valor
	// dado en "nuevo". El tama�o de la secuencia no cambia.
	// PRE: 0 <= indice < total_utilizados
	void Modifica (int indice, char nuevo){
		if ((indice >= 0) && (indice < total_utilizados))
			vector_privado[indice] = nuevo;
	}
	
	/*********************************************************/
	// Eliminar el car�cter de la posici�n dada por "indice".
	// Realiza un borrado f�sico (desplazamiento y sustituci�n).
	// PRE: 0 <= indice < total_utilizados
	void Elimina (int indice){
		if ((indice >= 0) && (indice < total_utilizados)) {
			int tope = total_utilizados-1; // posic. del �ltimo
			
			for (int i = indice ; i < tope ; i++)
				vector_privado[i] = vector_privado[i+1];
			
			total_utilizados--;
		}
	}
	
	/*********************************************************/
	// Inserta el car�cter "nuevo" en la posici�n dada por "indice".
	// Desplaza todos los caracteres una posici�n a la derecha
	// antes de copiar en "indice" en valor "nuevo".
	// PRE: 0 <= indice < total_utilizados
	void Inserta (int indice, char valor_nuevo){
		if ((total_utilizados < TAMANIO) && (indice >= 0)
											&& (indice < total_utilizados)){

			for (int i = total_utilizados ; i > indice ; i--)
				vector_privado[i] = vector_privado[i-1];
				
			vector_privado[indice] = valor_nuevo;
			total_utilizados++;
		}
	}
	
	/*********************************************************/
	// Compone un string con todos los caracteres que est�n
	// almacenados en la secuencia y lo devuelve.
	string ToString(){
		string cadena;
		
		for (int i=0; i<total_utilizados; i++)
			cadena = cadena + vector_privado[i];
			
		return (cadena);
	}
	
	/**********************************************************/
	// Elimina del string el caracter a_borrar. Para ello se utilizan las
	//variables escritura y lectura. Lectura siempre se mover� una casilla
	//en el vector_privado. En caso de que no se encuentre con el caracter
	//a_borrar, se escribir� en la posicion escritura el caracter 
	//de lectura. Si el caracter de lectura es el a_borrar, entonces 
	//escritura no se mueve y espera a que lectura encuentre un caracter
	//distinto de a_borrar para copiarlo.
	void EliminaOcurrencias(char a_borrar){
		int escritura = 0; //empieza por la posicion 0 del vector
		int contador = 0;
		
		//lectura siempre avanza una posicion
		for(int lectura = 0; lectura < total_utilizados; lectura++){
			if(vector_privado[lectura] != a_borrar){
				vector_privado[escritura] = vector_privado[lectura];
				escritura++;
			}else
				contador++;
		}
		total_utilizados = total_utilizados - contador; 
	}
};

//////////////////////////////////////////////////////////////////////////////

int main(){
	char caracter;
	SecuenciaCaracteres string;
	const char TERMINADOR = '.';
	
	//ENTRADA DE DATOS Y CALCULOS
	
	cout<<endl;
	cout<< " Introduzca una cadena de caracteres (termina con .): ";
	do{
		caracter = cin.get();
		//se va rellenando el vector_privado del objeto string
		string.Aniade(caracter);
	}while(caracter != TERMINADOR);
	
	//mostramos la longitud inicial
	cout<<" -------> Longitud: " << string.TotalUtilizados() << " caracteres";
	
	cout<<endl;
	cout<< " Introduzca el caracter que quiere borrar: ";
	cin>>caracter;
	string.EliminaOcurrencias(caracter);
	
	//SALIDA
	
	cout<<endl;
	cout<< " La cadena actualizada es: " << string.ToString() << endl;
	
	//mostramos la longitud final, comprobamos que funciona correctamente
	cout<<" -------> Longitud: " << string.TotalUtilizados() << " caracteres";
	
	cout<<endl << endl;
	
	return 0;
}

