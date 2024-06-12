/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 42: el programa lee una matriz propuesta por el usuario y se 
	encargará de, en cada fila, leer un entero y sumar tantos datos reales
	como indica el entero, luego leer el siguiente entero y hacer lo mismo.
	Así, se creará otra matriz nueva. La nueva matriz se creará gracias a un 
	método de TablaDentadaReales que se llama SumaMatrizReales().
	
	
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
				es_real =(caracter_posicion_j>='0' && caracter_posicion_j <='9')
							|| caracter_posicion_j == '.';		
				j++;
			}
			return es_real; //true si es un positivo y false si no lo es.	
		}
};

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
		double minimo;

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
		double maximo;

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
// Tabla dentada de reales
//
// Representación: matriz "clásica"

class TablaDentadaReales
{
	
private:

    static const int NUM_FILS = 50;  // Filas disponibles
    static const int NUM_COLS = 40;  // Columnas disponibles

    double matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS

    int filas_utilizadas;

    // PRE: 0 <= num_cols_utilizadas[i] <= NUM_COLS
    //      para i=0,1,...,filas_utilizadas-1
    // Número de columnas ocupadas en cada fila

    int num_cols_utilizadas[NUM_FILS] = {0};

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaDentadaReales (void) : filas_utilizadas(0) { }
	
	/***********************************************************************/
	// Constructor--> Recibe una secuencia de caracteres que será la primera 
	// fila de la tabla. 

	TablaDentadaReales (SecuenciaReales primera_fila)
		: filas_utilizadas(0)
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}
	
	/***********************************************************************/
	// Método de lectura: número máximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/*****************************************************************/
	// Método de lectura: número máximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/*****************************************************************/
	// Método de lectura: número real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/*****************************************************************/
	// Método de lectura: número real de columnas usadas en la fila "fila"
	// PRE: 0 <= fila < filas_utilizadas
	
	int ColumnasUtilizadas (int fila)
	{
		return (num_cols_utilizadas[fila]);
	}

	/*****************************************************************/
	// Método de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < num_cols_utilizadas[fila]	
	
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
	
	/***********************************************************************/
	// "Vacía" una tabla
	
	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
	
	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaCaracteres")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaReales Fila (int indice_fila)
	{
		SecuenciaReales la_fila;
				
		int num_columnas = num_cols_utilizadas[indice_fila];
			
		for (int c=0; c<num_columnas; c++) 
			la_fila.Aniade (matriz_privada[indice_fila][c]);
		
		return (la_fila);
	}

	/*****************************************************************/
	// Añade una fila completa. La fila se porporciona en un objeto de 
	// la clase "SecuenciaCaracteres".
	// PRE:  fila_nueva.TotalUtilizados() <= NUM_COLS
	// PRE:  filas_utilizadas < NUM_FILS
	
	void Aniade (SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva <= NUM_COLS)) {

			for (int c=0; c<numero_columnas_fila_nueva; c++) 
				matriz_privada[filas_utilizadas][c] = fila_nueva.Elemento(c);

			num_cols_utilizadas[filas_utilizadas]=numero_columnas_fila_nueva;
			
			filas_utilizadas++;
		}
	}

	/*****************************************************************/
	// Calcula si dos matrices dentadas son iguales

	bool EsIgual (TablaDentadaReales otra_tabla)
	{
		bool son_iguales = true; 
		
		if (filas_utilizadas != otra_tabla.FilasUtilizadas())
			
			son_iguales = false;
		
		else {
			
			int f=0; 
			
			while (f<filas_utilizadas && son_iguales) {
				
				if (num_cols_utilizadas[f] != otra_tabla.ColumnasUtilizadas(f)) 
				
					son_iguales = false;	
				
				else {
					
					int c=0; 
					
					while (c<num_cols_utilizadas[f] && son_iguales) {
				
						if (matriz_privada[f][c] != otra_tabla.Elemento(f,c)) 
							son_iguales = false;
							
						c++;
						
					} // while c
		
					f++;
					
				} // else 
					
			} // while f
					
		} // else 
	
		return (son_iguales);
	}
	
	/*****************************************************************/
	// Inserta una fila completa en una posición dada. 
	// La fila se porporciona en un objeto "SecuenciaCaracteres".
	// 
	// Recibe: num_fila, la posición que ocupará "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase SecuenciaCaracteres. 
	//
	// PRE:  fila_nueva.TotalUtilizados() <= NUM_COLS
	// PRE:  filas_utilizadas <= NUM_FILS
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" será la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" será la nueva 
	//		 última fila (el resultado será equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaReales fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva <= NUM_COLS) &&
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La última fila se copia en una NUEVA FILA que ocupa la 
			// posición "filas_utilizadas", la penúltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todavía) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) {	
			
				int num_columnas = num_cols_utilizadas[fil-1];
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c] = matriz_privada[fil-1][c]; 
					
				num_cols_utilizadas[fil] = num_cols_utilizadas[fil-1];
			}
					
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			for (int c=0; c<numero_columnas_fila_nueva; c++) 
				matriz_privada[num_fila][c] = fila_nueva.Elemento(c);
			
			num_cols_utilizadas[num_fila] = numero_columnas_fila_nueva;
			
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
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) {
			
				int num_columnas = num_cols_utilizadas[fil+1];
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c]=matriz_privada[fil+1][c];
					
				num_cols_utilizadas[fil] = num_cols_utilizadas[fil+1];
			}
			
			filas_utilizadas--; // Actualización del tamaño de la tabla.
		}
	}
		
	/*********************************************************************/
	// Forma un string con el contenido de la tabla.  
	// La primera línea es el encabezamiento indicado en "titulo".
	
	string ToString (string titulo)
	{
		string cad; 
		
		cad = "\n" + titulo + "\n"; 	
		cad = cad + "\n--------------------------------------\n"; 
		
		for (int fila=0; fila<filas_utilizadas; fila++) {
	
			SecuenciaReales la_secuencia = Fila(fila);
			
			int num_datos = la_secuencia.TotalUtilizados();
	
			cad = cad + "Fila " + to_string(fila+1); 
			cad = cad + " (" + to_string(num_datos) + " datos): "; 
			cad = cad + la_secuencia.ToString() + "\n";
		}
		
		cad = cad + "--------------------------------------\n"; 
		cad = cad + "\n\n";
		
		return (cad); 
	}
	
	/*****************************************************************/
	// Método que se encarga de crear una secuencia de reales que sea la suma
	// de los numeros de la fila. Primero se añade un entero, y luego la suma  
	// de los reales que le siguen. 
	//
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaReales SumaFilaReales (int indice_fila){
		
		SecuenciaReales una_fila;
		
		int pos_entero_fila = 0;
		double suma = 0;
		
		
		if(DatosCorrectosSumaFila(indice_fila)){
			do{
				int entero = matriz_privada[indice_fila][pos_entero_fila];
				//primero se añade el numero entero
				una_fila.Aniade(entero);
				
				for(int i = 1; i <= entero; i++){
									
					suma += matriz_privada[indice_fila][pos_entero_fila + i];
				}
				//después se añade la suma de los reales posteriores al entero
				una_fila.Aniade(suma);
				
				//se busca el siguiente entero
				pos_entero_fila += entero + 1;
				suma = 0;
				
			}while(pos_entero_fila < ColumnasUtilizadas(indice_fila));
		}
		
		return una_fila;
	}
	
	/*********************************************************************/
	// Método que se encarga de crear una matriz con todas las filas formadas
	// por un entero y la suma de los reales posteriores.
	
	TablaDentadaReales SumaMatrizReales(){
		
		TablaDentadaReales nueva;
		
		for(int i = 0; i < filas_utilizadas; i++){
			
			SecuenciaReales una_fila = SumaFilaReales(i);
			nueva.Aniade(una_fila);
		}
		
		return nueva;
	}
	
	
private:
	/********************************************************************/
	// Este método comprueba que la fila cuyos numeros se quieren sumar, está 
	// correctamente definida. Para que esto ocurra es necesario que por cada 
	// numero entero introducido existan ese numero de reales detrás de él.
	// Además, cada posicion de la fila donde supuestamente exista un entero, 
	// debe cumplirse también. 
	//
	// PRE: 0 <= indice_fila < filas_utilizadas
	bool DatosCorrectosSumaFila (int indice_fila){
		
		bool son_correctos = true;
		int pos = 0;
		
		do{
			double num_entero_principal = matriz_privada[indice_fila][pos];
			
			// si el numero que debe ser un entero, no es un entero, entonces 
			// los datos no son correctos.
			if(num_entero_principal- int(matriz_privada[indice_fila][pos]) !=0)
				son_correctos = false;
			
			// si el numero entero principal es negativo, los datos son 
			// incorrectos, porque no pueden existir -3 numeros detras, por
			// ejemplo.
			if(num_entero_principal < 0)
				son_correctos = false;
			
			// definimos cuándo termina dicha secuencia de numeros detrás del 
			// entero y pos = siguiente entero definido.
			else{
				pos = pos + num_entero_principal + 1;
			}
			
		}while(pos < ColumnasUtilizadas(indice_fila) && son_correctos);
		
		// comprobar que la posicion del ultimo numero +1 concuerda con el 
		// numero de columnas que deberían estar rellenas.
		if(pos != ColumnasUtilizadas(indice_fila))
			son_correctos = false;
			
		return son_correctos;
	}

};

///////////////////////////////////////////////////////////////////////////

int main(){
	
	cout<<endl;

	double num;
	const int TERMINADOR = -1;
	bool seguir_pidiendo = true;
	Lector lector(" Introduzca numero de filas de la matriz: ");
	
	SecuenciaReales una_fila; 
	TablaDentadaReales matriz;
	
	int num_filas_matriz = lector.LeeEnteroMayorOIgual(1);
	
	// rellenamos la matriz.
	cout<< "(Terminador = -1)";
	
	for(int j = 0; j < num_filas_matriz; j++){
		
		cout<<endl<<"Introduzca los reales de la fila "<< j+1 << ": ";
		while(seguir_pidiendo){
			
			cin>>num;
			
			if(num != TERMINADOR)
				una_fila.Aniade(num);
			else
				seguir_pidiendo = false;
		}
		cout<<"Fila "<< j+1 << ": " << una_fila.ToString() << endl;	
		
		matriz.Aniade(una_fila);
		una_fila.EliminaTodos();
		seguir_pidiendo = true;
	}
	
	/***********************************************************************/
	// Mostrar los datos de la matriz

	cout << endl;
	cout << matriz.ToString("Matriz original");
	cout << endl;
	
	/***********************************************************************/
	
	// Mostrar el resultado
	cout<<matriz.SumaMatrizReales().ToString("Matriz resultante");
	
	cout << endl << endl;
	
	return 0;
}
