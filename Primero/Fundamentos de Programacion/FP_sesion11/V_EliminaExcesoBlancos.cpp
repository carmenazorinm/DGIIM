/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 30: el programa lee una secuencia de caracteres hasta que se 
	introduzca un punto. Se encarga que todos los espacios reptidos despues
	de otro, se eliminen y actualiza la secuencia de caracteres. Para ello 
	utiliza la clase SecuenciaCaracteres y crea un objeto suyo.
*/

#include<iostream>

using namespace std;

class SecuenciaCaracteres {
	
private:
	static const int TAMANIO = 50; // Núm.casillas disponibles
	char vector_privado[TAMANIO];
	// PRE: 0<=total_utilizados<=TAMANIO
	int total_utilizados; // Núm.casillas ocupadas
	
public:
	/*********************************************************/
	// Constructor sin argumentos
	SecuenciaCaracteres (void) : 
		total_utilizados (0) 
		{}
		
	/*********************************************************/
	// Devuelve el número de casillas ocupadas
	int TotalUtilizados (void){
		return (total_utilizados);
	}
	
	/*********************************************************/
	// Devuelve el número de casillas disponibles
	int Capacidad (void){	
		return (TAMANIO);
	}
	
	/*********************************************************/
	// "Vacía" completamente la secuencia
	void EliminaTodos (void){
		total_utilizados = 0;
	}
	
	/*********************************************************/
	// Añade un elemento ("nuevo") al vector.
	// PRE: total_utilizados < TAMANIO
	// La adición se realiza si hay alguna casilla disponible.
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
	// dado en "nuevo". El tamaño de la secuencia no cambia.
	// PRE: 0 <= indice < total_utilizados
	void Modifica (int indice, char nuevo){
		if ((indice >= 0) && (indice < total_utilizados))
			vector_privado[indice] = nuevo;
	}
	
	/*********************************************************/
	// Eliminar el carácter de la posición dada por "indice".
	// Realiza un borrado físico (desplazamiento y sustitución).
	// PRE: 0 <= indice < total_utilizados
	void Elimina (int indice){
		if ((indice >= 0) && (indice < total_utilizados)) {
			int tope = total_utilizados-1; // posic. del último
			
			for (int i = indice ; i < tope ; i++)
				vector_privado[i] = vector_privado[i+1];
			
			total_utilizados--;
		}
	}
	
	/*********************************************************/
	// Inserta el carácter "nuevo" en la posición dada por "indice".
	// Desplaza todos los caracteres una posición a la derecha
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
	// Compone un string con todos los caracteres que están
	// almacenados en la secuencia y lo devuelve.
	string ToString(){
		string cadena;
		
		for (int i=0; i<total_utilizados; i++)
			cadena = cadena + vector_privado[i];
			
		return (cadena);
	}
	
	/**********************************************************/
	// Elimina todos los espacios sobrantes de un objeto de esta clase. Para
	//ello usa dos variables escritura y lectura. Ambos empiezan en la primera
	//posicion, ya que dependen del caracter en la posicion anterior.
	//La variable lectura avanza siempre una posicion y la variable escritura 
	//solo avanzará en caso de que la posicion anterior a ella sea distinta del
	//espacio. En caso de que sea un espacio, no se moverá y esperará a que
	//la variable lectura encuentre un caracter distinto del espacio.
	void EliminaExcesoBlancos(){
		const char ESPACIO = ' ';
		int escritura = 1;
		bool espacio_repetido = false;
		//creamos una variable que cuenta los espacios sobrantes y asi poder 
		//actualizar el dato total_utilizados al final del método.
		int contador_espacios_sobrantes = 0; 
		
		//lectura siempre avanza una posicion
		for(int lectura = 1; lectura < total_utilizados; lectura++){
			
			//si la posicion en lectura no es un espacio, se copiaen escitura 
			//siempre.
			if(vector_privado[lectura] == ESPACIO){
				espacio_repetido = (vector_privado[escritura-1] == ESPACIO);
				
				//Si ya hay un espacio en la posicion de antes de escritura, no
				//queremos que escritura avance. 
				//En caso de que no haya un espacio antes, pero en la posicion 
				//de LECTURA sí que haya un espacio, en la posicion de
				//escritura ponemos un espacio y avanzamos.
				if(!espacio_repetido){
					vector_privado[escritura] = ESPACIO;
					escritura++;
				}
				else
					contador_espacios_sobrantes++;
					
			}else{
				vector_privado[escritura] = vector_privado[lectura];
				escritura++;
			}
			
		}
		//actualizamos el dato total_utilizados
		total_utilizados = total_utilizados - contador_espacios_sobrantes; 
	}
	
	/***********************************************************/
	
};

//////////////////////////////////////////////////////////////////////////////

int main(){
	char caracter;
	SecuenciaCaracteres string;
	const char TERMINADOR = '.';
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	cout<< " Introduzca una cadena de caracteres (termina con .):";
	do{
		caracter = cin.get();
		//se va rellenando el vector_privado del objeto string
		string.Aniade(caracter);
	}while(caracter != TERMINADOR);
	
	//mostramos la longitud inicial
	cout<<" -------> Longitud: " << string.TotalUtilizados() << " caracteres";
	
	//CALCULOS
	
	string.EliminaExcesoBlancos();
	
	//SALIDA
	
	cout<<endl<<endl;
	cout<< " La cadena actualizada es:" << string.ToString() << endl;
	
	//mostramos la longitud final, comprobamos que funciona correctamente
	cout<<" -------> Longitud: " << string.TotalUtilizados() << " caracteres";
	
	cout<<endl << endl;
	
	return 0;
}

