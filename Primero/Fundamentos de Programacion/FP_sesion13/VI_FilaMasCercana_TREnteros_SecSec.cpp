/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 46: el programa está formado por la clase TablaRectangularEnteros 
	con un método que busca la fila de la matriz que más se parece a un vector 
	de enteros (clase SecuenciaEnteros) al que llamaremos referencia. El método 
	devolverá el número de la fila. La similitud entre dos vectores viene dada 
	por la distancia euclídea entre ambos (método de SecuenciaEnteros)
	Además, la búsqueda solo se hará sobre un conjunto seleccionado de filas de 
	la tabla, enumeradas en la secuencia de enteros filas_a_comparar (un objeto 
	de la clase SecuenciaEnteros).
	
	
*/

#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>

using namespace std;

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


/////////////////////////////////////////////////////////////////////////////
// El tipo de dato PosicionEnMatriz se emplea para guardar posiciones 	
// dentro de una matriz: se registra la pareja (fila, columna)
	
struct PosicionEnMatriz {
	int fila;
	int columna;
};

/////////////////////////////////////////////////////////////////////////////
// La clase "SecuenciaPosicionEnMatriz" es útil para representar una secuencia
// de  posiciones (coordenadas) en una tabla bidimensional.	
	
class SecuenciaPosicionEnMatriz
{
private:

	static const int TAMANIO = 50; // Número de casillas disponibles
	PosicionEnMatriz vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas

public: 
	
	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaPosicionEnMatriz (void) 
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

	void Aniade (PosicionEnMatriz nuevo)
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

	PosicionEnMatriz Elemento (int indice)
	{
		return vector_privado[indice];
	}
	
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// Tabla rectangular de enteros

class TablaRectangularEnteros
{

private:

    static const int MAX_FIL = 50; // "filas" disponibles
    static const int MAX_COL = 40;

    SecuenciaEnteros vector_privado[MAX_FIL];

    // PRE: 0 <= filas_utilizadas <= MAX_FIL
    // PRE: 0 <= cols_utilizadas <= MAX_COL
    
    int filas_utilizadas;
    int cols_utilizadas;

public:
	
	
	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaRectangularEnteros(void): filas_utilizadas(0),cols_utilizadas(0) { }

	/***********************************************************************/
	// Constructor--> Recibe "numero_de_columnas" que indica el número de 
	// columnas que deben tener TODAS las filas. 
	// PRE: numero_de_columnas <= MAX_COL


	TablaRectangularEnteros (int numero_de_columnas)
		: filas_utilizadas(0), cols_utilizadas(numero_de_columnas)
	{ }

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de enteros.  El número de 
	// elementos de la secuencia es el valor que se usa como "col_utilizadas"
	// PRE: primera_fila.TotalUtilizados() <= MAX_COL

	TablaRectangularEnteros (SecuenciaEnteros primera_fila)
		: filas_utilizadas(0), cols_utilizadas (primera_fila.TotalUtilizados())
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}

	/***********************************************************************/
	// Método de lectura: número máximo de filas

	int CapacidadFilas (void)
	{
		return (MAX_FIL);
	}

	/*****************************************************************/
	// Método de lectura: número máximo de columnas

	int CapacidadColumnas (void)
	{
		return (MAX_COL);
	}

	/*****************************************************************/
	// Método de lectura: número real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/*****************************************************************/
	// Método de lectura: número real de columnas usadas

	int ColumnasUtilizadas (void)
	{
		return (cols_utilizadas);
	}

	/*****************************************************************/
	// Método de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < cols_utilizadas	
	
	int Elemento (int fila, int columna)
	{
		return ((vector_privado[fila]).Elemento(columna));
	}

	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaEnteros Fila (int indice_fila)
	{
		return (vector_privado[indice_fila]);
	}

	/*****************************************************************/
	// Devuelve una columna completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_columna < cols_utilizadas
	
	SecuenciaEnteros Columna (int indice_columna)
	{
		SecuenciaEnteros columna;

		for (int fil=0; fil<filas_utilizadas; fil++)
			columna.Aniade ((vector_privado[fil]).Elemento(indice_columna));

		return (columna);
	}

	/***********************************************************************/
	// Añade una fila completa (un objeto "SecuenciaEnteros")
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	
	void Aniade (SecuenciaEnteros fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < MAX_FIL) && 
			(numero_columnas_fila_nueva == cols_utilizadas)) {

			vector_privado[filas_utilizadas] = fila_nueva;

			filas_utilizadas++;
		}
	}


	/***********************************************************************/
	// "Vacía" una tabla

	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
	
	/*****************************************************************/
	// Calcula si dos matrices rectangulares son iguales
	// Compara la tabla implícita con "otra" (tabla explícita) 

	bool EsIgual (TablaRectangularEnteros otra)
	{
		bool son_iguales = true; 
		
		if ((filas_utilizadas != otra.FilasUtilizadas()) ||  
			 (cols_utilizadas != otra.ColumnasUtilizadas()))		
			
			son_iguales = false;
		
		else {
			
			// Recorrido por filas 
	
			int fil = 0;
			
			while (fil < filas_utilizadas && !son_iguales) {
	
				SecuenciaEnteros una_fila = Fila (fil);
				SecuenciaEnteros otra_fila = otra.Fila (fil);	
				
				if (una_fila.EsIgual(otra_fila))
					fil++;
				else
					son_iguales = false;
					
			} // while fil
					
		} // else 
	
		return (son_iguales);
	}
	
	/***********************************************************************/
	// Devuelve la traspuesta de la matriz (si es posible calcularse)
	// PRE: filas_utilizadas <= MAX_COL
	// PRE: cols_utilizadas  <= MAX_FIL
	// Si no se puede calcular la traspuesta se devuelve una matriz nula. 
	
	TablaRectangularEnteros Traspuesta (void)
	{
	    TablaRectangularEnteros traspuesta; // Inicialmente vacía
			    
		if ((filas_utilizadas <= MAX_COL) && (cols_utilizadas <= MAX_FIL)) {
		
			// La traspuesta tiene tantas filas como columnas tiene la 
			// matriz original

			TablaRectangularEnteros solucion (filas_utilizadas);


			SecuenciaEnteros columna; // Las filas de "traspuesta" serán las 
								      // columnas de la tabla implícita 

			for (int col = 0; col < cols_utilizadas; col++){

				columna = Columna(col);
				solucion.Aniade(columna); 
			}
			
			traspuesta = solucion;
		} 

		return (traspuesta);
	}	
	
	/***********************************************************************/
	// Calcula si una matriz es simétrica.
	// CONDICIÓN NECESARIA: debe ser cuadrada. 
	// Este método comprueba directamente si cada componente es igual a
	// su simétrica, parando el recorrido cuando encuentre una componente
	// que no lo verifique.
	//
	// Evita el cálculo de la traspuesta, y el problema que puede surgir
	// si no se puede calcular la traspuesta de la matriz por problemas de
	// capacidad.

	bool EsSimetrica (void)
	{
		bool es_simetrica = true;
		
		// Si el número de filas y columnas no coinciden, no hay que seguir
		// porque la matriz no es simétrica.
		
		es_simetrica = (filas_utilizadas == cols_utilizadas);

		if (es_simetrica) {
		
			int f=0; 
			
			while (f<filas_utilizadas && es_simetrica) {
				
				int c=0; 
				
				while (c<cols_utilizadas && es_simetrica) {
			
					if (Elemento(f,c) != Elemento(c,f)) 
						es_simetrica = false;
						
					c++;
					
				} // while c
	
				f++;
					
			} // while f
			
		} // if (es_simetrica)
		
		return (es_simetrica);
	}
	
	
	/*****************************************************************/
	// Inserta una fila completa en una posición dada. 
	// La fila se porporciona en un objeto "SecuenciaEnteros".
	// 
	// Recibe: num_fila, la posición que ocupará "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase SecuenciaEnteros. 
	//
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" será la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" será la nueva 
	//		 última fila (el resultado será equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaEnteros fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < MAX_FIL) && 
			(numero_columnas_fila_nueva == cols_utilizadas) && 
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La última fila se copia en una NUEVA FILA que ocupa la 
			// posición "filas_utilizadas", la penúltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todavía) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) 			
				vector_privado[fil]=vector_privado[fil-1];
			
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			vector_privado[num_fila]=fila_nueva;	
			
			filas_utilizadas++; // Actualización del tamaño de la tabla.
		}
	}

	/*****************************************************************/
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
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) 
				vector_privado[fil]=vector_privado[fil+1];
			
			filas_utilizadas--; // Actualización del tamaño de la tabla.
		}
	}
	
	/*****************************************************************/
	// Devuelve TRUE si la matriz contiene el valor "buscado"
	
	bool Contiene (int buscado)
	{
		bool encontrado = false;

		// Recorrido por filas 

		int fil = 0;

		while (fil < filas_utilizadas  && !encontrado) {

			SecuenciaEnteros una_fila = Fila (fil);
			
			int pos_buscado = una_fila.Posicion(buscado,0,cols_utilizadas-1);

			if (pos_buscado != -1) 
				encontrado = true;
			else 
				fil++; 

		} // while fil

		return (encontrado);
	}
		
	/*****************************************************************/
	// Encontrar un dato en la matriz y devolver su posición.
	// El valor devuelto contiene información acerca de la posición 
	// (fila y columna) de "buscado".  
	// 		En el caso de que no esté contendrá {-1,-1}. 
	// La consulta de la fila y la columna se delega en los métodos de 
	// la clase "PosicionEnMatriz" 

	PosicionEnMatriz PrimeraOcurrencia (int buscado)
	{
		PosicionEnMatriz posicion_dato_buscado = {-1,-1};
      
		bool encontrado = false;

		// Recorrido por filas 

		int fil = 0;
		
		while (fil < filas_utilizadas && !encontrado) {

			SecuenciaEnteros una_fila = Fila (fil);
			
			int pos_buscado = una_fila.Posicion(buscado,0,cols_utilizadas-1);

			if (pos_buscado != -1) {
				encontrado = true;
				posicion_dato_buscado.fila = fil;
				posicion_dato_buscado.columna = pos_buscado;		
			}
			else 
				fil++; 

		} 
      
		return (posicion_dato_buscado);
	} 

	/***********************************************************************/
	// Devuelve true si la tabla está vacía

	bool EstaVacia (void) 
	{
		return (filas_utilizadas == 0);
	}		

	/***********************************************************************/
	// Método para pintar la matriz
	
	string ToString(string titulo){
		
		string cad;
		
		cad = "\n" + titulo + "\n"; 	
		cad = cad + "\n--------------------------------------\n"; 
		
		for (int i = 0; i < filas_utilizadas; i++){
				
			SecuenciaEnteros la_secuencia = vector_privado[i];
			
			cad = cad + "Fila " + to_string(i); 
			cad = cad + la_secuencia.ToString() + "\n";
		}
		
		cad = cad + "--------------------------------------\n"; 
		cad = cad + "\n\n";
		
		return cad;
	}
	
	/***********************************************************************/
	// Método que busca la fila de la matriz que más se parezca a un vector de 
	// enteros (clase SecuenciaEnteros) al que llamaremos referencia. Además,
	// se introduce  el objeto filas, que contendrá el numero de las filas 
	// entre las que se quiere encontrar al vector más parecido.
	// El método devolverá el número de la fila.
	//
	// PRE: 0 <= todos los elementos del objeto filas <= NUM_FILS 
	// PRE: referencia.TotalUtilizados() == cols_utilizadas <= MAX_COL
	int FilaMasParecida (SecuenciaEnteros referencia, SecuenciaEnteros filas){
		
		// índice del elemento del objeto filas.
		int i = 0;
		
		// distancia euclidea minima
		double dist_euc_min = 
				referencia.DistanciaEuclidea(vector_privado[filas.Elemento(0)]);
				
		// índice de la fila más parecida a referencia
		int fila_mas_parecida = filas.Elemento(0);
		
		// el contador sirve para calcular el numero de veces que se tendrá que 
		// calcular la distancia euclidea entre referencia y una fila.
		int contador = 0;
		
		// se tendrá que calcular la distancia euclidea entre referencia y una
		// fila según el numero de filas indicado por el objeto filas.
		while(contador < filas_utilizadas){
			i++;
			
			// distancia euclídea entre referencia y la fila de posicion 
			// filas.Elemento(i)
			double distancia = 
				referencia.DistanciaEuclidea(vector_privado[filas.Elemento(i)]);
			
			if(dist_euc_min > distancia){
				fila_mas_parecida = filas.Elemento(i);
				dist_euc_min = distancia;
			}
			
			contador++;
		}
		
		return fila_mas_parecida;
	}
			
};

/////////////////////////////////////////////////////////////////////////////


/***************************************************************************/


int main (void)
{
	cout<<endl;

	int num_filas_matriz;
	int num_cols_matriz;
	int num;
	int TERMINADOR = -1;
	bool seguir_leyendo = true;
	
	SecuenciaEnteros una_fila; 
	
	cout<<"Introduzca el numero de filas de la matriz: ";
	cin>>num_filas_matriz;
	cout<<"Introduzca el numero de columnas de la matriz: ";
	cin>>num_cols_matriz;
	
	TablaRectangularEnteros matriz(num_cols_matriz);
	
	// rellenamos la matriz.
	
	for(int j = 0; j < num_filas_matriz; j++){
		
		do{
			una_fila.EliminaTodos();
			
			cout<<endl << "(Terminador = -1)";
			cout<<endl<<"Introduzca los enteros de la fila "<< j+1 << ": ";
			
			while(seguir_leyendo){
				
				cin >> num;
				
				if (num == TERMINADOR)
					seguir_leyendo = false;
				else
					una_fila.Aniade(num);
			}
			seguir_leyendo = true;
			
		}while(una_fila.TotalUtilizados() != num_cols_matriz);
			
			
		cout<<"Fila "<< j+1 << ": " << una_fila.ToString() << endl;	
		
		matriz.Aniade(una_fila);
	}
	
	/***********************************************************************/
	// Mostrar los datos de la matriz

	cout << endl;
	cout << matriz.ToString("Matriz original");
	cout << endl;

	/**********************************************************************/
	// Leer SecuenciaEnteros referencia. Un objeto que se comparará con 
	// algunas filas de la matriz.
	SecuenciaEnteros referencia;
	bool num_correcto;
	
	do{
		referencia.EliminaTodos();
		
		cout<<endl;
		cout<<"(Terminador = -1)"<<endl;
		cout<<"Introduzca una secuencia de enteros a comparar: ";
		num_correcto = true;
		
		while(num_correcto){
			cin>>num;
			
			if(num != TERMINADOR)
				referencia.Aniade(num);
			else
				num_correcto = false;
		}
	}while(referencia.TotalUtilizados() != num_cols_matriz);
	
	cout<<"Secuencia a comparar: "<<referencia.ToString();
	cout<<endl;
	
	/**********************************************************************/
	// Leer las filas que se quieren comparar e introducirlas en un objeto de 
	// la clase SecuenciaEnteros
	SecuenciaEnteros filas_comp;
	num_correcto = true;
	num = 0;
	
	cout<<endl;
	cout<<"(Terminador = -1)"<<endl;
	cout<<"Introduzca las filas que se quieren comparar : ";
	while(num_correcto){
		cin>>num;
		
		if(num != TERMINADOR && num < num_filas_matriz && num >= 0)
			filas_comp.Aniade(num);
		else
			if(num == TERMINADOR)
				num_correcto = false;
			else{	
				if(num >= num_filas_matriz || num < 0)
					cout<<"--->No existe la fila "<<num<< " en la matriz"<<endl;
			}
	}
	cout<<"Filas que se van a comparar: "<<filas_comp.ToString();
	
	/***********************************************************************/
	// Cálculo de cuál es la fila más parecida a referencia. Posteriormente, 
	// la mostramos.
	int fila_buscada = matriz.FilaMasParecida(referencia, filas_comp);
	
	cout<<endl<<endl
		<<"La fila más parecida a la secuencia introducida es: "
		<<fila_buscada;
	
	cout << endl << endl;

	return 0;
}

/***************************************************************************/
