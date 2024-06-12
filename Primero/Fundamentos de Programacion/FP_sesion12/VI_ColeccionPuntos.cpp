/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 25: el programa leerá puntos hasta que se introduzca "FIN" en 
	la coordenada x. Cada vez que lee un punto lo mete en un objeto de la 
	clase ColeccionPuntos2D. Posteriormente, se preguntará por el radio y el
	centro de una circunferencia. Finalmente, se creará un nuevo objeto de la
	clase ColeccionPuntos2D que guardará los puntos que se han introducido
	anteriormente y que pertenecen a la circunferencia. Para ello, se ha creado
	un método en ColeccionPuntos2D que crea un objeto de esta clase con los
	puntos suyos que pertenecen a la circunferencia introducida. 
	
*/

#include <iostream>
#include <cctype>
#include <cmath>
#include <iomanip>
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
		
		//Lee entero mayor o igual. Sólo hace falta llamar al método con el 
		//valor de la referencia.
		int LeeEnteroMayorOIgual (int referencia){
			string respuesta;
			bool es_valido;
			int entero;
			
			do{
				cout<<titulo;
				getline( cin, respuesta);
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
		
		double LeeRealMayorOIgual (int referencia){
			string respuesta;
			bool es_valido;
			double real;
			
			do{
				cout<<titulo;
				cin>>respuesta;
				es_valido = ComprobarQueEsReal(respuesta);
		
				if(es_valido){ 
					real = stod(respuesta);
					es_valido = real>=referencia;
				}
			}while(!es_valido);
	
			return real;
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
};

///////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
// Función global (asociada a la constante PRECISION_SON_IGUALES) que
// permite que dos números reales muy próximos sean considerados iguales.

const double PRECISION_SON_IGUALES = 1e-6; // 0.000001

bool SonIguales(double uno, double otro) 
{
	return (fabs(uno-otro) <= PRECISION_SON_IGUALES);
}

/////////////////////////////////////////////////////////////////////////////

class Punto2D
{
private:
	
	// La pareja (x,y) son las coordenadas de un punto en un espacio 2D
	double x;
	double y;

public:
	
	/***********************************************************************/
	// Constructor con argumentos.
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está creando.
	
	Punto2D (double abscisaPunto, double ordenadaPunto)
	{
		SetCoordenadas (abscisaPunto, ordenadaPunto);
	}
	
	/***********************************************************************/
	// Constructor sin argumentos.
	//
	// No recibe nada y inicializa el punto en la coordenada (0,0)
	
	Punto2D (void)
	{
		SetCoordenadas (0, 0);
	}

	/***********************************************************************/
	// Método Set para fijar simultaneamente las coordenadas. 
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está modificando.
	
	void SetCoordenadas (double abscisaPunto, double ordenadaPunto)
	{
		x = abscisaPunto;
		y = ordenadaPunto;
	}

	/***********************************************************************/
	// Métodos Get para leer las coordenadas

	double GetX (void)
	{
		return (x);
	}
	double GetY (void)
	{
		return (y);
	}

	/***********************************************************************/
	// Calcula si dos puntos son iguales 
	//
	// Recibe: otro, el punto que se quiere comparar con el objeto implícito. 
	// Devuelve: true, si se consideran iguales los dos objetos. 

	bool EsIgual (Punto2D otro)
	{
		return (SonIguales(x,otro.x) && SonIguales(y,otro.y));
	}

	/***********************************************************************/
	// Calcula la distancia Euclídea del punto (objeto implícito) a otro que 
	// se recibe como argumento. 
	//
	// Recibe: otro, el punto respecto al cual que se quiere calcular la 
	// distancia euclídea.
	// Devuelve: la distancia entre los dos puntos. 

	double DistanciaEuclidea (Punto2D otro)
	{
		double dif_x = pow (x - otro.x, 2);
		double dif_y = pow (y - otro.y, 2);

		return (sqrt(dif_x + dif_y));
	}

	/***********************************************************************/

	string ToString ()
	{
		return ("["+to_string(x)+", "+to_string(y)+"]");
	}
	
	/***********************************************************************/

};

/////////////////////////////////////////////////////////////////////////////
// La clase "Circunferencia" representa circunferencias, objetos geométricos 
// que verifican la propiedad de que los puntos (x,y) que la forman están a 
// la misma distancia de otro punto (el centro).

class Circunferencia
{
private:

	// La constante "PI" es común a todos los objetos de la clase.
	static const double PI;		
	
	// Centro de la circunferencia
	Punto2D centro;	
	
	// Longitud del radio
	// PRE: radio >= 0
	double  radio;	

public:

	/***********************************************************************/
	// Constructor con argumentos
	// Recibe:
	//		el_centro, el punto central de la circunferencia. 
	//		radio, el valor del radio.
	// PRE: radio >= 0

	Circunferencia (Punto2D el_centro, double el_radio) : centro (el_centro)
	{
		// Observad cómo se ha iniciado "centro": como es de clase "Punto2D"
		// se ha empleado la lista de iniciación para que actúe el constructor
		// de la clase "Punto2D" 
		 
		radio  = el_radio; 
	}

	/***********************************************************************/
	// Métodos Get
	
	// Devuelve el punto central de la circunferencia
	Punto2D GetCentro (void)
	{
		return (centro);
	}

	// Devuelve el radio de la circunferencia
	double GetRadio (void)
	{
		return (radio);
	}

	// Devuelve el diámetro de la circunferencia
	double GetDiametro (void)
	{
		return (radio*2);
	}
	
	// Método SetRadio para cambiar el valor del radio
	//PRE: rad > 0
	void SetRadio(double rad){ radio = rad; }
	
	// Método SetCentro para cambiar las coordenadas del punto del centro
	void SetCentro(Punto2D punto){ centro = punto; }

	/***********************************************************************/
	// Calcula la longitud de la circunferencia

	double Longitud (void)
	{
		return (2.0 * PI * radio);
	}

	/***********************************************************************/
	// Calcula el área del círculo
	
	double Area (void)
	{
		return (PI * radio * radio);
	}

	/***********************************************************************/
	// Calcular si la circunferencia contiene a un punto dado.
	//
	// Recibe: un_punto, el punto del que se quiere evaluar su pertenencia. 
	/*
		Un punto (x, y) está dentro de una circunferencia con 
		centro (x_0, y_0) y radio r si se verifica que:
			(x-0 - x)^2 + (y_0 - y)^2 <= r^2
	*/
	/*
	bool Contiene (Punto2D un_punto)
	{
		double dif_x = pow (centro.GetX() - un_punto.GetX(), 2);
		double dif_y = pow (centro.GetY() - un_punto.GetY(), 2);
		return (dif_x + dif_y <= radio*radio);
	}
	*/
	/***********************************************************************/
	// Calcular si la circunferencia contiene a un punto dado usando un 
	// test explícito sobre la distancia Euclídea del centro de la 
	// circunferencia al punto.
	//
	// Recibe: un_punto, el punto del que se quiere evaluar su pertenencia. 
	/*
		Un punto P(x, y) está dentro de una circunferencia con centro 
		C(x_0, y_0) y radio r si DistaciaEuclidea (P, C) <= r
	*/
	// Esta implementación es preferible a la anterior ya que no requiere 
	// duplicar (aunque sea de manera indiirecta) el código referido al 
	// cálculo de la distancia entre dos puntos. 
	
	bool Contiene (Punto2D un_punto)
	{
		Punto2D el_centro = GetCentro();
		double distancia = el_centro.DistanciaEuclidea (un_punto);
		return (distancia <= radio);
		
		//return(GetCentro().DistanciaEuclidea(un_punto) <= radio);
	}

	/***********************************************************************/
};

const double Circunferencia :: PI = 3.1415926;

/////////////////////////////////////////////////////////////////////////////

class ColeccionPuntos2D{

private:
	static const int TAMANIO = 100;
	Punto2D vector_privado[TAMANIO];
	
	//PRE: O<= totsl_utilizados <= TAMANIO
	int total_utilizados;

public:
	/*********************************************************************/
	//constructor sin argumentos
	ColeccionPuntos2D(void){ total_utilizados = 0; }
	
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
		total_utilizados  = 0;
	}
	
	/*********************************************************/
	// Añade un elemento ("nuevo") al vector.
	// PRE: total_utilizados < TAMANIO
	// La adición se realiza si hay alguna casilla disponible.
	// El nuevo elemento se coloca al final del vector.
	// Si no hay espacio, no se hace nada.
	void Aniade (Punto2D nuevo){
		if (total_utilizados < TAMANIO){	
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}
	
	/*********************************************************/
	// Devuelve el elemento de la casilla "indice"
	// PRE: 0 <= indice < total_utilizados
	Punto2D Elemento (int indice){
		return (vector_privado[indice]);
	}
		
	/*********************************************************/
	// Cambia el contenido de la casilla "indice" por el valor
	// dado en "nuevo". El tamaño de la secuencia no cambia.
	// PRE: 0 <= indice < total_utilizados
	void Modifica (int indice, Punto2D nuevo){
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
	void Inserta (int indice, Punto2D nuevo){
		if ((total_utilizados < TAMANIO) && (indice >= 0)
											&& (indice < total_utilizados)){

			for (int i = total_utilizados ; i > indice ; i--)
				vector_privado[i] = vector_privado[i-1];
				
			vector_privado[indice] = nuevo;
			total_utilizados++;
		}
	}
	
	/*********************************************************/
	// Compone un string con todos los caracteres que están
	// almacenados en la secuencia y lo devuelve.
	string ToString(){
		string cadena;
		
		for (int i=0; i<total_utilizados; i++){
			Punto2D punto = vector_privado[i];
			string datos_punto = punto.ToString();
			cadena = cadena + datos_punto + '\n';
		}
		return (cadena);
	}
	
	/********************************************************/
	// Este método crea un objeto de la clase ColeccionPuntos2D 
	//en_circunferencia. Va pasando por todos los puntos que contiene
	//la coleccion implícita. Si el punto que se está estudiando pertenece
	//a la circunferencia, entonces se añade a en_circunferencia. Si no está
	//dentro de la circunferencia, se pasa a mirar el siguiente punto.
	
	ColeccionPuntos2D PuntosEnCircunferencia(Circunferencia circunf){
		ColeccionPuntos2D en_circunferencia;
		
		for(int i = 0; i < total_utilizados; i++){
			
			if(circunf.Contiene(vector_privado[i]))
				en_circunferencia.Aniade(vector_privado[i]);
		}
		return en_circunferencia;
	}
	/*********************************************************/
	
}; 

/////////////////////////////////////////////////////////////////////////////

int main(){
	ColeccionPuntos2D coleccion_general;
	string x;
	double y;
	bool seguir_pidiendo = true;
	Lector lector;
	
	//ENTRADA DE DATOS
	
	do{
		cout<<" Introduzca un punto: "<<endl;
		cout<<" Abscisa: ";
		//lee un string
		cin>>x;
		//si se entroduce "FIN", entonces dejar de leer más puntos
		if(x == "FIN")
			seguir_pidiendo = false;
		
		//si no se introduce "FIN", entonces hay que comprobar que la x 
		//introducida es un double. Para ello, utilizamos un lector. Como hemos
		//hecho el método ComprobarQueEsReal() público, podemos saber si el 
		//string x es un numero real. Si es un numero real, seguimos pidiendo el 
		//resto de datos. Si no es un numero real, queremos que vuelva a pedir 
		//la x hasta que lo sea.
		else{
			double real_x;
			Lector lector;
			
			if(!lector.ComprobarQueEsReal(x)){//comprobamos que x es real.
				lector.SetTitulo(" Abscisa: ");
				real_x = lector.LeeReal();	
			}else
				real_x = stod(x);
				
			lector.SetTitulo(" Ordenada: ");
			y = lector.LeeReal();
			
			//se crea un punto con las coordenadas leidas y se mete en la
			//coleccion_general.
			Punto2D punto(real_x, y);
			coleccion_general.Aniade(punto);	
		}
		cout<<endl;
		
	}while(seguir_pidiendo);	
	cout<<endl;
	cout<<" Los puntos introducidos son: "<<endl;
	cout<<coleccion_general.ToString()<<endl;
	
	//ahora leemos los datos de la circunferencia
	Lector lector_circunf(" Introduzca el radio de la circunferencia: ");
	double radio = lector_circunf.LeeRealMayorOIgual(0);
	
	cout<<" Introduzca las coordenadas del centro: "<<endl;
	lector.SetTitulo(" Abscisa: ");
	double x_circunf = lector.LeeReal();
	lector.SetTitulo(" Ordenada: ");
	double y_circunf = lector.LeeReal();
	
	Punto2D centro(x_circunf, y_circunf);
	cout<<" El centro es: " << centro.ToString()<<endl;
	Circunferencia circunf(centro, radio);
	
	//CALCULOS
	
	ColeccionPuntos2D puntos_dentro; //creamos la coleccion que contiene a los
									 //puntos que estan dentro de la circunf
	puntos_dentro = coleccion_general.PuntosEnCircunferencia(circunf);
	
	//SALIDA
	
	cout<<endl;
	cout<<" Los puntos dentro de la circunferencia son: "<<endl;
	cout<<puntos_dentro.ToString();
	
	cout<<endl<<endl;
	
	return 0;
}
