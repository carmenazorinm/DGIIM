/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 9: el programa lee una secuencia de caracteres y ordena sus 
	caracteres segun su posicion en la tabla ASCII. Adem�s, se encarga de que 
	cada caracter aparezca tantas veces como aparece en la cadena introducida.
	Para ello, se crea la clase SecuenciaCaracteres y se introduce el m�todo
	CountingSort, que devolver� la secuencia ordenada.
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
	//Este m�todo devuelve una secuencia ordenada de la secuencia implicita.
	//Para ello busca el menor y el mayor caracter en la secuencia implicita
	// A continuacion llama al m�todo CountingSortEntre(minimo,maximo) y copia
	//la secuencia que devuelve este m�todo en un objeto de Secuenciacaracteres.
	//El m�todo CountingSort() devuelve la secuencia ordenada.
	SecuenciaCaracteres CountingSort(void){
		
		int caracter_minimo = vector_privado[0];
		int caracter_maxima = caracter_minimo;
		for(int i=1; i < TotalUtilizados(); i++){
			
			if(caracter_minimo > vector_privado[i])
				caracter_minimo = vector_privado[i];
			if(caracter_maxima < vector_privado[i])
				caracter_maxima = vector_privado[i];
		}
		
		SecuenciaCaracteres secuencia_ordenada;
		secuencia_ordenada=CountingSortEntre(caracter_minimo, caracter_maxima);
		
		return secuencia_ordenada;
	}
	
private: 
	/*****************************************************************/
	//este m�todo devuelve una secuencia ordenada desde dos caracteres que se 
	//le dan. Para ello, crea un vector que guarda cu�ntas veces aparece cada
	//caracter en el vector_privado[]. A partir de ah�, crea un objeto de la 
	//SecuenciaCaracteres y va a�adiendo a esta secuencia nueva el caracter 
	//minimo tantas veces como aparaezca, luego el caracter minima+1 tantas 
	//veces como aparezca y as� hasta llegar al caracter maximo.
	SecuenciaCaracteres CountingSortEntre(char min, char max){
		
		const int TOTAL_CARACTERES = 100;
		int vector_frecuencias[TOTAL_CARACTERES];
		
		//inicializamos el vector_frecuencias[] a 0.
		for(int i = 0; i < TOTAL_CARACTERES; i++)
		    vector_frecuencias[i] = 0;
		
		//se pasa por todas las casillas del vector_privado[]. Miramos cual
		//es el caracter que pertenece a dicha casilla. Posicionamos el 
		//caracter en una casilla del vector_frecuencias[], su casilla en este
		//vector ser� su caracter - min. Se a�ade +1 en el vector_frecuencias[] 
		for(int i=0; i < total_utilizados; i++){
			int pos = vector_privado[i] - min;
			vector_frecuencias[pos]++;
		}
		
		//creamos la secuencia ordenada, al rpinciapio est� vac�a
		SecuenciaCaracteres ordenada;
		
		//la SecuenciaCaracteres ordenada se ir� rellenando con cada caracter
		//que pertenece al vector_privado[] y se a�adir� tantas veces como 
		//aparezca. Primero a�adiremos el caracter min y lo a�adiremos
		//vector_frecuencia[0] veces. Despu�s a�adiremos el caracter min+1 y lo 
		//a�adiremos vector_frecuencias[1] veces. Despu�s el caracter min+2 
		//vector_frecuencias[2] veces. 
		for(int i = 0; i < max-min+1; i++){
			char caracter = i + min;
			for(int veces = 0; veces < vector_frecuencias[i]; veces++){
				ordenada.Aniade(caracter);
			}
		}
		
		return ordenada;	
	}
	
};

///////////////////////////////////////////////////////////////////////////////

int main(){
	SecuenciaCaracteres secuencia;
	char caracter;
	bool sigue_leyendo = true;
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	cout<<" ";
	//rellenamos la secuencia
	do{
		cin>>caracter;
		if(caracter != '.')
			secuencia.Aniade(caracter);
		else
			sigue_leyendo = false;
			
	}while(sigue_leyendo);
	
	//CALCULOS
	
	cout<<endl;
	cout<<" Secuencia introducida: " <<endl;
	cout<<" " << secuencia.ToString();
	
	SecuenciaCaracteres ordenada(secuencia.CountingSort());
	
	//SALIDA
	
	cout<<endl;
	cout<<endl<<" Secuencia ordenada: "<<endl;;
	cout<<" " << ordenada.ToString();
	
	cout<<endl<<endl;
	return 0;
}
