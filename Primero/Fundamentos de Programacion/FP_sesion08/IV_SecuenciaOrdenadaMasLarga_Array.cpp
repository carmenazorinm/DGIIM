/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 22: el programa lee 100 temperaturas o menos, hasta que se 
	introduzca -1. Estas temperaturas se ir�n guardando en el vector 
	temperaturas[]. Se quiere saber cu�l es la secuencia ordenada de menor a 
	meor m�s grande que tiene el vector. Para ello se crear� un vector que 
	se llamar� secuencia_mas_larga[] en el que se introducir�n los valores de 
	las temperaturas de la secuencia mas larga hasta el momento. El programa
	utilizar� otro vector posible_secuencia[] que guardar� las temperaturas de 
	la siguiente secuencia del vector temperaturas[] si el vector 
	posible_secuencia[] tiene m�s temperturas que el vector 
	secuencia_mas_larga[], entonces se sustituir�n las temperaturas de �ste 
	ultimo por las de posible_secuencia[]. As� se comparar�n todas las 
	secuencias ordenadas del vector temperaturas[] y se mostrar� la secuencia
	m�s larga, que estar� incluida en secuencia_mas_larga[]. Adem�s se mostrar�
	cu�ntas temperaturas tiene secuencia_mas_larga[] y en que posicion empieza  
	la secuencia mas larga del vector temperaturas[].
*/

#include<iostream> //inclusion recursos de E/S

using namespace std;

int main(){
	
	int MAX_TEMPERATURAS = 100;
	double temperaturas[MAX_TEMPERATURAS];
	double temperatura; //el dato que se va a leer en cada casilla del vector
	int TERMINADOR = -1;// cuando se introduzca -1, se deja de leer valores
	
	int numero_temperaturas = 0; //para contar cuantas temperaturas ha leido
								 //el vector temperaturas[]
	int posicion = 0; //para saber en qu� posicion se tiene que meter cada temp
	bool seguir_pidiendo = true;
	
	//ENTRADA DE DATOS
	
	cout<< endl;
	cout<< " Introduzca las temperaturas: ";
	
	while(seguir_pidiendo && numero_temperaturas < MAX_TEMPERATURAS){	
		cin>>temperatura;
		
		if(temperatura != TERMINADOR){
			temperaturas[posicion] = temperatura;
			numero_temperaturas++;
			posicion++;
		}else
			seguir_pidiendo = false;
	}
							 
	//CALCULOS	
	
	//se crean dos vectores distintos del vector temperaturas[], uno que va a 
	//guardar las temperaturas de la secuencia mas larga hasta el momento y 
	//otro que va a guardar la siguiente secuencia de este. Se contar�n cu�ntos
	//valores hay en cada vector mediante las variables contador_sec y 
	//contador_posible. 
	double secuencia_mas_larga[MAX_TEMPERATURAS]; 
	double posible_secuencia[MAX_TEMPERATURAS];
	int contador_sec = 0;
	int contador_posible = 0;
	
	bool seguir_guardando = true;
	int posicion_comienza_secuencia = 0; //variable que guardar� en qu� 
										//posici�n del vector temperaturas[] 
										//comienza la secuencia m�s larga
	int posicion_sec = 1; //posicion de los vectores de secuencias
	int posicion_temp = 1; //posicion en la que se va a leer la temperatura
	 					   //en el vector temperaturas[]. Empieza en la primera
	 					   //posicion, porque se va acomprobar que la 
	 					   //temperatura de esta posicion sea mayor que la de 
	 					   //la anterior posicion
	
	secuencia_mas_larga[0] = temperaturas[0];
	//se va a guardar la primera secuencia, que hasta el momento ser� la m�s 
	//larga. En caso de que la temperatura de posicion_temp sea mayor que la 
	//temperatura de la posicion anterior a �sta, entonces se guarda el valor
	//en secuencia_mas_larga[]
	while(seguir_guardando && posicion_temp < numero_temperaturas){
		if(temperaturas[posicion_temp] > temperaturas[posicion_temp-1]){
			secuencia_mas_larga[posicion_sec] = temperaturas[posicion_temp];
			contador_sec++; //se va a guardar cu�ntas temperaturas guarda el 
							//vector secuenica_mas_larga[]
			posicion_sec++;
		}else
			seguir_guardando = false;
		posicion_temp++; //esta posicion siempre avanza independientemente del
						 //valor que se lea
	}
	//al final del bucle, la posicion_temp ser� una posicion mayor que la 
	//posicion donde empieza la siguiente secuencia. Es decir, si la secuencia
	//m�s larga acaba en la posicion 3 de temperaturas[], la siguiente 
	//secuencia empezar� en la posicion 4 de temperaturas[] y posicion_temp=5;
	
	while(posicion_temp < numero_temperaturas){
		contador_posible = 0;
		int posible_posicion_comienza_secuencia = posicion_temp-1;
		seguir_guardando = true;
		posicion_sec = 1; //otra vez ponemos el vector secuencia en 1, por la 
						  //misma raz�n que antes, queremos comparar esta 
						  //posicion con la anterior. Si la posicion_sec=0, no
						  //podr�amos comparar con la posicion anterior, porque
						  //no existe
	
		posible_secuencia[posicion_sec-1]=temperaturas[posicion_temp-1];
						  
		//usamos el mismo m�todo que antes, si la temperatura de la 
		//posicion_temp es mayor que la anterior, entonces se a�aden las 
		//dos al vector posible_secuencia[]
		while(seguir_guardando && posicion_temp < numero_temperaturas){
			if(temperaturas[posicion_temp] > temperaturas[posicion_temp-1]){
				posible_secuencia[posicion_sec] = temperaturas[posicion_temp];
				contador_posible++;
				posicion_sec++;
			}else
				seguir_guardando = false;
			posicion_temp++;
		}
		
		//si hay m�s temperaturas en el vector posible_secuencia[], entonces 
		//todas las temperaturas de secuencia_mas_larga[] se sustituir�n por   
		//las temperaturas de posible_secuencia[]
		if(contador_posible > contador_sec){
			for(int k = 0; k < contador_posible+1; k++)
				secuencia_mas_larga[k] = posible_secuencia[k];
			contador_sec = contador_posible;
			posicion_comienza_secuencia = posible_posicion_comienza_secuencia;
		}
	}
	
	cout<< " La secuencia m�s larga de temperaturas es: ";
	for(int k = 0; k<=contador_sec; k++){
		cout<< secuencia_mas_larga[k]<< " ";
	}
	cout<< endl;
	cout<< " Tiene un total de "<< contador_sec+1 << " temperaturas.";
	cout<<endl; //el contador_sec tiene el numero de posiciones del vector
				//secuencia_mas_larga[] y s� que est�n rellenas todas las 
				//posiciones incluyendo la del 0, as� que pongo +1.
	cout<< " Empieza en la temperatura numero ";
	cout<< posicion_comienza_secuencia+1; //quiero que las posiciones empiecen
										  //en 1 y no en 0
	cout<< endl << endl;
	
	
	
	return 0;
}
