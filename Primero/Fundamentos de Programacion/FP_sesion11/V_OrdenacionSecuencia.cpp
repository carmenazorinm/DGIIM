/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 35: el programa rellena un objeto de SecuenciaEnteros 
	aleatoriamente, es decir, con numeros aleatorios diseñados por un objeto
	de la clase GeneradorAleatorioEnteros. Una vez esta secuencia esté rellena, 
	se calcula el tiempo de ejecucion de cada uno de los metodos de ordenacion
	de la clase SecuenciaEnteros. Así, se crean tantas copias de la secuencia
	como métodos de ordenacion existan. Y creamos un cronometro de la clase
	Cronometro. Para cada copia de la secuencia, el cronometro se pone a 0 y
	se calcula el tiempo en ordenar dicha copia. Al final del todo, mostramos
	los tiempos en cada uno de los metodos de ordenacion.
	
	Para saber si la secuencia está siendo ordenada correctamnte, pibtaremos la
	secuencia inicial y cada una de las copias después de haberse ordenado.
	
*/

#include<iostream>
#include <random>  // para la generaci?n de n?meros pseudoaleatorios
#include <chrono>  // para la semilla

using namespace std;

class GeneradorAleatorioEnteros
{  
private:
	
	mt19937 generador_mersenne;    // Mersenne twister
	uniform_int_distribution<int>  distribucion_uniforme;
	
	/************************************************************************/
	
	long long Nanosec(){
		return (chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	
	/************************************************************************/ 
	
public:
	
	/************************************************************************/
		
	GeneradorAleatorioEnteros() : GeneradorAleatorioEnteros(0, 1) 
	{ }
	
	/************************************************************************/  
	GeneradorAleatorioEnteros(int min, int max) {
	
		const int A_DESCARTAR = 70000;
		// ACM TOMS Volume 32 Issue 1, March 2006
		
		auto semilla = Nanosec();
		generador_mersenne.seed(semilla);
		generador_mersenne.discard(A_DESCARTAR);
		distribucion_uniforme = uniform_int_distribution<int> (min, max);
	}
	
	/************************************************************************/
	
	int Siguiente(){
	  return (distribucion_uniforme(generador_mersenne));
	}
	
	/************************************************************************/

};
/////////////////////////////////////////////////////////////////////////////

class Cronometro
{
	
private:
	
   typedef std::chrono::time_point<std::chrono::steady_clock>
           Punto_en_el_Tiempo;
   typedef chrono::duration <double, nano> IntervaloTiempo;

   Punto_en_el_Tiempo inicio;
   Punto_en_el_Tiempo final;

public:
	
	/***********************************************************************/
	void Reset() { 
		inicio = chrono::steady_clock::now();
	}
	
	/************************************************************************/
	double NanoSegundosTranscurridos() {
		final = chrono::steady_clock::now();		
		IntervaloTiempo diferencia = final - inicio;
		return (diferencia.count());
	}
	
	/************************************************************************/
	double MiliSegundosTranscurridos() {
		final = chrono::steady_clock::now();		
		IntervaloTiempo diferencia = final - inicio;
		return (diferencia.count()/1e6);
	}
	/************************************************************************/  
};

/////////////////////////////////////////////////////////////////////////////

class SecuenciaEnteros {
	
private:
	static const int TAMANIO = 10; // Núm.casillas disponibles
	int vector_privado[TAMANIO];
	// PRE: 0<=total_utilizados<=TAMANIO
	int total_utilizados; // Núm.casillas ocupadas
	
public:
	/*********************************************************/
	// Constructor sin argumentos
	SecuenciaEnteros (void) : 
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
	int Elemento (int indice){
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
			cadena = cadena + " " + to_string(vector_privado[i]);
			
		return (cadena);
	}
	
	/*********************************************************/
	int PosicionMinimoEntre(int a, int b){
		int pos_minimo = a;
		a = a + 1;
		
		while(a <= b){
			
			if(vector_privado[pos_minimo] > vector_privado[a])
				pos_minimo = a;
			a++;
		}
		
		return pos_minimo;
	}
	
	/*********************************************************/
	void Ordena_por_Seleccion(){
		int pos_min;
		
		for (int izda = 0 ; izda < total_utilizados ; izda++){
			pos_min = PosicionMinimoEntre (izda, total_utilizados-1);
			IntercambiaComponentes_en_Posiciones (izda, pos_min);
		}
	}
	
	/*********************************************************/
	void Ordena_por_Insercion(){
		int izda, i;
		char a_desplazar;
		
		for (izda = 1; izda < total_utilizados; izda++){
			a_desplazar = vector_privado[izda];
			
			for (i = izda; i > 0 && a_desplazar < vector_privado[i-1]; i--)
				vector_privado[i] = vector_privado[i-1];
				
			vector_privado[i] = a_desplazar;
		}
	}
	
	/*********************************************************/
	void OrdenaIntercambio(){
		int izda, i;
		
		for (izda = 0; izda < total_utilizados; izda++){
			
			for(i = total_utilizados - 1; i > izda; i--){
				
				if(vector_privado[i] < vector_privado[i-1])
					IntercambiaComponentes_en_Posiciones(i, i-1);
			}
		}
	}
	
	/*********************************************************/
	void OrdenaIntercambioMejorado(){
		int izda, i;
		bool cambio;
		cambio = true;
		
		for(izda = 0; izda < total_utilizados && cambio; izda++){
			cambio = false;
			
			for(i = total_utilizados - 1; i > izda; i--){
				
				if(vector_privado[i] < vector_privado[i-1]){
					IntercambiaComponentes_en_Posiciones(i, i-1);
					cambio = true;
				}
			}
		}
	}
	
	/*********************************************************/
	void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
		char intercambia;
		
		intercambia = vector_privado[pos_izda];
		vector_privado[pos_izda] = vector_privado[pos_dcha];
		vector_privado[pos_dcha] = intercambia;
	}
	
};

//////////////////////////////////////////////////////////////////////////////

int main(){
	const int MINIMO = 0;
	const int MAXIMO = 10;
	
	SecuenciaEnteros secuencia;
	GeneradorAleatorioEnteros generador(MINIMO, MAXIMO);
	Cronometro cronometro;
	
	int casillas_vector = secuencia.Capacidad();
	
	//CALCULOS
	cout<<endl;
	
	//rellenamos la secuencia con enteros aleatorios.
	for(int i = 0; i < casillas_vector; i++){
		secuencia.Aniade(generador.Siguiente());
		//mostramos la secuencia inicial.
		cout<<secuencia.Elemento(i) << " ";
	}
	cout<<endl;
	
	//cronometramos cada uno de los metodos de ordenacion:
	
	SecuenciaEnteros sec_resultado; //constructor sin argumentos
	
		//ordenacion por seleccion
	sec_resultado = secuencia; //asignación
	cronometro.Reset();
	sec_resultado.Ordena_por_Seleccion();
	int tiempo_por_seleccion = cronometro.NanoSegundosTranscurridos();
	
		
		//ordenacion por inserción 
	sec_resultado = secuencia; //asignación
	cronometro.Reset();
	sec_resultado.Ordena_por_Insercion();
	int tiempo_por_insercion = cronometro.NanoSegundosTranscurridos();

		//ordenacion por intercambio
	sec_resultado = secuencia; //asignación
	cronometro.Reset();
	sec_resultado.OrdenaIntercambio();
	int tiempo_por_intercambio = cronometro.NanoSegundosTranscurridos();
	
		//ordenacion por intercambio mejorado
	sec_resultado = secuencia; //asignación
	cronometro.Reset();
	sec_resultado.OrdenaIntercambioMejorado();
	int tiempo_por_inter_mejorado = cronometro.NanoSegundosTranscurridos();
	
	//SALIDA
	
	cout<<endl<<endl;
	cout<<" Duracion en ejecutarse los distintos metodos de ordenacion: ";
	cout<<endl<<endl;
	cout<<" Por seleccion: " << tiempo_por_seleccion << " nanosegundos";
	cout<<endl;
	cout<<" Por insercion: " << tiempo_por_insercion << " nanosegundos";
	cout<<endl;
	cout<<" Por intercambio: " <<tiempo_por_intercambio << " nanosegundos";
	cout<<endl;
	cout<<" Por intercambio mejorado: " <<tiempo_por_inter_mejorado 
		<< " nanosegundos";
	
	cout<<endl<<endl;
	
	return 0;
}
