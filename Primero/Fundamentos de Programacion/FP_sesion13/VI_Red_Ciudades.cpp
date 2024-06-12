/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 38:el programa contiene una clase llamada MapaDistancias cuya
	función es guardar la distancia que hay entre distintas ciudades. Para 
	ello, primero debe rellenar su dato TablaRectangularReales mediante el
	método RellenaMapa(), posteriormente hará una serie de cálculos:s
	a) se calcula cuál es la ciudad con mas conexiones directas 
	b) se pregunta por una ciudad y se muestran sus conexiones directas
	c) se pregunta por dos ciudades que no tengan conexion directa y se muestra
	cuál es la ciudad intermedia por la que se debería pasar para hacer el 
	menor recorrido posible
	d) se preguntan por varias ciudades y se dicen si las ciudades están todas
	conectadas entre ellas o no.
	
	
*/

#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>

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
		
		//método que permite cambiar el titulo 
		void SetTitulo(string enunciado){
			titulo = enunciado;
		}
		
		//Lee entero. A esta función no hay que llamarla con ninguna expresión,
		//porque la expresión que va a pintar es la del titulo de su objeto.
		int LeeEntero (void){
			string respuesta;
			bool es_valido;
			do{
				cout<< titulo;
				cin>>respuesta;
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
				cout<<titulo;
				cin>>respuesta;
				es_valido = ComprobarQueEsEntero(respuesta); 
		
				if(es_valido){ 
					entero = stoi(respuesta);
					es_valido = EstaDentroDelRango(entero, menor, mayor);
				}
			}while(!es_valido);
			return entero; 
		}
		
		//Lee entero mayor o igual. Sólo hace falta llamar al método con el 
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
		//el método que comprueba que es entero es privado. No queremos que se
		//pueda utilizar en a funcion main, simplemente es un bool que servirá
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
				es_real=(caracter_posicion_j>='0' && caracter_posicion_j <='9')
							|| caracter_posicion_j == '.';		
				j++;
			}
			return es_real; //true si es un positivo y false si no lo es.	
		}
};
///////////////////////////////////////////////////////////////////////

class SecuenciaEnteros  
{

private:

	static const int TAMANIO = 40; // Número de casillas disponibles
	int vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas

public:
	
	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaEnteros (void) 
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Métodos de lectura (Get) de los datos individuales 

	// Devuelve el número de casillas ocupadas
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}

	// Devuelve el número de casillas disponibles
	int Capacidad (void)
	{
		return (TAMANIO);
	}

	/***********************************************************************/
	// Añade un elemento al vector.
	// Recibe: nuevo, el elemento que se va a añadir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adición se realiza si hay espacio para el nuevo elemento. 
	// 		El nuevo elemento se coloca al final del vector. 
	// 		Si no hay espacio, no se hace nada.	

	void Aniade (int nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}

	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice" 
	//
	// PRE: 0 <= indice < total_utilizados 

	int Elemento (int indice)
	{
		return vector_privado[indice];
	}

	/***********************************************************************/
	// Devuelve true si la secuencia está vacía

	bool EstaVacia (void)
	{
		return (total_utilizados == 0);
	}

	/***********************************************************************/
	// "Vacía" una secuencia

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}
	
	/***********************************************************************/
	// FIN METODOS BASICOS
	/***********************************************************************/
	
	/***********************************************************************/
	// Búsqueda de un valor en la secuencia, entre dos posiciones dadas. 
	// Realiza una búsqueda secuencial
	//
	// Recibe: 	buscado, el valor a buscar en la secuencia.
	//			izda y dcha, posiciones entre las que se realiza la búsqueda.
	// Devuelve: la posición del elemento "buscado", si está en la secuencia,
	//			 o -1, si no lo encuentra.
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Posicion (int buscado, int izda, int dcha)
	{
		bool encontrado = false; 
		int pos = izda; 

		while ((pos <= dcha) && (!encontrado)) {

			if (vector_privado[pos] != buscado) // Seguir buscando
				pos++;
			else // Terminar la búsqueda: éxito
				encontrado =  true;
		} 

		if (encontrado)
			return (pos);
		else 
			return (-1);

	}
	
	/***********************************************************************/
	// Devuelve la posición del mínimo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados
	
	int PosicionMinimo (int izda, int dcha)
	{
		int posicion_minimo;
		int minimo;
	
		minimo = vector_privado[izda];
		posicion_minimo = izda;
		
		for (int i = izda; i <= dcha ; i++) { 
			
			if (vector_privado[i] < minimo){
				minimo = vector_privado[i];
				posicion_minimo = i;
			}
		}
		
		return (posicion_minimo);		
	}
	
	/***********************************************************************/
	// Devuelve la posición del máximo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados
	
	int PosicionMaximo (int izda, int dcha)
	{
		int posicion_maximo;
		int maximo;
	
		maximo = vector_privado[izda];
		posicion_maximo = izda;
		
		for (int i = izda; i <= dcha ; i++) { 
			
			if (vector_privado[i] > maximo){
				maximo = vector_privado[i];
				posicion_maximo = i;
			}
		}
		
		return (posicion_maximo);		
	}
	
	/***********************************************************************/
	// Devuelve el mínimo de la secuencia. 
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Minimo (int izda, int dcha)
	{
		return (vector_privado[PosicionMinimo(izda, dcha)]);
	}


	/***********************************************************************/
	// Devuelve el máximo de la secuencia. 
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Maximo (int izda, int dcha)
	{
		return (vector_privado[PosicionMaximo(izda, dcha)]);
	}
	
	/***********************************************************************/
	// Devuelve una secuencia incluida en la secuencia implícita, que empieza 
	// en la posición "pos_init" y tiene "num_datos" valores
	//
	// Recibe: pos_init, posición inicial desde donde empieza la copia a la 
	//					 subsecuencia. 
	//		   num_datos, número de valores que se copian a la subsecuencia. 
	// Devuelve: una subsecuencia de la secuencia implícita. 
	// 
	// Casos: 1) Si 0 <= pos_init < total_utilizados Y 
	//			 pos_init+num_datos<=total_utilizados
	//			 se devuelve una subsecuencia de tamaño "num_datos"
	//		  2) Si 0 <= pos_init < total_utilizados Y 
	//			 pos_init+num_datos>total_utilizados, se devuelve una 
	//			 subsecuencia de tamaño total_utilizados-pos_init
	//		  3) Si pos_init < 0 Ó pos_init >= total_utilizados, 
	//			 se devuelve una subsecuencia vacía.
	//		  4) Si num_datos = 0, se devuelve una subsecuencia vacía.

	SecuenciaEnteros Subsecuencia (int pos_init, int num_datos)
	{
		SecuenciaEnteros a_devolver; // inicialmente vacía
		
		if ((pos_init>=0) && (pos_init<total_utilizados) && (num_datos>0)) {
			
			int pos_end;
			
			if (pos_init+num_datos>total_utilizados) 
				pos_end = total_utilizados;
			else 
				pos_end = pos_init+num_datos;
			
			for (int pos=pos_init; pos<pos_end; pos++)
				a_devolver.Aniade(vector_privado[pos]);
		}
		
		return (a_devolver);
	}
		
	/***********************************************************************/
	// COMPARACIÓN
	/***********************************************************************/
				
	/***********************************************************************/
	// Compara dos secuencias
	
	bool EsIgual (SecuenciaEnteros otra_secuencia) 
	{
		bool son_iguales = true; 
		
		if (total_utilizados != otra_secuencia.total_utilizados)
		
			son_iguales = false;
		
		else {
				
			bool sigo = true;
			int pos = 0;
			
			while (sigo && (pos < total_utilizados)) {
	
				if (vector_privado[pos]!=otra_secuencia.vector_privado[pos]) {
					sigo = false;
					son_iguales = false;
				}
				else
					pos++; 
			} // while (sigo && pos < total_utilizados) 
		}
			
		return (son_iguales);
	}
	
	/***********************************************************************/
	// Calcula la similitud entre dos vectores de enteros con la distancia 
	// euclidea. Su formula es dist(x, y) = v(x1 - y1)^2 + · · · + (xp - yp)^2
	
	double DistanciaEuclidea (SecuenciaEnteros a_comparar){
		
		double distancia_euclidea = 0;
		
		for(int i = 0; i < total_utilizados; i++){
			
			double resta = vector_privado[i] - a_comparar.Elemento(i);
			distancia_euclidea = resta*resta + distancia_euclidea;
		}
		distancia_euclidea = sqrt(distancia_euclidea);
		
		return distancia_euclidea;
	}
	
	/*********************************************************************/
	// Método que pinta la secuencia
	string ToString(void){
		
		string cadena = " ";
		for(int i = 0; i < total_utilizados; i++){
			cadena = cadena + " " + to_string(vector_privado[i]);
		}
		
		return cadena;
	}

};

/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

class SecuenciaReales
{

private:

	static const int TAMANIO = 50; // Número de casillas disponibles
	double vector_privado[TAMANIO];

	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas

public:

	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaReales (void)
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Métodos de lectura (Get) de los datos individuales

	// Devuelve el número de casillas ocupadas
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}

	// Devuelve el número de casillas disponibles
	int Capacidad (void)
	{
		return (TAMANIO);
	}

	/***********************************************************************/
	// Añade un elemento al vector.
	// Recibe: nuevo, el elemento que se va a añadir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adición se realiza si hay espacio para el nuevo elemento.
	// 		El nuevo elemento se coloca al final del vector.
	// 		Si no hay espacio, no se hace nada.

	void Aniade (double nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}

	/***********************************************************************/
	// Eliminar el dato de la posición dada por "indice".
	// Realiza un borrado físico (con desplazamiento y sustitución).
	//
	// PRE: 0 <= indice < total_utilizados

	void Elimina (int indice)
	{
		// Recorremos de izquierda a derecha toda las componentes
		// que hay a la derecha de la posición a eliminar
		//		Le asignamos a cada componente la que hay a su derecha

		if ((indice >= 0) && (indice < total_utilizados)) {

			int tope = total_utilizados-1; // posición del último

			for (int i = indice ; i < tope ; i++)
				vector_privado[i] = vector_privado[i+1];

			total_utilizados--;
		}
	}

	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice"
	//
	// PRE: 0 <= indice < total_utilizados

	double Elemento (int indice)
	{
		return vector_privado[indice];
	}

	/***********************************************************************/
	// Devuelve true si la secuencia está vacía

	bool EstaVacia (void)
	{
		return (total_utilizados == 0);
	}

	/***********************************************************************/
	// "Vacía" una secuencia

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Devuelve la posición del mínimo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int PosicionMinimo (int izda, int dcha)
	{
		int posicion_minimo;
		int minimo;

		minimo = vector_privado[izda];
		posicion_minimo = izda;

		for (int i = izda; i <= dcha ; i++) {

			if (vector_privado[i] < minimo){
				minimo = vector_privado[i];
				posicion_minimo = i;
			}
		}

		return (posicion_minimo);
	}

	/***********************************************************************/
	// Devuelve la posición del máximo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int PosicionMaximo (int izda, int dcha)
	{
		int posicion_maximo;
		int maximo;

		maximo = vector_privado[izda];
		posicion_maximo = izda;

		for (int i = izda; i <= dcha ; i++) {

			if (vector_privado[i] > maximo){
				maximo = vector_privado[i];
				posicion_maximo = i;
			}
		}

		return (posicion_maximo);
	}

	/***********************************************************************/
	// Devuelve el mínimo de la secuencia.
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	double Minimo (int izda, int dcha)
	{
		return (vector_privado[PosicionMinimo(izda, dcha)]);
	}


	/***********************************************************************/
	// Devuelve el máximo de la secuencia.
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	double Maximo (int izda, int dcha)
	{
		return (vector_privado[PosicionMaximo(izda, dcha)]);
	}

	/***********************************************************************/

};

class TablaRectangularReales
{

private:

    static const int NUM_FILS = 50; // Filas disponibles
    static const int NUM_COLS = 40; // Columnas disponibles
    
    double  matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS
    // PRE: 0 <= col_utilizadas < NUM_COLS
    
    int filas_utilizadas;
    int cols_utilizadas;

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaRectangularReales(void): filas_utilizadas(0), cols_utilizadas(0) {}
	
	/***********************************************************************/
	// Constructor--> Recibe "numero_de_columnas" que indica el número de 
	// columnas que deben tener TODAS las filas. 
	// PRE: numero_de_columnas <= MAX_COL

	TablaRectangularReales (int numero_de_columnas) : filas_utilizadas(0), 
		  cols_utilizadas(numero_de_columnas)
	{ }

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de enteros.  El número de 
	// elementos de la secuencia es el valor que se usa como "col_utilizadas"
	// PRE: primera_fila.TotalUtilizados() <= MAX_COL

	TablaRectangularReales (SecuenciaReales primera_fila)
		: filas_utilizadas(0), cols_utilizadas (primera_fila.TotalUtilizados())
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}
	
	/***********************************************************************/
	// Método de lectura: número máximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/***********************************************************************/
	// Método de lectura: número máximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/***********************************************************************/
	// Método de lectura: número real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/***********************************************************************/
	// Método de lectura: número real de columnas usadas

	int ColumnasUtilizadas (void)
	{
		return (cols_utilizadas);
	}

	/***********************************************************************/
	// Método de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < cols_utilizadas	
	
	double Elemento (int fila, int columna)
	{
		return (matriz_privada[fila][columna]);
	}

	/***********************************************************************/
	// Devuelve true si la tabla está vacía

	bool EstaVacia (void)
	{
		return (filas_utilizadas == 0);
	}
	
	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaReales Fila (int indice_fila)
	{
		SecuenciaReales fila;

		for (int col=0; col<cols_utilizadas; col++)
			fila.Aniade(matriz_privada[indice_fila][col]);

		return (fila);
	}

	/***********************************************************************/
	// Devuelve una columna completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_columna < cols_utilizadas
	
	SecuenciaReales Columna (int indice_columna)
	{
		SecuenciaReales columna;

		for (int fil=0; fil<filas_utilizadas; fil++)
			columna.Aniade (matriz_privada[fil][indice_columna]);

		return (columna);
	}

	/***********************************************************************/
	// Añade una fila completa (un objeto "SecuenciaEnteros")
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	
	void Aniade (SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva == cols_utilizadas)) {

			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[filas_utilizadas][col]=fila_nueva.Elemento(col);

			filas_utilizadas++;
		}
	}

	/***********************************************************************/
	// "Vacía" una tabla

	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
					
	/***********************************************************************/
	// Inserta una fila completa en una posición dada. 
	// La fila se porporciona en un objeto "SecuenciaEnteros".
	// 
	// Recibe: num_fila, la posición que ocupará "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase "SecuenciaEnteros". 
	//
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" será la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" será la nueva 
	//		 última fila (el resultado será equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva == cols_utilizadas) && 
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La última fila se copia en una NUEVA FILA que ocupa la 
			// posición "filas_utilizadas", la penúltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todavía) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) {
				
				for (int col = 0; col < numero_columnas_fila_nueva; col++)
					matriz_privada[fil][col]=matriz_privada[fil-1][col];
			}
			
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[num_fila][col]=fila_nueva.Elemento(col);	
			
			filas_utilizadas++; // Actualización del tamaño de la tabla.
		}
	}
	/*************************************************************************/
	// Método que cambia un numero en una posicion de la matriz
	void CambiaElemento(int fila, int columna, double elemento){
		matriz_privada[fila][columna] = elemento;
	}

	/***********************************************************************/
	// Elimina una fila completa, dada una posición. 
	// 
	// Recibe: num_fila, la posición de la fila a eliminar.
	// PRE:  0 <= num_fila < TotalUtilizados()
	
	void Elimina (int num_fila)
	{		
		// Comprobar precondiciones
		
		if ((0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones bajas. 
			// En la posición "num_fila" se copia la que está en la posición
			// siguiente ("num_fila"+1), en su lugar se copia que está en 
			// "num_fila"+2, ... y en la posición "total_utilizados"-2 se 
			// copia la de "total_utilizados"-1. 
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) {
			
				int num_columnas = cols_utilizadas;
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c]=matriz_privada[fil+1][c];
			}
			
			filas_utilizadas--; // Actualización del tamaño de la tabla.
		}
	}	
	
	/***********************************************************************/
	// Devuelve TRUE si la matriz contiene el valor "buscado"
	
	bool Contiene (double buscado)
	{
		bool encontrado = false;

		// Recorrido por columnas 

		int col = 0;

		while (col < cols_utilizadas && !encontrado) {

			int fil=0;

			while (fil < filas_utilizadas && !encontrado) {

				if (matriz_privada[fil][col] == buscado)
					encontrado = true;
				
				fil++;

			} // while fil

			col++; 

		} // while col

		return (encontrado);
	}

};

//////////////////////////////////////////////////////////////////////////////

class MapaDistancias{

private:
	TablaRectangularReales mapa;
	int num_ciudades;

public:
	/********************************************************************/
	// constructor que tiene una TablaRectangularReales como argumento
	MapaDistancias(TablaRectangularReales matriz): mapa(matriz)
	{ num_ciudades = matriz.ColumnasUtilizadas(); }
	
	/********************************************************************/
	// constructor cuyo arguemtno es el numero de ciudades. Se añade un -1 en 
	// la distancias de todas las ciudades para rellenar la matriz 
	// posteriormente
	MapaDistancias(int numero): num_ciudades(numero)
	{
		SecuenciaReales fila;
		
		for(int i = 0; i < num_ciudades; i++)
			fila.Aniade(-1);
		
		TablaRectangularReales matriz(fila);
		mapa = matriz;
			
		for(int i = 0; i < num_ciudades; i++)
			mapa.Aniade(fila);
	}
	
	/*******************************************************************/
	// Método para rellenar el mapa. Sabemos que el mapa está formado por 
	// una tabla de reales rectangular simétrica. POr lo tanto, si la matriz
	// rellena no es simétrica, se volverán a pedir todos los datos.
	
	void RellenaMapa(void){
		
		for (int fil = 0; fil< num_ciudades; fil++){
			cout<<endl;
			if(!(fil == num_ciudades-1))
				cout<< " Introduzca la distancia de la ciudad " <<fil+1 << ": "
					<< endl;
			
			for(int col = 0; col < num_ciudades; col++){
				if(fil == col) //la distancia de una ciudad consigo misma es 0
					mapa.CambiaElemento(fil, col, 0);
				else{
					if(mapa.Elemento(fil, col) == -1){//si todavía no sabemos  
													//la distancia entre dos 
													//ciudades, la pedimos
						do{
							cout<< " con la ciudad "<< col+1 << ": ";
							double distancia;
							cin>> distancia;
							mapa.CambiaElemento(fil, col, distancia);
						}while(mapa.Elemento(fil, col) < 0);
						
						//sabemos que la matriz es simétrica, porque la  
						//distancia de la ciudad 0 a la 1, es la misma 
						//distancia que la de la ciudad 1 a la 0. 
						mapa.CambiaElemento(col, fil, mapa.Elemento(fil, col));
					}
				}
			}
		}
		
	}
	
	/*************************************************************************/
	// Método que devuelve la distancia entre dos ciudades
	//
	// PRE: 0 <= ciudad1 <= num_ciudades
	// PRE: 0 <= ciudad2 <= num_ciudades
	
	double DistanciaCiudades (int ciudad1,int ciudad2){
		
		return mapa.Elemento(ciudad1, ciudad2);
	}
	
	
	/*******************************************************************/
	// método que devuelve cuál es la ciudad con más conexiones
	
	int CiudadMasConexiones(void){
		
		//se crea un vector que guarda cuántas conexiones directas tiene 
		//cada ciudad
		int conexiones_directas_ciudades[mapa.CapacidadColumnas()] = {0};
		int ciudad_mas_conexiones = 0;
	
		//rellenamos el vector conexiones_directas_ciudades[]. Para ello vamos 
		//mirando fila por fila de la matriz y añadimos +1 a la ciudad de la  
		//fila, cada vez que en una de sus columnas la distancia =/= 0
		for(int i = 0; i < num_ciudades; i++){
			for(int j = 0; j < num_ciudades; j++){
				if(mapa.Elemento(i, j) != 0)
					conexiones_directas_ciudades[i]++;
			}
		}
		
		//calculamos cual es la ciudad con mas conexiones.
		for(int i = 1; i < num_ciudades; i++){
			if(conexiones_directas_ciudades[i] > 
							conexiones_directas_ciudades[ciudad_mas_conexiones])
			ciudad_mas_conexiones = i;
		}
		
		return ciudad_mas_conexiones;
	}
	
	/**********************************************************************/
	// Método que devuelve una SecuenciaEnteros con las ciudades directamente
	// conectadas con "ciudad"
	//
	// PRE: 0 <= ciudad <= num_ciudades
	SecuenciaEnteros CiudadesConectadasCon(int ciudad){
		
		SecuenciaEnteros conexiones_ciudad;
		//vamos mirando la fila de la ciudad en la matriz y cada vez que en una  
		//de columnas aparezca una distancia distinta de 0, mostramos la ciudad 
		//que corresponde con la columna
		for(int i = 0; i < num_ciudades; i++){
			if(mapa.Elemento(ciudad, i) != 0)
				conexiones_ciudad.Aniade(i+1);
		}
		
		return conexiones_ciudad;
	}
	
	/************************************************************************/
	// Método que busca la ciudad intermedia más cercana a dos ciudades 
	// indirectamente conectadas
	//
	// PRE: mapa.Elemento(ciudad1, ciudad2) != 0
	// PRE: 0 <= ciudad1 <= num_ciudades
	// PRE: 0 <= ciudad2 <= num_ciudades
	int CiudadIntermedia( int ciudad1, int ciudad2){
		
		double distancia_total; 
		double distancia_minima; 
		// si no existe ninguna ciudad intermedia, el metodo devolverá -1
		int ciudad_intermedia = -1;
		bool existe_ciudad_intermedia = false;
		
		//se mira cada una de las ciudades para saber si es una ciudad 
		// intermedia
		for(int i = 0; i <= num_ciudades; i++){
			
			double distancia_ciudad1 = mapa.Elemento(ciudad1, i);
			double distancia_ciudad2 = mapa.Elemento(ciudad2, i);
			
			if(distancia_ciudad1 != 0 && distancia_ciudad2 != 0){
				
				existe_ciudad_intermedia = true;
				// por ahora, esa es la ciudad intermedia con menor distancia
				distancia_minima = distancia_ciudad1 + distancia_ciudad2;
				ciudad_intermedia = i;
			}
		}
		
		if(existe_ciudad_intermedia){
			
			// se comprueba si hay alguna ciudad intermedia de menor distancia
			for(int i = ciudad_intermedia; i < num_ciudades; i++){
				
				double distancia_ciudad1 = mapa.Elemento(ciudad1, i);
				double distancia_ciudad2 = mapa.Elemento(ciudad2, i);
				
				// si la ciudad es una ciudad intermedia, miramos la distancia
				if(distancia_ciudad1 != 0 && distancia_ciudad2 != 0){
					
					distancia_total = distancia_ciudad1 + distancia_ciudad2;
					
					if(distancia_total < distancia_minima){
						
						distancia_minima = distancia_total;
						ciudad_intermedia = i;
					}
				}
			}
		}
		
		return ciudad_intermedia;
	}
	
	/*********************************************************************/
	// Método que recibe una serie de ciudades y devuelve si tienen todas 
	// conexiones directas entre sí o no
	
	bool CiudadesConectadas(SecuenciaEnteros ciudades){
		
		bool estan_conectadas = true;
		
		// se va mirando ciudad por ciudad guardada en la secuencia ciudades
		// y se mira si está conectada directamente con el resto de ciudades
		// del vector
		for(int i = 0; i < ciudades.TotalUtilizados() && estan_conectadas; i++){
			//miramos cuál es la primera ciudad a comparar
			int ciudad_a_comparar = ciudades.Elemento(i);
			
			//vamos a comparar ciudad_a_comparar con el resto de ciudades 
			//siguientes a ella
			int siguiente_ciudad = ciudades.Elemento(i + 1);
			
			for(int j = siguiente_ciudad; j < ciudades.TotalUtilizados(); j++){
				//si en la matriz primera, la distancia entre una ciudad y otra  
				//de las que estamos comparando es 0, entonces no están 
				//conectadas. 
				if(mapa.Elemento(ciudad_a_comparar, j) == 0)
					estan_conectadas = false;
			}
		}
		return estan_conectadas;
	}
	
	/********************************************************************/
	// Método que devuelve si dos ciudades están directamente conectadas o no
	bool DosCiudadesConectadas (int ciudad1, int ciudad2){
		
		return (mapa.Elemento(ciudad1, ciudad2) != 0);
	}
	
};

//////////////////////////////////////////////////////////////////////////////

int main(){
	cout.setf(ios::fixed);
	
	cout<<endl;
	
	Lector lector(" Introduzca el numero de ciudades: ");
	int num_ciudades = lector.LeeEnteroEnRango(1, 40);

	MapaDistancias distancia_ciudades(num_ciudades);
	
	//rellenamos el mapa de distancias
	distancia_ciudades.RellenaMapa();
	
	/***********************************************************************/
	// Mostrar los datos del mapa 

	cout << endl;
	
	//encabezado
	cout<<setw(15)<<" ";
	for(int i = 0; i < num_ciudades; i++){
		cout << setw(15) << "Ciudad " << i+1;
	}
	cout << endl;
	
	//cada fila
	for(int i = 0; i < num_ciudades; i++){
		cout << setw(15) << "Ciudad " << i+1;
		
		for(int j = 0; j < num_ciudades; j++){
			cout<<setw(15) << distancia_ciudades.DistanciaCiudades(i,j);
		}
		cout<<endl<<endl;
	}
	
	/*********************************************************************/
	// a) mostramos cuál es la ciudad con más conexiones
	
	cout<<endl;
	cout<<" La ciudad con más conexiones es: " 
		<< distancia_ciudades.CiudadMasConexiones() + 1
		<<endl;
	
	/*********************************************************************/
	// b) pedimos una ciudad y mostramos sus conexiones directas
	
	lector.SetTitulo(" Introduzca una ciudad: ");
	int ciudad = lector.LeeEnteroEnRango(1, num_ciudades);
	
	cout<< " Las conexiones directas de la ciudad " << ciudad << " son: " 
		<< distancia_ciudades.CiudadesConectadasCon(ciudad-1).ToString()
		<< endl << endl;
	
	/*********************************************************************/
	// c) Dadas dos ciudades i y j para las cuales no existe un camino directo, 
	// obtener aquella ciudad intermedia z que permita hacer el trayecto entre 
	// i y j de la forma más económica posible.
	
	cout<< " Introduzca dos ciudades: " << endl;
	lector.SetTitulo(" Ciudad A: ");
	int ciudad_a = lector.LeeEnteroEnRango(1, num_ciudades);
	lector.SetTitulo(" Ciudad B: ");
	int ciudad_b = lector.LeeEnteroEnRango(1, num_ciudades);
	
	if(distancia_ciudades.DosCiudadesConectadas(ciudad_a -1, ciudad_b -1))
		cout << " Las ciudades están ya conectadas. ";
	else{
		int ciudad_intermedia = distancia_ciudades.CiudadIntermedia(ciudad_a-1, 
																	ciudad_b-1);
		if(ciudad_intermedia == -1 )
			cout << " No existe una ciudad intermedia entre las ciudades"
				<< " indicadas";
		else
			cout<< " La ciudad intermedia mas proxima entre las ciudades "
				<< "indicadas es: " << ciudad_intermedia + 1;
	}
	cout<<endl<<endl;
	
	/*********************************************************************/
	// d) Dadas distintas ciudades mostrar si están todas conectadas entre 
	// sí o no.
	
	int num;
	SecuenciaEnteros ciudades;
	bool seguir_leyendo = true;
	int TERMINADOR = -1; 
	
	do{
		ciudades.EliminaTodos();
		cout<<endl
		<< " Introduzca distintas ciudades (Terminador = -1) : ";
	
		while(seguir_leyendo){
			cin>>num;
			
			if(num == TERMINADOR)
				seguir_leyendo = false;
			else
				ciudades.Aniade(num-1);
		}
		
		if(distancia_ciudades.CiudadesConectadas(ciudades))
			cout<<" Todas las ciudades están conectadas entre si. ";
		else
			cout<<" No hay conexion directa entre todas las ciudades. ";
			
	}while(ciudades.TotalUtilizados() > num_ciudades);
	
	
	
	cout << endl << endl;
	
	return 0;
}
