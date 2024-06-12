/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicios 6, 7 y 8: el programa lee dos secuencias de caracteres y pide
	el numero de la posicion de la secuencia1 en la que se quiere insertar la
	secuencia2. Por lo tanto, tenemos dos secuencias: 
	- secuencia1 es la implicita
	- secuencia2 es la explicita
	Se llama a un m�todo de la secuencia1 InsertaSecuenciaCaracteres() y se
	inserta la secuencia2 dentro de la secuencia1. Este m�todo devuelve una 
	nueva secuencia. En la funci�n main, se crea una nueva secuencia que ser�
	la que devuelva la funci�n InsertaSecuenciaCaracteres(). Finalmente, el 
	programa muestra la secuencia nueva.
	
*/

#include<iostream>
#include<string>

using namespace std;

class Lector{
	private:
		string titulo;
		
	public:
		//constructor
		Lector(string enunciado):
			titulo(enunciado)
		{}
		
		//constructor 2. Se puede crear un objeto sin darle ningun string
		Lector(void):
			titulo()
		{}
		
		//m�todo que permite cambiar el titulo 
		void SetTitulo(string enunciado){
			titulo = enunciado;
		}
		
		//Lee entero. A esta funci�n no hay que llamarla con ninguna expresi�n,
		//porque la expresi�n que va a pintar es la del titulo de su objeto.
		int LeeEntero (void){
			string respuesta;
			bool es_valido;
			do{
				cout<< titulo;
				getline( cin, respuesta);
				es_valido = ComprobarQueEsEntero(respuesta);
			}while(!es_valido);
			int entero = stoi(respuesta); 
			return entero;
		}
		
		//Lee entero en rango. Se le va a llamar introduciendo los valores 
		//limites del rango, pero no va a hacer falta introducir el titulo, 
		//pues ya se sabe, porque se ha introducido al crear el objeto.
		int LeeEnteroEnRango (int menor, int mayor){
			string respuesta;
			bool es_valido;
			int entero;
			
			do{
				cout<< titulo<< menor << " y "<<mayor<<":";
				getline( cin, respuesta);
				es_valido = ComprobarQueEsEntero(respuesta); 
		
				if(es_valido){ 
					entero = stoi(respuesta);
					es_valido = EstaDentroDelRango(entero, menor, mayor);
				}
			}while(!es_valido);
			return entero; 
		}
		
		//Lee entero mayor o igual. S�lo hace falta llamar al m�todo con el 
		//valor de la referencia.
		int LeeEnteroMayorOIgual (int referencia){
			string respuesta;
			bool es_valido;
			int entero;
			
			do{
				cout<<titulo;
				cin>>respuesta;
				es_valido = ComprobarQueEsEntero(respuesta);
		
				if(es_valido){ 
					entero = stoi(respuesta);
					es_valido = entero>=referencia;
				}
			}while(!es_valido);
	
			return entero;
		}
		
		//Lee real. Tampoco se le llama con nada, el titulo es el del objeto
		double LeeReal (void){
			string respuesta;
			bool es_valido;
	
			do{
				cout<< titulo;
				cin>>respuesta;
				es_valido = ComprobarQueEsReal(respuesta);
			}while(!es_valido);
	
			double real = stod(respuesta);
			return real;
		}
		
	
	private:
		//el m�todo que comprueba que es entero es privado. No queremos que se
		//pueda utilizar en a funcion main, simplemente es un bool que servir�
		//para ejecutar las funciones LeeEntero, LeeEnteroEnRango y 
		//LeeEnteroMayorOIgual
		bool ComprobarQueEsEntero (string cadena){
			int j = 0;
			bool es_entero = true;
			
			if(cadena.at(0) == '-' || cadena.at(0) == '+')
				j++;
				
			while(es_entero && j<cadena.length()){
				char caracter_posicion_j = cadena.at(j);
				es_entero = (caracter_posicion_j>='0' && 
						caracter_posicion_j <='9')||caracter_posicion_j == ' ';
				j++;
			}
			return es_entero; //true si es un entero y false si no lo es.	
		}
		
		bool EstaDentroDelRango(int numero, int minimo, int maximo){
			bool correcto = false;
			if(numero>=minimo && numero<=maximo) 
				correcto = true;
		
			return correcto;
		}
		
		bool ComprobarQueEsReal (string cadena){
			int j = 0;
			bool es_real = true;
	
			if(cadena.at(0) == '+' || cadena.at(0) == '-')
				j++;
		
			while(es_real && j<cadena.length()){
		
				char caracter_posicion_j = cadena.at(j);
				es_real =(caracter_posicion_j>='0' && caracter_posicion_j <='9')
							|| caracter_posicion_j == '.';		
				j++;
			}
			return es_real; //true si es un positivo y false si no lo es.	
		}
};
//////////////////////////////////////////////////////////////////////////////

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
	//inserta la secuencia otra dentro de la secuencia impl�cita. Para ello, 
	//crea una SecuenciaCaracteres nueva, a �sta se le a�adiran los caracteres
	//de la secuencia impl�cita hasta la pos_insercion-1. A partir de la 
	//pos_insercion-1, se empiezan a a�adir los caracteres de la secuencia otra.
	//Cuando la secuencia otra haya acabado de copiarse entera en nueva,  
	//entonces introducimos los caracteres de la secuencia impl�cita desde 
	//donde los hab�amos dejado, es decir, desde pos_insercion-1.
	
	//PRE: pos_insercion > 0
	SecuenciaCaracteres InsertaSecuenciaCaracteres(int pos_insercion, 
													SecuenciaCaracteres otra){
		SecuenciaCaracteres nueva;
		//si la posicion desde donde se quiere empezar a insertar la secuencia
		//otra no est� en la secuencia impl�cita, entonces se copia en nueva
		//toda la secuencia impl�cita. Justo despu�s, se copiar� la secuencia 
		//otra. 
		if(pos_insercion <= total_utilizados){
			
			for(int i = 0; i < pos_insercion-1; i++){
				if(nueva.TotalUtilizados() < TAMANIO)
					nueva.Aniade(vector_privado[i]);
			}
		}else
			for(int i = 0; i < total_utilizados; i++)
				nueva.Aniade(vector_privado[i]);
		
		//se copia la secuencia otra, a partir de la pos_insercion
		for (int i = 0; i < otra.TotalUtilizados(); i++){
			if(nueva.TotalUtilizados() < TAMANIO)
				nueva.Aniade(otra.Elemento(i));
		}
		
		for(int i = pos_insercion-1; i < total_utilizados; i++){
			if(nueva.TotalUtilizados() < TAMANIO)
				nueva.Aniade(vector_privado[i]);
		}
		
		return nueva;	
	}
};

///////////////////////////////////////////////////////////////////////////////

int main(){
	SecuenciaCaracteres secuencia;
	SecuenciaCaracteres otra;
	char caracter;
	
	//ENTRADA DE DATOS
	
	//se pide la secuencia impl�cita
	cout<<" Introduzca una secuencia de caracteres: ";
	do{
		cin>> caracter;
		if(caracter != '.')
			secuencia.Aniade(caracter);
	}while(caracter != '.');
	
	cout<<" Secuencia introducida: "<< secuencia.ToString()<<endl;
	
	//se pide la secuencia a inssertar en la impl�cita
	cout<<" Introduzca otra secuencia de caracteres: ";
	do{
		cin>> caracter;
		if(caracter != '.')
			otra.Aniade(caracter);
	}while(caracter != '.');
	
	cout<<" Secuencia introducida: "<<otra.ToString()<<endl;
	
	//se pide la posicion de insercion
	Lector lector;
	lector.SetTitulo(" Introduzca la posicion de insercion: ");
	int numero;
	numero = lector.LeeEnteroMayorOIgual(1);
	
	//CALCULOS
	
	SecuenciaCaracteres nueva;
	nueva = secuencia.InsertaSecuenciaCaracteres(numero, otra);
	
	//SALIDA
	
	cout<<" Secuencia final: "<<nueva.ToString();
	
	cout<<endl<<endl;
	return 0;
}
