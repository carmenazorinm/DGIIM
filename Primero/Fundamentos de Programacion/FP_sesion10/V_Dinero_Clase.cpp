/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 4: el programa leerá una cantidad de dinero en euros y centimos. 
	Después leerá el incremento mensual y el numero de meses que se tiene que 
	hacer el incremento. Calculará el dinero final y lo mostrará en pantalla.
*/

#include<iostream> //inclusion de recursos de E/S
#include<string> 
#include<cmath>
using namespace std;

class Dinero{ //se crea la clase dinero
	
	private:
		//PRE: los euros y los centimos deben ser positivos o cero.
		int euros;
		int centimos;
		double incremento;
		
	public:
		//constructor
		Dinero (int cant_eu, int cant_cents, double incremento):
			euros(cant_eu), centimos(cant_cents), incremento(incremento)
			{
				Simplifica();
			}
			
		string ToString(void){
			string cad;
			cad = " " + to_string(euros) + " euros y " + to_string(centimos) +
				" centimos. ";
			return(cad);
		}
		
		//PRE: el num_meses debe ser un entero positivo.
		void IncrementarXMeses(int num_meses){
			int mes = 1;
			bool seguir_calculando = true;
			//se va a hacer el incremento mientras que se pueda. Si no se puede
			//hacer el incremento, porque el incremento es negativo, entonces 
			//el dinero se pone a 0.
			while(mes <= num_meses && seguir_calculando){
				if(euros >= abs(incremento)){
					IncrementarUnMes();
					cout<< " Mes " <<mes<<" : "<< ToString() << endl;
				}else{
					euros = 0;
					centimos = 0;
					cout<< "--->Ya no se puede hacer mas incremento negativo. ";
					seguir_calculando = false;
				}
				mes++;			
			}
		}
	
	private: 
		void Simplifica(){
			while(centimos >= 100){
				centimos = centimos-100;
				euros++;
			}
		}
		
		//se aplica el incremento un mes y se vuelve a simplificar el dinero.
		void IncrementarUnMes(){
			centimos = centimos + euros*100;
			euros = 0;
			double incremento_en_cent = incremento*100;
			
			centimos = centimos + incremento_en_cent;
			Simplifica();
		}
			
};

/****************************************************************************/

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
bool ComprobarQueEsReal (string cadena){
	
	int j = 0;
	bool es_real = true;
	
	if(cadena.at(0) == '+' || cadena.at(0) == '-')
		j++;
	
	while(es_real && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_real = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == '.';
					
		j++;
	}
		
	return es_real; //true si es un positivo y false si no lo es.	
}

double LeeReal (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		cin>>respuesta;
		es_valido = ComprobarQueEsReal(respuesta);
	}while(!es_valido);
	
	double real = stod(respuesta); //convierte el string respuesta en un int
	return real;
}

/*****************************************************************************/
double GetParteDecimal (double num_double){
	num_double = num_double - int(num_double);
	return num_double;
}
/*****************************************************************************/

int main(){
	
	double lector_euros;
	double incremento_fijo;
	int meses;
	int euros;
	int centimos;
	
	//ENTRADA DE DATOS
	
	//los euros pueden ser un numero real, pero para meter los euros en la clase
	//pasaremos los decimales de los auros a centimos.
	cout<<endl;
	do{
		lector_euros = LeeReal(" Introduzca los euros iniciales: ");
	}while(lector_euros<0);
	centimos = LeePositivo(" Introduzca los centimos iniciales: ");
	incremento_fijo = LeeReal(" Introduzca un incremento fijo: ");
	meses = LeePositivo( " Introduzca el numero de meses: ");
	
	//CALCULOS
	
	//simplificamos la cantidad de dinero para que se pueda meter en la clase 
	//Dinero
	centimos = GetParteDecimal(lector_euros)*100 + centimos;
	euros = int(lector_euros);
	
	Dinero cantidad_inicial(euros, centimos, incremento_fijo);
	cout<<endl <<" Cantidad inicial: "<< cantidad_inicial.ToString()<<endl;
	
	cantidad_inicial.IncrementarXMeses(meses);
	cout<<endl <<" Cantidad final: "<< cantidad_inicial.ToString()<<endl;
	
	return 0;
}
