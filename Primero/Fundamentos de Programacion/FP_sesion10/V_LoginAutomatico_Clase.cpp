/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 14: el programa lee un numero de caracteres maximo (n) y el nombre
	completo del usuario. Crea un objeto que será nombre_usuario con el que 
	calculará una recomendacion de nombre de usuario. Para ello, cogerán los
	n primeros caracteres de cada nombre del usuario. 
	
*/

#include<iostream>
#include<string>

using namespace std;

class Login{
	private: //PRE: el numero es un entero positivo
		int num_caracteres_a_coger;
	public:
		Login (int n): 
			num_caracteres_a_coger (n)
			{ }
		
		string Codifica(string nombre_completo){
    		const int NUMERO_CARACTERES= nombre_completo.length(); 
			int contador = 0;
    		string usuario = ""; //al principio el nombre de usuario no tiene 
    							 //ningun caracter, está vacío
    		
    		//un bucle que pasa por cada uno de los caracteres del nombre 
    		//completo del usurio. Si la posicion donde se encuentra el caracter
    		//está en una posicion menor a la del num_caracteres_a_coger y es
    		//distinto de un espacio, entonces ese caracter se añade al nombre
    		//de usuario. Además se suma uno a la posicion, es decir, se mira
    		//el siguiente caracter. 
    		for (int i = 0; i < NUMERO_CARACTERES ; i++){
	   			if(contador < num_caracteres_a_coger && 
				   									nombre_completo[i] != ' '){
				   	char caracter = tolower(nombre_completo[i]);
		    		usuario.push_back(caracter);
   		 			contador++;
				}else{ //si no se cumplen las condiciones, las posiciones van a 
					   //ir pasando mientras que sean espacios. Los contadores
					   //se ponen a 0 cada vez, para que cuando llegue al 
					   //siguiente nombre, perita leer sus caracter.
					if(contador > num_caracteres_a_coger || 
														nombre_completo[i]==' ')
					contador = 0;
	    		}
			}
			return usuario;
		}
};

/*****************************************************************************/
bool ComprobarQueEsPositivo (string cadena){
	
	int j = 0;
	bool es_positivo = true;
	
	if(cadena.at(0) == '+')
		j++;
	
	while(es_positivo && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_positivo = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == ' ';
		j++;
	}
		
	return es_positivo; //true si es un positivo y false si no lo es.	
}

int LeePositivo (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		cin>>respuesta;
		es_valido = ComprobarQueEsPositivo(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}

/*****************************************************************************/

int main(){
	string nombre;
	int numero;
	
	//ENTRADA DE DATOS
	
	cout<< " Introduzca su nombre completo: ";
	getline(cin, nombre); //para que lea la cadena entera y no sólo una palabra
	numero = LeePositivo(" Introduzca el maximo de caracteres: ");
	
	//CALCULOS
	
	Login nombre_usuario(numero);
	
	//SALIDAS
	
	cout<<endl;
	cout<< " Nombre de usuario recomendado: "<<nombre_usuario.Codifica(nombre);
	cout<<endl<<endl;
	
	return 0;
}
