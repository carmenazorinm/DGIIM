/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 17: el programa lee los datos de un alumno (nombre, apellido, 
	dni y las notas de cada uno de los examenes). A partir de ahí, calculará 
	la nota final con los porcentajes dados en el enunciado. Si hay algun
	examen suspendido, se mostrará en pantalla la nota de ese examen.
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
	//PRE: dni con 8 digitos numericos y una letra mayucula
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
	AlumnoFP (string nombre, string apellido1, string dni):
		nombre(nombre), apellido(apellido1), dni(dni), nota_teoria(0),
		nota_practico1(0), nota_practico2(0), nota_ev_cont(0)
	{}
	
	void SetNotas(double teoria, double practico1, double practico2, 
					double ev_cont){
		nota_teoria = teoria;
		nota_practico1=practico1;
		nota_practico2 = practico2; 
		nota_ev_cont = ev_cont;
	}
	
	void SetTeoria(double nota){
		nota_teoria = nota;
	}
	void SetPractico1(double nota){
		nota_practico1 = nota;
	}
	void SetPractico2(double nota){
		nota_practico2 = nota;
	}
	void SetEvContinua(double nota){
		nota_ev_cont = nota;
	}
	
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
	
	bool HayNotasSuspensas(void){
		bool hay_notas_suspensas = false;
		if(nota_teoria<5||nota_practico1<5||nota_practico2<5||nota_ev_cont<5)
			hay_notas_suspensas = true;
		
		return hay_notas_suspensas;
	}
	
	string GetNombre(void){
		return nombre;
	}
	
	string GetApellido(void){
		return apellido;
	}
	
	string GetDni(void){
		return dni;
	}
	
	double GetNotaTeorico(){
		return nota_teoria;
	}
	
	double GetNotaPractico1(){
		return nota_practico1;
	}
	
	double GetNotaPractico2(){
		return nota_practico2;
	}
	
	double GetEvalCont(){
		return nota_ev_cont;
	}
	
	string ToString(){
		string cad = " El alumno "+ nombre + " "+ apellido +" con DNI "+dni
					+ " tiene de nota final: " + to_string(CalcularNotaFinal());
		return cad;
	}

private:
	double CalcularFinalTeoria(void){
		double nota = PORC_TEORIA*0.01*nota_teoria;
		return nota;
	}		
	double CalcularFinalPractica1(void){
		double nota = PORC_PRACTICO1*0.01*nota_practico1;
		return nota;
	}		
	double CalcularFinalPractica2(void){
		double nota = PORC_PRACTICO2*0.01*nota_practico2;
		return nota;
	}
	double CalcularFinalEvCont(void){
		double nota = PORC_EV_CONT*0.01*nota_ev_cont;
		return nota;
	}		
};
const int AlumnoFP::PORC_TEORIA = 60;
const int AlumnoFP::PORC_PRACTICO1 = 10;
const int AlumnoFP::PORC_PRACTICO2 = 20;
const int AlumnoFP::PORC_EV_CONT = 10;

/*****************************************************************************/
/*****************************************************************************/

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
	string nombre_alumno, dni, apellido_alumno;
	Lector lector_notas;
	double teoria, pract1, pract2, ev_continua;
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	cout<<" Introduzca los datos del alumno: "<<endl;
	
	//nombre y apellidos
	cout<<" Nombre: ";
	cin>>nombre_alumno;
	cout<<" Apellido: ";
	cin>>apellido_alumno;
	
	//dni completo. Se ha creado la funcion EsCorrecto() como filtro
	do{
		cout<< " DNI con letra incluida: ";
		cin>>dni;
	}while(!EsCorrecto(dni));
	
	//al lector notas le incluimos el titulo para el examen teorico y leemos la
	//nota. Pero, una vez que se haya incluido esa nota correctamente, se 
	//introduciráotro titulo para el lector y se leerá otra nota...
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
	double nota_final = alumno.CalcularNotaFinal();
	
	//SALIDA
	
	cout<<endl;
	cout<<alumno.ToString();
	
	cout<<endl;
	if(alumno.HayNotasSuspensas()){
		if(alumno.GetNotaTeorico()<5)
			cout<<" En el examen teorico se ha obtenido un "
				<<alumno.GetNotaTeorico()<<endl;
		if(alumno.GetNotaPractico1()<5)
			cout<<" En el examen practico 1 se ha obtenido un "
				<<alumno.GetNotaPractico1()<<endl;
		if(alumno.GetNotaPractico2()<5)
			cout<<" En el examen practico 2 se ha obtenido un "
				<<alumno.GetNotaPractico2()<<endl;
		if(alumno.GetEvalCont()<5)
			cout<<" En la evaluacion continua se ha obtenido un "
				<<alumno.GetEvalCont()<<endl;
	}else
		cout<<" No hay examenes suspensos. ";
	
	cout<<endl<<endl;
	
	return 0;
}
