/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 31: el programa lee distancias entre ciudades, para ello primero
	pregunta cuántas ciudades se van a comparar. Se asegura de preguntar por
	las distancias entre ciudades que no tenga ya. A partir de ahí:
	a) se calcula cuál es la ciudad con mas conexiones directas 
	b) se pregunta por una ciudad y se muestran sus conexiones directas
	c) se pregunta por dos ciudades que no tengan conexion directa y se muestra
	cuál es la ciudad intermedia por la que se debería pasar para hacer el 
	menor recorrido posible
	d) se preguntan por varias ciudades y se dicen si las ciudades están todas
	conectadas entre ellas o no.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

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
		getline( cin, respuesta);
		es_valido = ComprobarQueEsPositivo(respuesta);
	}while(!es_valido);
	
	int entero = stoi(respuesta); //convierte el string respuesta en un int
	return entero;
}

/*****************************************************************************/

int main(){
	
	const int MAX_CIUDADES = 50;
	int num_ciudades;
	double distancia_ciudades[MAX_CIUDADES][MAX_CIUDADES];
	//se crea un vector que guarda cuántas conexiones directas tiene 
	//cada ciudad
	int conexiones_directas_ciudades[MAX_CIUDADES] = {0};
	
	//inicializamos todos los valores de la matriz a -1, para que en el momento
	//de rellenar todas las casillas de la matriz, sepamos qué casillas están 
	//ya rellenas y cuáles no
	for( int i = 0; i < MAX_CIUDADES; i++){
		for(int j = 0; j < MAX_CIUDADES; j++){
			distancia_ciudades[i][j] = -1;
		}
	}
	
	//ENTRADA DE DATOS

	num_ciudades = LeePositivo(" Introduzca el numero de ciudades totales: ");
	
	for (int i = 0; i< num_ciudades-1; i++){
		cout<< " Introduzca la distancia de la ciudad "<< i+1 <<": "<<endl;
		
		for(int j = 0; j < num_ciudades; j++){
			if(i==j) //la distancia de una ciudad a sí misma es 0
				distancia_ciudades[i][j] = 0;
			else{
				if(distancia_ciudades[i][j] == -1){//si todavía no sabemos la 
												   //distancia entre dos 
												   //ciudades, la pedimos
					do{
						cout<< " con la ciudad "<< j+1 << ": ";
						cin>> distancia_ciudades[i][j];
					}while(distancia_ciudades[i][j] < 0);
					//sabemos que la matriz es simétrica, porque la distancia 
					//de la ciudad 0 a la 1, es la misma distancia que la de la
					//ciudad 1 a la 0. Por tanto,
					distancia_ciudades[j][i] = distancia_ciudades[i][j];
				}
			}
		}
	}
	
	//CALCULOS
	
	//APARTADO A
	
	int ciudad_mas_conexiones = 0;
	
	//rellenamos el vector conexiones_directas_ciudades[]. Para ello vamos 
	//mirando fila por fila de la matriz y añadimos +1 a la ciudad de la fila, 
	//cada vez que en una de sus columnas la distancia =/= 0
	for(int i = 0; i < num_ciudades; i++){
		for(int j = 0; j < num_ciudades; j++){
			if(distancia_ciudades[i][j] != 0)
				conexiones_directas_ciudades[i]++;
		}
	}
	
	//calculamos cual es la ciudad con mas conexiones.
	for(int i = 1; i < num_ciudades; i++){
		if(conexiones_directas_ciudades[i] > 
							conexiones_directas_ciudades[ciudad_mas_conexiones])
		ciudad_mas_conexiones = i;
	}
	
	cout<<endl;
	cout<< " La ciudad con mas conexiones directas es la numero ";
	cout<< ciudad_mas_conexiones+1;
	cout<< " con "<< conexiones_directas_ciudades[ciudad_mas_conexiones];
	cout<< " conexiones."<<endl;
	
	//APARTADO B
	
	int ciudad;
	cout<<endl;
	do{
		ciudad = LeePositivo(" Introduzca una ciudad: ");
	}while(ciudad<= 0 || ciudad>num_ciudades);
	cout<< " Se conecta de forma directa con las ciudades: ";
	
	//vamos mirando la fila de la ciudad en la matriz y cada vez que en una de 
	//columnas aparezca una distancia distinta de 0, mostramos la ciudad que
	//corresponde con la columna
	for(int i = 0; i < num_ciudades; i++){
		if(distancia_ciudades[ciudad-1][i] != 0)
			cout<< i+1<< " ";
	}
	cout<<endl;
	
	//APARTADO C
	
	int ciudad1;
	int ciudad2;
	cout<<endl;
	cout<< " Introduzca dos ciudades que no tengan conexion directa: ";
	cout<<endl;
	//se crea un filtro para que se introduzcan obligatoriamente dos ciudades 
	//que no tengan conexion directa
	do{
		ciudad1 = LeePositivo(" Ciudad 1: ");
		ciudad2 = LeePositivo(" Ciudad 2: ");
	}while(distancia_ciudades[ciudad1-1][ciudad2-1] != 0);
	
	double distancia_total; 
	double distancia_minima;
	int ciudad_intermedia;
	int aux = 0;
	bool seguir_buscando = true;
	
	while(seguir_buscando){//Se busca la primera ciudad que conecte 
						   //ambas ciudades y se calcula la distancia total
						   //entre ciudad1 y ciudad2 pasando por dicha ciudad
						   //calculada y por, ahora, esa es la minima distancia
		if(distancia_ciudades[aux][ciudad1-1] != 0 
								&& distancia_ciudades[aux][ciudad2-1] != 0){
		distancia_total = distancia_ciudades[aux][ciudad1-1] + 
											distancia_ciudades[aux][ciudad2-1];
		seguir_buscando = false;
		}
		ciudad_intermedia = aux; //la ciudad intermedia buscada es, por ahora, 
								 //la primera ciudad encontrada que conecta 
								 //a ciudad1 y ciudad2
		aux++;
	}
	distancia_minima = distancia_total; 
	
	//se buscan el resto de ciudades que conectan a ciudad1 y ciudad2 y se 
	//mira qué distancia entre ciudad1 y ciudad2 pasando por dichas ciudades
	//es menor. 
	for(int i = aux; i < num_ciudades; i++){
		if(distancia_ciudades[i][ciudad1-1] != 0 
									&& distancia_ciudades[i][ciudad2-1] != 0){
			distancia_total =  distancia_ciudades[i][ciudad1-1] + 
											distancia_ciudades[i][ciudad2-1];
		}
		if(distancia_total < distancia_minima){
			distancia_minima = distancia_total;
			ciudad_intermedia = i;
		}
	}
	cout<< " La ciudad intermedia que se debe cruzar para ahorrar en distancia";
	cout<< " es la numero " << ciudad_intermedia+1<< " y se recorrerian ";
	cout<< distancia_minima;
	
	//APARTADO D
	
	int supuestas_ciudades_conectadas[MAX_CIUDADES];//se crea n vector que 
													//guarde las ciudades 
													//introducidas por el
													//usuario
	int posicion = 0;
	int TERMINADOR = -1;
	int numero; //los valores que se van a ir leyendo
	bool estan_conectadas = true;
	
	cout<< endl<<endl;
	cout<< " Introduzca numeros de ciudades para saber si estan conectadas ";
	cout<< "entre si: ";
	do{
		cout<< " Ciudad "<<posicion+1<< ": ";
		cin>>numero;	
		if(numero > 0 && numero <= num_ciudades){
			supuestas_ciudades_conectadas[posicion] = numero;
			posicion++;
		}else
			numero = TERMINADOR;
	}while(numero != TERMINADOR);
	
	//se va mirando ciudad por ciudad guardada en el vector 
	//supuestas_ciudades_conectadas[] y se mira si está conectada directamente
	//con el resto de ciudades del vector
	for(int i = 0; i < posicion; i++){
		//miramos cuál es la primera ciudad a comparar
		int ciudad_a_comparar = supuestas_ciudades_conectadas[i];
		//vamos a comparar ciudad_a_comparar con el resto de ciudades 
		//siguientes a ella
		int siguiente_ciudad = supuestas_ciudades_conectadas[i+1];
		for(int j = siguiente_ciudad; j < posicion; j++){
			//si en la matriz primera, la distancia entre una ciudad y otra de 
			//las que estamos comparando es 0, entonces no están conectadas. 
			if(distancia_ciudades[ciudad_a_comparar]
										[supuestas_ciudades_conectadas[j]] == 0)
				estan_conectadas = false;
		}
	}
	
	if(estan_conectadas){
		cout<< " Las ciudades introducidas estan todas conectadas."<<endl;
	}else
		cout<< " Las ciudades introducidas no estan todas conectadas.";
	cout<<endl<<endl;
	
	return 0;
}
