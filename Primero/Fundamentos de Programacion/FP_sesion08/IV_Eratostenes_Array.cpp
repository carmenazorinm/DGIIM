/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 14: el programa lee un numero y muestra todos los numeros primos
	menores o iguales que éste. Para ello crea un vector primos[50001] en el 
	que se guardaran datos de tipo bool. Al principio, todos van a ser true, 
	pero se irán modificando para que solo quede true en las posiciones primas.
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
	Eratostenes(void):
		total_utilizados(0)
	{
	    vector_privado[total_utilizados] = 1;
	    total_utilizados++;
	}	
	
	void CalculaHasta(int n){
		if(GetMaximo() <= n){
			int pos = total_utilizados;
			
			for(int i = 2; i<=n; i++){
				bool es_primo = true;
				
				for(int j = 2; j < i; j++){
					if(i%j ==0)
						es_primo = false;
				}
				if(es_primo){
					vector_privado[pos] = i;
					total_utilizados++;
					pos++;
				}
			}
		}
	}
	
	int TotalCalculados(void){
		return total_utilizados;
	}
	
	int Elemento(int k){
		if(k > total_utilizados && k < TAMANIO)
			CalculaHasta(k);
		
		return vector_privado[k];
	}

private:	
	int GetMaximo(void){
	    int posicion;
	    if(total_utilizados == 0)
	        posicion = 0;
        else 
            posicion = total_utilizados - 1;
	        
		return vector_privado[posicion];
	}
		
};

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
