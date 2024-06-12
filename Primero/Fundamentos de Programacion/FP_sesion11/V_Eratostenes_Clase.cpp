/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 22: el programa lee un numero n y calcula todos los primos menores
	que n con la clase Eratostenes. Posteriormente, muestra todos los primos.
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

/******************************************************************************/
/******************************************************************************/

class Eratostenes{
	
private:
	static const int TAMANIO = 500;
	int vector_privado[TAMANIO];
	//PRE: 0<=total_utilizados<=TAMANIO
	int total_utilizados;

public:
	//Constructor. Se inicializa la variable total_utilizados con 0 y, 
	//posteriormente, se introduce en la posicion 0 el primo 1.
	Eratostenes(void):
		total_utilizados(0)
	{
	    vector_privado[total_utilizados] = 1;
	    total_utilizados++;
	}	
	
	void CalculaHasta(int n){
		
		//si ya están calculados todos los primos menores que n, no hace falta 
		//volver a rellenar todo el vector. Y si no están calculados todos los
		//primos menores que n, empezaremos a rellenar el vector desde el 
		//ultimo primo calculado, no hace falta empezar desde el principio.
		if(GetMaximo() <= n){
			
			//empezamos desde el numero 2, porque el 1 ya lo hemos añadido al 
			//vector en la posicion 0 con el constructor.
			for(int i = 2; i<=n; i++){
				bool es_primo = true;
				
				//vamos desde un numero más que el 1 y hasta un numero menos 
				//que el i. Si hay algun divisor entre ese rango de numeros, 
				//entonces i no es primo
				for(int j = 2; j < i; j++){
					if(i%j ==0)
						es_primo = false;
				}
				
				//si es primo, lo añadimos al vector
				if(es_primo){
					vector_privado[total_utilizados] = i;
				}
			}
		}
	}
	
	int TotalCalculados(void){
		return total_utilizados;
	}
	
	int Elemento(int k){
		
		//si la posicion k no está rellenada en el vector, hay que rellenarla.
		if(k > total_utilizados && k < TAMANIO)
			CalculaHasta(k);
		
		return vector_privado[k];
	}

private:	
	
	//el primo más alto calculado será el último del vector.
	int GetMaximo(void){
	    int posicion = total_utilizados - 1;
	        
		return vector_privado[posicion];
	}
		
};

/******************************************************************************/
/******************************************************************************/

int main(){
    /* EJEMPLO DADO
    
	Eratostenes primos;
	int n = 100;
	primos.CalculaHasta(n);
	int tope = primos.TotalCalculados();
	for (int i=0; i<tope; i++)
	    cout << primos.Elemento(i) << " ";
	*/
	
	int n;
	Lector lector_n(" Introduzca un numero para saber los primos menores: ");
	
	//ENTRADA
	
	cout<<endl;
	n = lector_n.LeeEnteroEnRango(0, 500);
	
	//CALCULOS
	
	Eratostenes primos;
	primos.CalculaHasta(n);
	int tope = primos.TotalCalculados();
	
	//SALIDA
	
	for(int i = 0; i < tope; i++)
		cout << primos.Elemento(i) << " ";
	
	cout<<endl<<endl;

	return 0;
}
