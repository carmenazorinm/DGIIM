/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 20: este programa va leyendo los datos de cada uno de los alumnos
	hasta que se introduzca un FIN en el apellido del alumno. Una vez 
	tenemos a todos los alumnos, los metemos en un objeto de la clase 
	Grupo_AlumnosFP grupo_a. Los alumnos se ordenarán por orden 
	de notas. Para ello se utilizará el método CreaGrupoOrdenado que devuelve
	un objeto del Grupo_ALumosFP grupo_a con los alumnos ordenados de menor
	a mayor notas. 
	
*/

#include<iostream>
#include<string>
#include<iomanip>

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

/*****************************************************************************/
/*****************************************************************************/

class AlumnoFP{
private:
	string nombre;
	string apellido;
	//PRE: dni con 8 digitos numericos y una letra
	string dni;
	//PRE: todas las notas deben ser >=0 y <=10
	double nota_teoria;
	double nota_practico1;
	double nota_practico2;
	double nota_ev_cont;
	static const int PORC_TEORIA;
	static const int PORC_PRACTICO1;
	static const int PORC_PRACTICO2;
	static const int PORC_EV_CONT;
	
public:
	/**********************************************************/
	//Constructor que tiene como argumentos el nombre, apellido y dni 
	AlumnoFP (string nombre, string apellido1, string dni):
		nombre(nombre), apellido(apellido1), dni(dni), nota_teoria(0),
		nota_practico1(0), nota_practico2(0), nota_ev_cont(0)
	{}
	
	/**********************************************************/
	//constructor sin argumentos
	AlumnoFP(void){
		nombre = " ";
		apellido = " ";
		dni = " ";
		nota_teoria = 0;
		nota_practico1 = 0;
		nota_practico2 = 0;
		nota_ev_cont = 0;
	}
	
	/**********************************************************/
	//método que introduce las notas del alumno
	void SetNotas(double teoria, double practico1, double practico2, 
					double ev_cont){
		nota_teoria = teoria;
		nota_practico1=practico1;
		nota_practico2 = practico2; 
		nota_ev_cont = ev_cont;
	}
	
	/**********************************************************/
	//método que introduce la nota de teoría
	void SetTeoria(double nota){
		nota_teoria = nota;
	}
	
	/**********************************************************/
	//método que introduce la nota del practico1
	void SetPractico1(double nota){
		nota_practico1 = nota;
	}
	
	/**********************************************************/
	//método que introduce la nota del practico2
	void SetPractico2(double nota){
		nota_practico2 = nota;
	}
	
	/**********************************************************/
	//método que introduce la nota de la evalucacion continua
	void SetEvContinua(double nota){
		nota_ev_cont = nota;
	}
	
	/**********************************************************/
	double CalcularNotaFinal(void){
		double final_teoria = CalcularFinalTeoria();
		double final_practica1 = CalcularFinalPractica1();
		double final_practica2 = CalcularFinalPractica2();
		double final_ev_cont = CalcularFinalEvCont();
		double nota_final;
		
		if(nota_teoria<=4)
			nota_final = nota_teoria;
		else
			nota_final = final_teoria + final_practica1 + final_practica2 +
																final_ev_cont;
		return nota_final;
	}
	
	/**********************************************************/
	bool HayNotasSuspensas(void){
		bool hay_notas_suspensas = false;
		if(nota_teoria<5||nota_practico1<5||nota_practico2<5||nota_ev_cont<5)
			hay_notas_suspensas = true;
		
		return hay_notas_suspensas;
	}
	
	/**********************************************************/
	string GetNombre(void){
		return nombre;
	}
	
	/**********************************************************/
	string GetApellido(void){
		return apellido;
	}
	
	/**********************************************************/
	string GetDni(void){
		return dni;
	}
	
	/**********************************************************/
	double GetNotaTeorico(){
		return nota_teoria;
	}
	
	/**********************************************************/
	double GetNotaPractico1(){
		return nota_practico1;
	}
	
	/**********************************************************/
	double GetNotaPractico2(){
		return nota_practico2;
	}
	
	/**********************************************************/
	double GetEvalCont(){
		return nota_ev_cont;
	}
	
	/**********************************************************/
	string ToString(){
		string cad = apellido + ", " + nombre + " ---> T: " + 
					to_string(nota_teoria) + " P1: " + to_string(nota_practico1)
					+ " P2: " + to_string(nota_practico2) + " EC: " +
					to_string(nota_ev_cont) + " Nota final = " + 
					to_string(CalcularNotaFinal());
		return cad;
	}
	
	/***********************************************************/
	bool MayorNotaFinal(AlumnoFP alumno2){
		bool es_mayor = false;
		
		if(CalcularNotaFinal() > alumno2.CalcularNotaFinal())
			es_mayor = true;
		
		return es_mayor;
	}
	
	/***********************************************************/
	bool IgualNotaFinal(AlumnoFP alumno2){
		bool es_igual = false;
		
		if(CalcularNotaFinal() > alumno2.CalcularNotaFinal())
			es_igual = true;
		
		return es_igual;
	}
	
	/***********************************************************/
	bool MayorNotaTeoria(AlumnoFP alumno2){
		bool es_mayor = false;
		
		if(GetNotaTeorico() > alumno2.GetNotaTeorico())
			es_mayor = true;
		
		return es_mayor;
	}
	
	/**********************************************************/
	bool IgualNotaTeoria(AlumnoFP alumno2){
		bool es_igual = false;
		
		if(GetNotaTeorico() == alumno2.GetNotaTeorico())
			es_igual = true;
		
		return es_igual;
	}
	
	/**********************************************************/
	bool MayorNotaPractico1(AlumnoFP alumno2){
		bool es_mayor = false;
		
		if(GetNotaPractico1() > alumno2.GetNotaPractico1())
			es_mayor = true;
		
		return es_mayor;
	}
	
	/**********************************************************/
	bool IgualNotaPractico1(AlumnoFP alumno2){
		bool es_igual = false;
		
		if(GetNotaPractico1() == alumno2.GetNotaPractico1())
			es_igual = true;
		
		return es_igual;
	}
	
	/**********************************************************/
	bool MayorNotaPractico2(AlumnoFP alumno2){
		bool es_mayor = false;
		
		if(GetNotaPractico2() > alumno2.GetNotaPractico2())
			es_mayor = true;
		
		return es_mayor;
	}
	
	/**********************************************************/
	bool IgualNotaPractico2( AlumnoFP alumno2){
		bool es_igual = false;
		
		if(GetNotaPractico2() == alumno2.GetNotaPractico2())
			es_igual = true;
		
		return es_igual;
	}
	
	/**********************************************************/
	bool MayorEvContinua(AlumnoFP alumno2){
		bool es_mayor = false;
		
		if(GetEvalCont() > alumno2.GetEvalCont())
			es_mayor = true;
		
		return es_mayor;
	}
	
	/**********************************************************/
	bool IgualEvContinua(AlumnoFP alumno2){
		bool es_igual = false;
		
		if(GetEvalCont() == alumno2.GetEvalCont())
			es_igual = true;
		
		return es_igual;
	}

private:
	/**********************************************************/
	double CalcularFinalTeoria(void){
		double nota = PORC_TEORIA*0.01*nota_teoria;
		return nota;
	}	
	
	/**********************************************************/	
	double CalcularFinalPractica1(void){
		double nota = PORC_PRACTICO1*0.01*nota_practico1;
		return nota;
	}
		
	/**********************************************************/	
	double CalcularFinalPractica2(void){
		double nota = PORC_PRACTICO2*0.01*nota_practico2;
		return nota;
	}
	
	/**********************************************************/
	double CalcularFinalEvCont(void){
		double nota = PORC_EV_CONT*0.01*nota_ev_cont;
		return nota;
	}
	
	/**********************************************************/		
};
const int AlumnoFP::PORC_TEORIA = 60;
const int AlumnoFP::PORC_PRACTICO1 = 10;
const int AlumnoFP::PORC_PRACTICO2 = 20;
const int AlumnoFP::PORC_EV_CONT = 10;


/*****************************************************************************/
/*****************************************************************************/
class Grupo_AlumnosFp{

private:
	static const int TAMANIO = 100;
	AlumnoFP vector_alumnos[TAMANIO];
	int total_alumnos = 0;
	
public:
	public:
	/*********************************************************/
	// Constructor sin argumentos
	Grupo_AlumnosFp (void): total_alumnos(0)
		{}
		
	/*********************************************************/
	// Devuelve el número de casillas ocupadas
	int TotalAlumnos (void){
		return (total_alumnos);
	}
	
	/*********************************************************/
	// Devuelve el número de casillas disponibles
	int Capacidad (void){	
		return (TAMANIO);
	}
	
	/*********************************************************/
	// "Vacía" completamente la secuencia
	void EliminaTodos (void){
		total_alumnos = 0;
	}
	
	/*********************************************************/
	// Añade un elemento ("nuevo") al vector.
	// PRE: total_utilizados < TAMANIO
	// La adición se realiza si hay alguna casilla disponible.
	// El nuevo elemento se coloca al final del vector.
	// Si no hay espacio, no se hace nada.
	void Aniade (AlumnoFP nuevo){
		if (total_alumnos < TAMANIO){	
			vector_alumnos[total_alumnos] = nuevo;
			total_alumnos++;
		}
	}
	
	/*********************************************************/
	// Devuelve el elemento de la casilla "indice"
	// PRE: 0 <= indice < total_utilizados
	AlumnoFP Elemento (int indice){
		return (vector_alumnos[indice]);
	}
		
	/*********************************************************/
	// Cambia el contenido de la casilla "indice" por el valor
	// dado en "nuevo". El tamaño de la secuencia no cambia.
	// PRE: 0 <= indice < total_utilizados
	void Modifica (int indice, AlumnoFP nuevo){
		if ((indice >= 0) && (indice < total_alumnos))
			vector_alumnos[indice] = nuevo;
	}
	
	/*********************************************************/
	// Eliminar el carácter de la posición dada por "indice".
	// Realiza un borrado físico (desplazamiento y sustitución).
	// PRE: 0 <= indice < total_utilizados
	void Elimina (int indice){
		if ((indice >= 0) && (indice < total_alumnos)) {
			int tope = total_alumnos-1; // posic. del último
			
			for (int i = indice ; i < tope ; i++)
				vector_alumnos[i] = vector_alumnos[i+1];
			
			total_alumnos--;
		}
	}
	
	/*********************************************************/
	// Inserta el carácter "nuevo" en la posición dada por "indice".
	// Desplaza todos los caracteres una posición a la derecha
	// antes de copiar en "indice" en valor "nuevo".
	// PRE: 0 <= indice < total_utilizados
	void Inserta (int indice, AlumnoFP alumno_nuevo){
		if ((total_alumnos < TAMANIO) && (indice >= 0)
											&& (indice < total_alumnos)){

			for (int i = total_alumnos ; i > indice ; i--)
				vector_alumnos[i] = vector_alumnos[i-1];
				
			vector_alumnos[indice] = alumno_nuevo;
			total_alumnos++;
		}
	}
	
	/*********************************************************/
	// Compone un string con todos los caracteres que están
	// almacenados en la secuencia y lo devuelve.
	string ToString(){
		string cadena;
		
		for (int i=0; i<total_alumnos; i++){
			AlumnoFP alumno = vector_alumnos[i];
			string datos_alumno = alumno.ToString();
			cadena = cadena + datos_alumno + '\n';
		}
			
		return (cadena);
	}
	/************************************************************/
	//método utilizado por el método Ordena_por_Seleccion(). En este método
	//se busca la posicion en vector_alumnos del alumno con menor nota de entre
	//dos posiciones. Para ello, se va mirando alumno por alumno sus notas
	//con respecto el alumno con las notas mas bajas. Si el alumno en cuestión 
	//tiene las notas más bajas que el actual alumno con las notas más bajas.
	//entonces, se cambian el pusto. 
	//Para comparar las notas de dos alumnos, primero se mira la nota final,
	//en caso de que sean iguales, se mira la nota del teórico; en caso de que 
	//sean iguales, se mira la nota del practico2; en caso de que sean iguales,
	//se mira la nota del practico1; en caso deque sean iguales, la nota de la
	//evaluacion continua; en caso de que sean iguales, el que tenga el 
	//caracter tercero del apellido más grande.
	/*
	int PosicionMinimoEntre(int a, int b){
		int pos_minimo = a;
		a = a + 1;
		
		while(a <= b){
			
			AlumnoFP alumno_minimo = vector_alumnos[pos_minimo];
			AlumnoFP alumno_a = vector_alumnos[a];
			
		if(alumno_minimo.MayorNotaFinal(alumno_a))
			pos_minimo = a;
		else{
			if(alumno_minimo.IgualNotaFinal(alumno_a)){
				if(alumno_minimo.MayorNotaTeoria(alumno_a))
					pos_minimo =a;
				else{
					if(alumno_minimo.IgualNotaTeoria(alumno_a)){
						if(alumno_minimo.)
					}
				}
			}
		}
		
		
			a++;
		}
		
		return pos_minimo;
	}
	*/
	
	//HACER DE NUEVO LA FUNCION ANTERIORRRRRR.SUBIDA A PRADO
	
	/*********************************************************/
	//este método ordena las notas mediante seleccion. Para ello, primero 
	//busca entre todos los alumnos, el que tiene las notas más bajas. A este
	//alumno lo deja en primera posicion. De entre el resto de alumno, busca
	//al segundo con las notas más bajas y lo deja en segunda posicion. De entre
	//el resto, busca al tercero con las notas más bajas, y lo deja en tercera 
	//posicion. Así continuamente.
	void Ordena_por_Seleccion(){
		int pos_min;
		
		for (int izda = 0 ; izda < total_alumnos ; izda++){
			pos_min = PosicionMinimoEntre (izda, total_alumnos-1);
			IntercambiaComponentes_en_Posiciones (izda, pos_min);
		}
	}
	
	/*********************************************************/
	//este método cambia a dos alumnos de posiciones. Es decir, si se quiere
	//cambiar, por ejemplo, al alumno en la posicion3 y ponerlo en la posicion5.
	//Para ello, crea un AlumnoFP intercambia que guarde los datos del alumno
	//del que se quiere cambiar la posicion. Entonces se posiciona al otro 
	//alumno a la posicion de éste. Y en la posicion donde se encontraba el 
	//otro, se pegan los datos del alumno intercambia.
	void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
		AlumnoFP intercambia;
		
		intercambia = vector_alumnos[pos_izda];
		vector_alumnos[pos_izda] = vector_alumnos[pos_dcha];
		vector_alumnos[pos_dcha] = intercambia;
	}
	
	/********************************************************/
	//este método devuelve un Grupo_AlumnosFP en el que los alumnos del grupo
	//implícito se encuentran ordenados por sus notas. Para ello, primero copia
	//todos los alumnos del grupo implícito a un nuevo Grupo_AlumnosFP que se 
	//llamará grupo_ordenado. grupo_ordenado será ordenado mediante el método
	//de Ordena_por_Seleccion. Se devuleve grupo_ordenado ordenado.
	Grupo_AlumnosFp CreaGrupoOrdenado(void){
		Grupo_AlumnosFp grupo_ordenado;
		for(int i = 0; i < total_alumnos; i++){
			grupo_ordenado.Aniade(vector_alumnos[i]);
		}
		
		grupo_ordenado.Ordena_por_Seleccion();
		
		return grupo_ordenado;
	}
	
};
/*****************************************************************************/
/*****************************************************************************/
//esta función verifica que el numero del dni sea válido. Para que un dni sea
//valido debe tener 9 caracteres. Los ocho primeros deben ser dígitos numéricos
//y el último debe ser una letra.
bool EsCorrecto(string dni){
	bool es_correcto = true;
	if(dni.length() != 9)
		es_correcto = false;
	else{
		for(int i = 0; i < dni.length(); i++){
			if(i <= 7){
				if(dni.at(i)<'0' || dni.at(i)>'9')
					es_correcto = false;
			}
			else{
				dni.at(i) = toupper(dni.at(i));
				if(dni.at(i)<'A' || dni.at(i)>'Z')
					es_correcto = false;
			}
		}
	}
	return es_correcto;
}

/*****************************************************************************/
/*****************************************************************************/

int main(){
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 
	
	//DECLARACION DE VARIABLES
	
	string nombre_alumno, dni, apellido_alumno;
	Grupo_AlumnosFp grupo_a;
	Lector lector_notas;
	double teoria, pract1, pract2, ev_continua;
	
	//ENTRADA DE DATOS
	
	bool seguir_pidiendo = true;
	
	do{
		cout<<endl;
		cout<<" Introduzca los datos del alumno: "<<endl;
		
		//nombre y apellidos
		cout<<" Nombre: ";
		cin.ignore();
		getline(cin, nombre_alumno);
		do{
			cout<<" Apellido: ";
			getline(cin, apellido_alumno);	
		}while(apellido_alumno.length() < 3);//debe tener una longitud mayor de 
											//tres caracteres para poder 
											//ordenar a los alumnos.
		
		//si el apellido es "FIN" significa que nose quieren leer los datos de 
		//más alumnos.
		if(apellido_alumno == "FIN"){
			seguir_pidiendo = false;
			
		}else{
			
			//dni completo. Se ha creado la funcion EsCorrecto() como filtro
			do{
				cout<< " DNI con letra incluida: ";
				cin>>dni;
			}while(!EsCorrecto(dni));
			
			//al lector notas le incluimos el titulo para el examen teorico y 
			//leemos la nota. Pero, una vez que se haya incluido
			//esa nota correctamente, se introduciráotro titulo 
			//para el lector y se leerá otra nota...
			lector_notas.SetTitulo(" Nota examen teorico: ");
			do{
				teoria = lector_notas.LeeReal();
			}while(teoria<0 || teoria>10);
			
			//nota examen practico 1
			lector_notas.SetTitulo(" Nota examen practico 1: ");
			do{
				pract1 = lector_notas.LeeReal();
			}while(pract1<0 || pract1>10);
			
			//nota examen practico 2
			lector_notas.SetTitulo(" Nota examen practico 2: ");
			do{
				pract2 = lector_notas.LeeReal();
			}while(pract2<0 || pract2>10);
			
			//nota evaluacion continua
			lector_notas.SetTitulo(" Nota evaluacion continua: ");
			do{
				ev_continua = lector_notas.LeeReal();
			}while(ev_continua<0 || ev_continua>10);
			
			//CALCULOS
			
			AlumnoFP alumno(nombre_alumno, apellido_alumno, dni);
			alumno.SetNotas(teoria, pract1, pract2, ev_continua);
			grupo_a.Aniade(alumno);
				
		}//se cierra el else	
	}while(seguir_pidiendo);
	
	cout<<endl;
	cout<<" Resumen de los alumnos: "<<endl;
	cout<< grupo_a.ToString();
	
	//CALCULOS
	
	Grupo_AlumnosFp grupo_a_ordenado = grupo_a.CreaGrupoOrdenado();
	
	//SALIDA
	
	cout<<endl;
	cout<<" Resumen alumnos ordenados por nota de menor a mayor: "<<endl;
	cout<<grupo_a_ordenado.ToString();	

	cout<<endl<<endl;
	
	return 0;
}
