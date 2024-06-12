/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 38: el programa leerá las coordenadas del centro de un círculo
	y su radio y lo dibujará. Posteriormente, pedirá las coordenadas superior
	izquierda e inferior derecha de una rectáncgulo y tambien lo pintará. En
	caso de que las figuras se solapen, se dibujará 'x', si no, las figuras
	vendrán dadas por el caracter '*'
*/

#include<iostream> //inclusion de recursos de E/S
#include<string> //para incluir el tipo string
#include<cmath> //para incluir la raíz cuadrada
#include<iomanip>

using namespace std;

struct Punto{
	int fila;
	int columna;
};

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
	
	int entero = 3; //convierte el string respuesta en un int
	return entero;
}

/******************************************************************************/

int main(){
	cout.setf(ios::fixed);
	
	int NUM_FILAS = 51;
	int NUM_COLUMNAS = 51;
	const char FIGURA = '*';
	const char CONEXION ='x';
	const char HUECO = '.';
	char matriz[NUM_FILAS][NUM_COLUMNAS];
	
	Punto centro; //creamos el punto del centro del círculo
	int x_centro;
	int y_centro;
	
	//ENTRADA DE DATOS 
	
	cout<<endl;
	cout<< " Introduzca el centro del circulo: "<<endl;
	do{
		x_centro = LeePositivo(" Coordenada x: ");
	}while(x_centro >= NUM_FILAS || x_centro < 0);
	do{
		y_centro = LeePositivo(" Coordenada y: ");
	}while(y_centro >= NUM_COLUMNAS || y_centro < 0);
	int radio = LeePositivo(" Introduzca el radio del circulo: ");
	
	//pasamos los puntos de coordenadas a casillas de la matriz con columnas y
	//filas
	centro.fila = NUM_FILAS - y_centro;
	centro.columna = x_centro;
	
	//CALCULOS
	
	//se rellena la matriz con todas las casillas vacías, es decir, con huecos
	for(int i = 0; i < NUM_FILAS; i++ ){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			matriz[i][j] = HUECO;
		}
	}

	//calculamos cada uno de los puntos extremos de la circunferencia. Así, ya
	//podemos saber donde se ha de comenzar y de parar. Además, calculamos 
	//si el circulo se va a salir de la matriz y solucionamos el problema
	Punto ext_izq;
	ext_izq.fila = centro.fila;
	ext_izq.columna = centro.columna - radio;
		if(ext_izq.columna<0)//significa que el circulo se sale de la matriz
			ext_izq.columna = 0;
		else
			matriz[ext_izq.fila][ext_izq.columna] = FIGURA;
	
	Punto ext_dcha;
	ext_dcha.fila = centro.fila;
	ext_dcha.columna = centro.columna + radio;
		if(ext_dcha.columna>=NUM_COLUMNAS)
			ext_dcha.columna = NUM_COLUMNAS-1;
		else
			matriz[ext_dcha.fila][ext_dcha.columna] = FIGURA;
	
	Punto ext_arrb;
	ext_arrb.fila = centro.fila - radio;
	ext_arrb.columna = centro.columna;
		if(ext_arrb.fila<0)
			ext_arrb.fila = 0;
		else
			matriz[ext_arrb.fila][ext_arrb.columna] = FIGURA;
			
	Punto ext_abj;
	ext_abj.fila = centro.fila + radio;
	ext_abj.columna = centro.columna;
		if(ext_abj.fila>=NUM_FILAS)
			ext_abj.fila = NUM_FILAS-1;
		else
			matriz[ext_abj.fila][ext_abj.columna] = FIGURA;
	
	//ahora nos ponemos a pintar todo el círculo en la matriz, por columnas. 
	//Primero, miraremos la columna del centro del circulo y la pintaremos.
	//Luego, la columna_a_pintar es la del centro del circulo-1, luego es la
	//del centro del circulo-2...hasta llegar al ext_izq del circulo. Por cada
	//columna, calcularemos qué filas de esa columna hay que pintar. Para ello
	//utilizaremos que f(x,y)=x^2 + y^2 - r^2, siendo x la diferencia entre
	//la columna a pintar y la columna del centro del circulo, e y es el numero
	//de filas que se pintan por encima y por debajo de la fila del centro del
	//circulo. 
	//Además, como el circulo es simétrico, podemos calcular cómo se pintan
	//la mitad de las columnas y la otra mitad copiarla. Por ello, por cada 
	//columna que pintemos a la izquierda de la columna del centro, pintaremos
	//su equivalente a la derecha de la columna del centro del circulo. 
	int columna_a_pintar = centro.columna;
	int columna_final = ext_izq.columna;
	
	while(columna_a_pintar >= columna_final){
		
		int x = centro.columna - columna_a_pintar;
		int y = sqrt(abs(radio*radio - x*x));
		int fila_a_pintar = centro.fila + y;
		int fila_final = centro.fila-y;
		
		int equivalente = centro.columna-columna_a_pintar+x;
		while(fila_a_pintar >= fila_final){
			matriz[fila_a_pintar][columna_a_pintar] = FIGURA;
			//si la columna equivalente se sale de la matriz, no la pintamos
			if(columna_a_pintar+equivalente < ext_dcha.columna)
				matriz[fila_a_pintar][columna_a_pintar+equivalente] = FIGURA;
			fila_a_pintar--;
		}
		columna_a_pintar--;
	}
	
	//pintamos el dibujo sólo con el circulo
		
	for(int i = 0; i < NUM_FILAS; i++){
		cout<<endl;
		for(int j = 0; j < NUM_COLUMNAS; j++){
			cout<<setw(2)<<matriz[i][j];
		}
	}
	
		
	cout<<endl<<endl;
	
       /**************************RECTÁNGULO**************************/
       
    Punto sup_izq_rect;
    Punto inf_dcha_rect;
    int x_rectangulo;
    int y_rectangulo;
    //se debe crear un filtro para que las coordenadas superior izquierda e 
    //inferior derecha del circulo tengan sentido. Es, decir que la superior
    //arriba de la inferior, y la izquierda, a la izquierda de la derecha.
    do{
    	cout<< " Escriba las coordenadas del extremo";
		cout<<" superior izquierdo del rectangulo: "<<endl;
    	do{
    		x_rectangulo = LeePositivo(" Coordenada x: ");
		}while(x_rectangulo < 0 || x_rectangulo > NUM_FILAS);
    	do{
    		y_rectangulo = LeePositivo(" Coordenada y: ");
		}while(y_rectangulo < 0 || y_rectangulo > NUM_COLUMNAS);
	
		sup_izq_rect.fila = NUM_FILAS - y_rectangulo;
		sup_izq_rect.columna = x_rectangulo;
	
		cout<< " Escriba las coordenadas del extremo";
		cout<<" inferior derecho del rectangulo: "<<endl;
		do{
    		x_rectangulo = LeePositivo(" Coordenada x: ");
		}while(x_rectangulo < 0 || x_rectangulo > NUM_FILAS);
		do{
    		y_rectangulo = LeePositivo(" Coordenada y: ");
		}while(y_rectangulo < 0 || y_rectangulo > NUM_COLUMNAS);

		inf_dcha_rect.fila = NUM_FILAS - y_rectangulo;
		inf_dcha_rect.columna = x_rectangulo;	
	}while(sup_izq_rect.fila > inf_dcha_rect.fila || 
		sup_izq_rect.columna > inf_dcha_rect.columna);
	
	
	//CALCULOS
	
	//pintaremos el rectngulo por columnas de izquierda a derecha. La primera
	//columna, obviamente, es la del extremo superior izquierdo del rectangulo.
	//Y la ultima columna es la del extremo inferior izquierdo. 
	//En cada columna pintamos las filas que correspondan, y lo haremos de 
	//abajo hacia arriba. Por tanto, la primera fila será la del extremo 
	//inferior derecho, y la ultima fila será la del superior derecho.
	//En caso de que en la casilla de la matriz ya haya pintado un caracter
	//figura, significará que en esa casillaya está pintado el circulo, por
	//tanto, se cambiará el caracter FIGURA por elcaracter CONEXION.
	columna_a_pintar = sup_izq_rect.columna;
	columna_final = inf_dcha_rect.columna;
	while(columna_a_pintar <= columna_final){
		int fila_a_pintar = inf_dcha_rect.fila;
		int fila_final = sup_izq_rect.fila;
		while(fila_a_pintar >= fila_final){
			if(matriz[fila_a_pintar][columna_a_pintar] == FIGURA)
				matriz[fila_a_pintar][columna_a_pintar] = CONEXION;	
			else
				matriz[fila_a_pintar][columna_a_pintar] = FIGURA;
			fila_a_pintar--;
		}
		columna_a_pintar++;
	}
	
	//pintamos la matriz con el circulo y el rectangulo.
	for(int i = 0; i < NUM_FILAS; i++){
		cout<<endl;
		for(int j = 0; j < NUM_COLUMNAS; j++){
			cout<<setw(2)<<matriz[i][j];
		}
	}
	
	cout<<endl<<endl;
	
	return 0;
}
