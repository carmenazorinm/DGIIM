/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 1: el programa lee enteros y los va guardando en el vector datos.
	Una vez esté el vector completado o se haya introducido un negativo, se 
	dejarán de leer enteros. Con el vector ya hecho, se modificará éste
	para que se quede un vector sin numeros repetidos. Para ello utilizará 
	una variable posicion_lectura que irá leyendo todos los numeros anteriores
	a su posicion; y una variable posicion_escritura que se quedará en una
	posicion fija hasta que se actualice el valor que le corresponde. 
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	const int MAX = 50; //no hará falta utilizar las 50 posiciones del vector
	int datos[MAX];
	int dato; //el entero que se va a leer
	int numero_casilla = 0; //contador para saber en qué posicon del vector hay
							//hay que introducir el siguiente dato leido
	bool seguir_pidiendo = true;
	
	while(seguir_pidiendo && numero_casilla < MAX){	
		cin>>dato;
		
		if(dato >= 0){
			datos[numero_casilla] = dato;
			numero_casilla++;
		}else
			seguir_pidiendo = false;
	}
	
	int posicion_lectura = 1; 
	int posicion_escritura = 1;
	bool esta_repetido;
	
	for(int j = 0; j < numero_casilla -1; j++){//tantas veces como casillas se 
											   //hayan rellenado con datos
		
		int i = 0;
		esta_repetido = false;
		
		//va mirando todos los datos de las posiciones anteriores a la 
		//posicion_lectura y comprobando que todos son diferentes al de esta 
		//posicon. Si alguno es igual, entonces esta_repetido = true y se 
		//dejarán de mirar el resto de las posiciones
		while(i < posicion_lectura && !esta_repetido){
			if(datos[i] == datos[posicion_lectura]){
				esta_repetido = true;
			}
			i++;
		}
		
		//si se han leido todos los datos anteriores al dato de la posicion de 
		//lectura y ninguno es igual a éste, entonces en la posicion de 
		//escritua se meterá ese dato.
		if(!esta_repetido){
			datos[posicion_escritura] = datos[posicion_lectura];
			posicion_escritura++;
		}
		
		//la posicion de lectura correindependientemente de si el dato está 
		//repetido o no.
		posicion_lectura++;
	}
	for(int l = posicion_escritura; l < MAX; l++){//en las casillas del vector 
												//que no se hayan rellenado, se
												//introducirá 0
		datos[l] = 0;
	}
	
	
	//salida
	
	cout<<endl;
	for(int k = 0; k < MAX; k++){
		cout<< " Posicion " << k<< ": "<< datos[k];
		cout<<endl;
	}
	cout<<endl<<endl;
	
	return 0;
}
