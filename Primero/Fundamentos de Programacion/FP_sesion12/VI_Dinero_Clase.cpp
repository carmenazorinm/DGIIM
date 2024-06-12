/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 5: el programa lee una cantidad inicial de dinero. esta cantidad 
	va a pasar a ser un objeto de la clase Dinero. A partir de ahí, se van a ir
	haciendo modificaciones a la cantidad leida mediante distintos métodos.
	Después de utilizar los distintos métodos de incrementar la cantidad, 
	decrementar y modificar, comienzan los métodos de comparación. En estos 
	métodos se van a ir pidiendo cantidades nuevas para comparar si la nueva
	cantidad es mayor, menor o igual que la cantidad inicial. Finalmente, se 
	ejecutarán los métodos de diferencia. Para ello se pide una nueva cantidad
	y se calcula la diferencia entre la nueva cantidad y la cantidad inicial.
	
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
			double nueva_cantidad = GetCantidad();
			if(GetCantidad()>cantidad)
				nueva_cantidad = GetCantidad() - cantidad;
				
			Dinero actualizacion(nueva_cantidad);
			
			return actualizacion;
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
			bool es_mayor = true;
			if(GetCantidad() <= cantidad)
				es_mayor = false;
			
			return es_mayor;
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
			bool es_menor = true;
			if(GetCantidad() >= cantidad)
				es_menor = false;
			
			return es_menor;
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
			bool es_igual = false;
			if(GetCantidad() == cantidad)
				es_igual = true;
			
			return es_igual;
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

/*****************************************************************************/
/*****************************************************************************/

double GetParteDecimal (double num_double){
	num_double = num_double - int(num_double);
	return num_double;
}
      /*****************************************************************/
      /*****************************************************************/
      /*****************************************************************/

int main(){
	cout.setf(ios::fixed);
	
	Lector lector(" Introduzca la cantidad inicial: ");
	double cantidad;
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	cantidad = lector.LeeRealMayorOIgual(0);
	
	Dinero cantidad_inicial(cantidad);
	
	cout<< endl << " Cantidad inicial = " << setw(4)
	    <<cantidad_inicial.ToString()<<endl<<endl;
	
	//INCREMENTO DINERO OBJETO
	
	cout<<"________CALCULO DE UN INCREMENTO POR OBJETO________"<<endl;
	lector.SetTitulo(" Introduzca un incremento: ");
	double incremento = lector.LeeRealMayorOIgual(0);
	
	Dinero incremento_objeto(incremento);
	cantidad_inicial = cantidad_inicial.Incrementa(incremento_objeto);
	
	cout<<" Cantidad actual =  "
		<< cantidad_inicial.ToString() << endl<<endl;
	
	//DECREMENTO DINERO OBJETO
	
	cout<<"________CALCULO DE UN DECREMENTO POR OBJETO________"<<endl;
	lector.SetTitulo(" Introduzca un decremento: ");
	double decremento = lector.LeeRealMayorOIgual(0);
	
	Dinero decremento_objeto(decremento);
	cantidad_inicial = cantidad_inicial.Decrementa(decremento_objeto);
	
	cout<<" Cantidad actual =  "
		<< cantidad_inicial.ToString() << endl<<endl;
	
	//DECREMENTO DINERO CANTIDAD
	
	cout<<"________CALCULO DE UN DECREMENTO POR CANTIDAD________"<<endl;
	lector.SetTitulo(" Introduzca otro decremento: ");
	decremento = lector.LeeRealMayorOIgual(0);
	
	cantidad_inicial = cantidad_inicial.Decrementa(decremento);
	cout<<" Cantidad actual =  "
		<< cantidad_inicial.ToString() << endl<<endl;
		
	//MODIFICA DINERO CANTIDAD
	
	cout<<"________CALCULO DE UNA MODIFICACION POR CANTIDAD________"<<endl;
	lector.SetTitulo(" Introduzca cuanto desea modificar: ");
	double modificacion = lector.LeeReal();
	
	cantidad_inicial = cantidad_inicial.Modifica(modificacion);
	cout<<" Cantidad actual =  "
		<< cantidad_inicial.ToString() << endl<<endl;
	
	//COMPROBAR QUE ES MAYOR POR OBJETO
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES MAYOR POR OBJETO________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	Lector lector2(" Introduzca otra cantidad: ");
	double otra_cant = lector2.LeeRealMayorOIgual(0);
	
	Dinero cantidad_comparar_mayor(otra_cant);
	bool es_mayor = cantidad_inicial.EsMayor(cantidad_comparar_mayor);
	
	if(es_mayor)
		cout<<cantidad_inicial.ToString() << " es mayor que "
			<<cantidad_comparar_mayor.ToString() << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es mayor que "
			<<cantidad_comparar_mayor.ToString() << endl;
	
	//COMPROBAR QUE ES MAYOR POR CANTIDAD
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES MAYOR POR CANTIDAD________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	es_mayor = cantidad_inicial.EsMayor(otra_cant);
	
	if(es_mayor)
		cout<<cantidad_inicial.ToString() << " es mayor que "
			<<otra_cant << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es mayor que "
			<<otra_cant << endl;
	
	//COMPROBAR QUE ES MENOR POR OBJETO
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES MENOR POR OBJETO________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	Dinero cantidad_comparar_menor(otra_cant);
	bool es_menor = cantidad_inicial.EsMenor(cantidad_comparar_menor);
	
	if(es_menor)
		cout<<cantidad_inicial.ToString() << " es menor que "
			<<cantidad_comparar_menor.ToString() << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es menor que "
			<<cantidad_comparar_menor.ToString() << endl;
	
	//COMPROBAR QUE ES MENOR POR CANTIDAD
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES MENOR POR CANTIDAD________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	es_menor = cantidad_inicial.EsMenor(otra_cant);
	
	if(es_menor)
		cout<<cantidad_inicial.ToString() << " es menor que "
			<<otra_cant << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es menor que "
			<<otra_cant << endl;
	
	//COMPROBAR QUE ES IGUAL POR OBJETO
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES IGUAL POR OBJETO________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	Dinero cantidad_comparar_igual(otra_cant);
	bool es_igual = cantidad_inicial.EsIgual(cantidad_comparar_igual);
	
	if(es_igual)
		cout<<cantidad_inicial.ToString() << " es igual que "
			<<cantidad_comparar_igual.ToString() << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es igual que "
			<<cantidad_comparar_igual.ToString() << endl;
	
	//COMPROBAR QUE ES IGUAL POR CANTIDAD
	
	cout<<endl;
	cout<<"________COMPROBAR SI ES IGUAL POR CANTIDAD________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	es_igual = cantidad_inicial.EsIgual(otra_cant);
	
	if(es_igual)
		cout<<cantidad_inicial.ToString() << " es igual que "
			<<otra_cant << endl;
	else
		cout<<cantidad_inicial.ToString() << " no es igual que "
			<<otra_cant << endl;
	
	//DIFERENCIA DINERO POR OBJETO
	
	cout<<endl;
	cout<<"________CALCULO DE LA DIFERENCIA POR OBJETO________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad a restar: ");
	otra_cant = lector.LeeRealMayorOIgual(0);
	
	Dinero cantidad_a_restar(otra_cant);
	Dinero cantidad_diferencia;
	cantidad_diferencia = cantidad_inicial.Diferencia(cantidad_a_restar);
	
	cout<<" Diferencia ("<< cantidad_inicial.ToString() << " - " 
		<< cantidad_a_restar.ToString() << ") = " 
		<< cantidad_diferencia.ToString() << endl;
	
	//DIFERENCIA DINERO POR CANTIDAD
	
	cout<<endl;
	cout<<"________CALCULO DE LA DIFERENCIA POR OBJETO________"<<endl;
	cout<<" Cantidad actual = " << cantidad_inicial.ToString() <<endl;
	lector.SetTitulo(" Introduzca otra cantidad a restar: ");
	otra_cant = lector.LeeReal();
	
	cantidad_diferencia = cantidad_inicial.Diferencia2(otra_cant);
	
	cout<<" Diferencia ("<< cantidad_inicial.ToString() << " - " 
		<< otra_cant << ") = " 
		<< cantidad_diferencia.ToString() << endl;
	
	cout<<endl<<endl;
	return 0;
}
