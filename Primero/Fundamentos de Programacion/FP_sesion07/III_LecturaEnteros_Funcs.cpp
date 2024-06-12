/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 18: el programa consta de tres partes:
	a) La primera lee una cadena de caracteres y comprueba que la cadena está 
	formada por dígitos numéricos. Si no es así, vuelve a pedir otra cadena.
	b) La segunda parte lee una cadena de carcateres y, si todos sus caracteres
	no son digitos o el numero que forman no está dentro del rango, vuelve a 
	pedir otra cadena.
	c) La tercera parte lee una cadena de caracteres y, si todos sus caracteres
	no son digitos o el numero que forman es menor que LIMITE, se vuelve a 
	pedir otra cadena.
*/

#include<iostream> //inclusion de recursos de E/S
#include<string>

using namespace std;

bool ComprobarQueEsEntero (string cadena){
	
	int j = 0;
	bool es_entero = true;
	
	//pasa caracter por caracter de la cadena comprobando que cada uno de ellos 
	//es un digito numerico.
	
	if(cadena.at(0) == '-' || cadena.at(0) == '+')
		j++;
	
	while(es_entero && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_entero = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == ' ';
		j++;
	}
	
	return es_entero; //true si es un entero y false si no lo es.	
}

int LeeEntero (string titulo){
	
	string respuesta;
	bool es_valido;
	
	//vuelve a escribir "titulo" hasta que la respuesta sea un número entero
	
	do{
		cout<< titulo;
		getline( cin, respuesta);
		es_valido = ComprobarQueEsEntero(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}

bool EstaDentroDelRango(int numero, int minimo, int maximo){
	
	bool correcto = false;
	
	if(numero>=minimo && numero<=maximo) //si esta dentro del rango, entonces 
										//el bool es true, si no, es false
		correcto = true;
		
	return correcto;
}


int LeeEnteroEnRango (string titulo, int menor, int mayor){
	
	string respuesta;
	bool es_valido;
	int entero;
	
	//pide una cadena de caracteres una y otra vez hasta que la respuesta sea 
	//un numero entero y esté dentro del rango
	
	do{
		cout<< titulo<< menor << " y "<<mayor<<":";
		getline( cin, respuesta);
		es_valido = ComprobarQueEsEntero(respuesta); //comprobamos que es entero
		
		if(es_valido){ //será valido si también está dentro del rango
			entero = stoi(respuesta);
			es_valido = EstaDentroDelRango(entero, menor, mayor);
		}
			
	}while(!es_valido);
	
	return entero; 
}

int LeeEnteroMayorOIgual (string titulo, int referencia){
	
	string respuesta;
	bool es_valido;
	int entero;
	
	//pide una cadena de caracteres hasta que la respuesta sea un numero entero
	//y éste sea mayor que "referencia"
	
	do{
		cout<<titulo<< referencia<< ": ";
		getline( cin, respuesta);
		es_valido = ComprobarQueEsEntero(respuesta);//comprobamos que es entero
		
		if(es_valido){ //será válido si también es mayor que referencia
			entero = stoi(respuesta);
			es_valido = entero>=referencia;
		}
	}while(!es_valido);
	
	return entero;
}

int main(){
	
	const int MAX = 10;
	const int MIN = -10;
	const int LIMITE = 10;
	
	int x;
	int y;
	int z;
	
	cout<<endl;
	x = LeeEntero(" Introduzca la coordenada x: ");
	cout<< " La coordenada x es: " << x;
	
	cout<<endl<< endl;
	y = LeeEnteroEnRango(" Introduzca un valor entre ", MIN, MAX);
	cout<< " El valor entre el rango es: "<<y;
	
	cout<< endl<< endl;
	z = LeeEnteroMayorOIgual(" Introduzca un entero mayor o igual que ",LIMITE);
	cout<< " El entero es: " << z;
	
	cout<<endl<<endl;
	
	return 0;
}
