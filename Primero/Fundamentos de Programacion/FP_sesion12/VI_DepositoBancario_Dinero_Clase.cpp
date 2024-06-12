/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 19: el programalee una cantidad de dinero, un numero de años y 
	el interes a aplicar. Posteriormente, se calcula cuánto dinero se 
	tendría al cabo de esos años reinvirtiendo cada año todo el capital nuevo 
	al interes introducido. Para ello, se utiliza una clase DepositoBancario
	que tiene como datos miembro el interes y el capital. Esta clase tiene dos
	métodos, uno que calcula el capital final al cabo de los años introducidos;
	y otro que devuelve cuántos años se debe invertir para doblar el capital 
	del deposito.
	
*/

#include<iostream> //inclusion de recursos de E/S
#include<string> 
#include<cmath>
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

/****************************************************************************/
/****************************************************************************/

class Dinero{ //se crea la clase dinero
	
	private:
		//PRE: los euros y los centimos deben ser positivos o cero.
		int euros;
		int centimos;
		static const int EQUIVALENTE = 100;
		
	public:
		/************************************************************/
		//constructor con argumentos(euros y centimos)
		Dinero (int cant_eu, int cant_cents):
			euros(cant_eu), centimos(cant_cents)
			{
				Simplifica();
			}
		
		/************************************************************/
		//constructor con cantidad
		//PRE: cantidad > 0
		Dinero(double cantidad):
			euros(int(cantidad)), centimos((cantidad-int(cantidad))*EQUIVALENTE)
			{
			    string cant = to_string((cantidad-int(cantidad))*EQUIVALENTE);
			    centimos = stod(cant);
			}
		
		/************************************************************/
		//constructor sin argumentos
		Dinero():
			euros(0), centimos(0)
			{}
		
		/************************************************************/
		//funciones get	y set
		int GetEuros(void){ return euros; }
		int GetCentimos(void){ return centimos; }
		
		/************************************************************/
		//PRE: nuevos_euros > 0 y nuevos_cents > 0
		void SetEuros(int nuevos_euros){ euros = nuevos_euros; }
		void SetCentimos(int nuevos_cents){ centimos = nuevos_cents; }
		
		/************************************************************/
		//método ToString()	
		string ToString(void){
			double cantidad = GetCantidad();
			return(to_string(cantidad));
		}
		
		/************************************************************/
		//calcula la cantidad total de un objeto Dinero.
		double GetCantidad(void){
			double cantidad = euros + ((1.0/EQUIVALENTE)*centimos);
			return cantidad;
		}
		
		/************************************************************/
		//PRE: el num_meses > 0 && incremento > 0.
		void IncrementarXMeses(int num_meses, int incremento){
			int mes = 1;
			bool seguir_calculando = true;
			//se va a hacer el incremento mientras que se pueda. Si no se puede
			//hacer el incremento, porque el incremento es negativo, entonces 
			//el dinero se pone a 0.
			while(mes <= num_meses && seguir_calculando){
				if(euros >= abs(incremento)){
					IncrementarUnMes(incremento);
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
		
		/************************************************************/
		//modifica el objeto implícito incrementando su valor el valor del
		//objeto explícito cantidad. Para ello suma los euros del objeto
		//implicito y explicito por separado de la suma de los centimos del 
		//objeto implicito y explicito.
		//PRE: cantidad > 0
		Dinero Incrementa(Dinero cantidad){
			int cant_euros = euros + cantidad.GetEuros();
			int cant_cents = centimos + cantidad.GetCentimos();
			Dinero dinero_incrementado(cant_euros, cant_cents);
			
			return dinero_incrementado;
		}
		
		/***************************************************************/
		//Incrementa sin repetir código pero recibiendo un double
		Dinero Incrementa(double cantidad){
			
			return (Incrementa(Dinero(cantidad)));
		}
		
		/************************************************************/
		//modifica el objeto implícito decrementando su valor el valor del
		//objeto explícito cantidad. Para ello resta los euros del objeto
		//implicito y explicito por separado de la resta de los centimos del 
		//objeto implicito y explicito.
		//PRE: cantidad > 0
		Dinero Decrementa(Dinero cantidad){
			int cant_euros = euros - cantidad.GetEuros();
			int cant_cents = centimos - cantidad.GetCentimos();
			Dinero dinero_decrementado(cant_euros, cant_cents);
			
			return dinero_decrementado;
		}
		
		/************************************************************/
		//modifica el objeto implícito decrementando su valor el valor de
		//cantidad. Para ello resta la cantidad total del
		//objeto implicito y la cantidad introducida.
		//PRE: cantidad > 0
		Dinero Decrementa(double cantidad){
			
			return (Decrementa(Dinero(cantidad)));
		}
		
		/************************************************************/
		//modifica el objeto implícito. Suma la cantidad introducida a la 
		//cantidad implicita. En caso de que la cantidad introducida sea
		//negativa, es decir, que se quiere restar. Pero se quiere restar más
		//cantidad de la que hay, entonces la cantidad implícita no se modifica
		Dinero Modifica(double cantidad){
			double nueva_cantidad;
			if(GetCantidad()<abs(cantidad) && cantidad<0)
				nueva_cantidad = GetCantidad();
			else
				nueva_cantidad = GetCantidad() + cantidad;
				
			Dinero actualizacion(nueva_cantidad);
			
			return actualizacion;
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es mayor que la cantidad del 
		//objeto explicito.
		bool EsMayor(Dinero otro){
			bool es_mayor = true;
			if(GetCantidad() <= otro.GetCantidad())
				es_mayor = false;
			
			return es_mayor;
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es mayor que la cantidad  
		//introducida.
		//PRE: cantidad > 0
		bool EsMayor(double cantidad){
			return (EsMayor(Dinero(cantidad)));
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es menor que la cantidad del 
		//objeto explicito.
		bool EsMenor(Dinero otro){
			bool es_menor = true;
			if(GetCantidad() >= otro.GetCantidad())
				es_menor = false;
			
			return es_menor;
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es menor que la cantidad  
		//introducida.
		//PRE: cantidad > 0
		bool EsMenor(double cantidad){
			
			return (EsMenor(Dinero(cantidad)));
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es igual que la cantidad del 
		//objeto explicito.
		bool EsIgual(Dinero otro){
			bool es_igual = false;
			if(GetCantidad() == otro.GetCantidad())
				es_igual = true;
			
			return es_igual;
		}
		
		/************************************************************/
		//Comprueba si la cantidad implicita es igual que la cantidad  
		//introducida.
		//PRE: cantidad > 0
		bool EsIgual(double cantidad){
			
			return (EsIgual(Dinero(cantidad)));
		}
		
		/************************************************************/
		//Calcula el resultado de la diferencia entre la cantidad del dinero
		//implicito y la cantidad del dinero explicito. En caso de que no se 
		//pueda, porque la cantidad del explicito es mayor, entonces la 
		//diferencia es la cantidad del implicito.
		Dinero Diferencia(Dinero otro){
			Dinero diferencia_objeto(euros, centimos);
			
			if(GetCantidad() >= otro.GetCantidad()){
				double diferencia = GetCantidad() - otro.GetCantidad();
				int nuevos_euros = int(diferencia);
				int nuevos_cents = (diferencia-int(diferencia))*
															(1.0/EQUIVALENTE);
				
				diferencia_objeto.SetEuros(nuevos_euros);
				diferencia_objeto.SetCentimos(nuevos_cents);
			}
			return diferencia_objeto;
		}
		
		/************************************************************/
		//Calcula el resultado de la diferencia entre la cantidad del objeto 
		//implicito menos la cantidad introducida. En caso de que la cantidad 
		//introducida sea mayor que la cantidad implicita, se devuelve un objeto
		//con la cantidad del objeto implicito
		//PRE: cantidad > 0
		Dinero Diferencia2(double cantidad){
			Dinero diferencia_objeto(euros, centimos);
			
			if(GetCantidad() >= cantidad){
				double diferencia = GetCantidad() - cantidad;
				int nuevos_euros = int(diferencia);
				int nuevos_cents = (diferencia-int(diferencia))*
															(1.0/EQUIVALENTE);
				diferencia_objeto.SetEuros(nuevos_euros);
				diferencia_objeto.SetCentimos(nuevos_cents);	
			}

			return diferencia_objeto;	
		}


	
	private: 
		/************************************************************/
		void Simplifica(){
			while(centimos >= 100){
				centimos = centimos-100;
				euros++;
			}
		}
		
		/************************************************************/
		//se aplica el incremento un mes y se vuelve a simplificar el dinero.
		void IncrementarUnMes(int incremento){
			centimos = centimos + euros*EQUIVALENTE;
			euros = 0;
			double incremento_en_cent = incremento*EQUIVALENTE;
			
			centimos = centimos + incremento_en_cent;
			Simplifica();
		}
			
};

///////////////////////////////////////////////////////////////////////////

class DepositoBancario {
	
private:
	Dinero capital; // PRE: 0 < capital.GetCantidad()
	double interes; // PRE: 0 < interes <= 100
	
public:
	/************************************************************/
	//constructor 
	DepositoBancario(Dinero dinero, double porcentaje):
		capital(dinero), interes(porcentaje)
		{}
		
	/*************************************************************/
	//metodo getcantidad para obtener el capital
	double GetCantidadCapital(void){ return capital.GetCantidad(); }
	
	/************************************************************/
	//método set para cambiar el interés
	// PRE: 0 < nuevo_interes <= 100
	void SetInteres(double nuevo_interes){ interes = nuevo_interes; }
	
	/************************************************************/
	//método set para modificar el capital 
	// PRE: 0 < nuevo_capital
	void Setcapital(Dinero nuevo_capital){ capital = nuevo_capital; }
	
	/************************************************************/
	//el método calcula el incremento cada año que se quiere reinvertir y lo
	//suma al capital_reinvertido. De esta manera, cada año se reinvierte todo
	//el dinero.
	//PRE: 0 <= num_años <= 20
	Dinero ReinvierteXAnios(int num_anios){
		Dinero capital_reinvertido(capital);
		
		for(int i = 1; i <= num_anios; i++){
			double incremento = capital_reinvertido.GetCantidad()*interes/100;
			capital_reinvertido = capital_reinvertido.Modifica(incremento);
		}
		
		return capital_reinvertido;
	}
	
	/**************************************************************/
	//Este método calcula cuántos años se debe reinvertir el capital para que 
	//se duplique. Para ello crea un Deposito auxiliar cuyo capital inicial
	//será el del objeto implicito. Este deposito irá reinvirtiendo su capital
	//hasta que su capital sea el doble que el del capital implicito-
	int AniosParaDoblarCapital(void){
		double doble_capital = 2*capital.GetCantidad();
		DepositoBancario auxiliar(capital, interes);
		int anios = 0;
		
		while(auxiliar.GetCantidadCapital() < doble_capital){
			
			//reinvertimos todo el dinero. Por lo tanto, calculamos el capital
			//al reinvertir un año más para reinvertirlo al año siguiente.
			auxiliar.Setcapital(auxiliar.ReinvierteXAnios(1));
			anios++;
		}
		
		return anios;
	}	
};

/////////////////////////////////////////////////////////////////////////////

int main(){
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 
	
	//DECLARACION DE VARIABLES
	
	Lector lector(" Introduzca el capital a invertir: ");
	double capital_inicial;
	double interes;
	int anios;
	
	//lee el capital a invertir
	cout<<endl;
	capital_inicial = lector.LeeRealMayorOIgual(0);
	Dinero capital(capital_inicial);
	
	//lee el interes
	lector.SetTitulo(" Introduzca el interes: ");
	interes = lector.LeeEnteroEnRango(0, 100);
	
	//lee el numero de años que se quiere invertir
	lector.SetTitulo(" Introduzca el numero de anios que se quiere invertir: ");
	anios = lector.LeeEnteroEnRango(0, 20);
	
	//CALCULOS
	
	DepositoBancario cuenta1(capital, interes);
	Dinero capital_final(cuenta1.ReinvierteXAnios(anios));
	
	//SALIDA
	
	cout<<endl;
	cout<<" El capital al cabo de " << anios << " anios es " 
		<< capital_final.ToString() << endl;
	
	cout<<" Para que se doble la cantidad de capital deben pasar "
		<<cuenta1.AniosParaDoblarCapital()<< " anios." <<endl;
		
	cout<<endl<<endl;
	
	return 0;
}

