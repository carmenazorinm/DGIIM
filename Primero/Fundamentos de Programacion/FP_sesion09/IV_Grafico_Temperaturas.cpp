/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 34: el programa lee todas las temperaturas del año y las 
	introduce en el vector temperaturas[]. Con un for, meterá las temperaturas 
	de 7 en 7 en temp_semana[], un vector que se irá modificando cada semana e 
	introducirá su minima y su maxima temperatura en el vector minimos[] y 
	maximos[]. Una vez estén llenos estos dos ultimos vectores, tendremos las
	minimas y las maximas temperaturas del año por semanas y podremos hacer las
	dos gráficas. 
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //para incluir el absoluto
#include<iomanip>

using namespace std;

double BuscaMinimoDelVector(double vector[7]){//al introducir el vector 
											  //que contiene a las temperaturas 
											  //de la semana, sacamos el minimo.
	
	double minimo = vector[0];
	for(int i = 1; i < 7; i++){
		if(vector[i]<minimo)
			minimo = vector[i];
	}
	return minimo;
}
double BuscaMaximoDelVector(double vector[7]){//sacamos el maximo de las
											  //temperaturas de cada semana
	
	double maximo = vector[0];
	for(int i = 1; i < 7; i++){
		if(vector[i]>maximo)
			maximo = vector[i];
	}
	return maximo;
}
/******************************************************************************/

int main(){
	cout.setf(ios::fixed);
	
	const int DIAS_ANIO = 365;
	const int DIAS_SEMANA = 7;
	const int SEMANAS_ANIO = DIAS_ANIO/DIAS_SEMANA;
	
	double temperaturas[DIAS_ANIO];//se guardan las temperaturas de todo el año
	double temp_semana[DIAS_SEMANA];//este vector guarda las primeras 7 
									//temperaturas del año y saca la minima y 
									//la maxima. Luego vuelve a llenarse con 
									//las siguientes 7 temperaturas y vuelve a 
									//sacar la maxima y la minima								
	double minimos[SEMANAS_ANIO];//guarda las minimas temperaturas de cada 
								 //semana del año
	double maximos[SEMANAS_ANIO];//guarda las maximas temperaturas de cada
								 //semana del año
	double temperatura;//para leer las temperaturas que se introducen
	
	const double MAX_TEMP = 50.0;//la maxima temperatura del grafico
	const double MIN_TEMP = -10;//la minima temperatura del grafico
	
	//ENTRADA DE DATOS
	
	cout<<endl;
	cout<< " Introduzca las temperaturas de cada día del anio: ";
	cout<<endl;
	for(int i = 0; i < DIAS_ANIO; i++){
		do{
			cout<< " Dia " << i+1 <<": ";
			cin>>temperatura;
			temperaturas[i] = temperatura;
		}while(temperatura > MAX_TEMP || temperatura < MIN_TEMP);
	}
	
	//CALCULOS

	int dia_sem = 0;
	int pos_min = 0;
	int pos_max = 0;
	
	//en el siguiente for, se van a ir metiendo las primeras 7 temperaturas del
	//año en el vector temp_semana[7] y se buscará su minimo y su maximo. 
	//Después mete las siguientes 7 temperaturas del año y vuelve a calcular
	//los extremos.  
	for(int i = 0; i < DIAS_ANIO; i++){
		temp_semana[dia_sem] = temperaturas[i];
		if(dia_sem == DIAS_SEMANA-1){
			minimos[pos_min] = BuscaMinimoDelVector(temp_semana);
			maximos[pos_max] = BuscaMaximoDelVector(temp_semana);
			pos_min++;
			pos_max++;
			dia_sem = -1; //para que en la siguiente instruccion, dia_sem = 0;
		}
		dia_sem++;
	}
	
	//para hacer la gráfica
	
	const int NUM_FILAS = 20;
	const int NUM_COLUMNAS = 60;
	const char TRAZO = '*';
	const char HUECO = '.'; 
	
	char tablero[NUM_FILAS][NUM_COLUMNAS];
	
	//la grafica va a tener en el eje de ordenadas intervalos de temperaturas
	//Como queremos que haya 20 filas y las temperatura maxima = 50 y la 
	//minima = -10, entonces cada intervalo va a tener 3 grados.
	const double INTERVALO = (abs(MIN_TEMP)+abs(MAX_TEMP))/NUM_FILAS;
	
	for(int i = 0; i < NUM_FILAS; i++){//pintamos todo el tablero con huecos
		for(int j = 0; j < NUM_COLUMNAS; j++){
			tablero[i][j] = HUECO;
		}
	}
	
	//se pinta la grafica de los minimos
	cout<<endl<< " Medias de las minimas semanales: ";
	cout<<endl;
	
	//con el vector minimos[] se va a ir cogiendo cada temperatura del vector
	//y se va a calcular su fila (la columna es la propia posicion que ocupa en 
	//vector). Para calcular su fila, calculamos entre que rangos de 
	//temperaturas está. Por tanto, empezamos con la minimos[0]. Si esta 
	//temperatura es mayor que (-10+3 = -7), entonces estará una fila más
	//arriba en el tablero (fila 19). Si la temperatura es mayor que (-7+3 = -4)
	//entonces su fila será una más en el tablero (fila 18). Una vez encontramos
	//su fila, pintamos el trazo en tablero[fila][i]. Y hace lo mismo con la 
	//temperatura de minimos[1], minimos[2],...,minimos[SEMANAS_ANIO-1]
	for(int i = 0; i < SEMANAS_ANIO; i++){
		int interv = MIN_TEMP + INTERVALO;
		int fila = NUM_FILAS;
		
		while(minimos[i] > interv){
			fila--;
			interv = interv + INTERVALO;
		}
		fila--;
		tablero[fila][i] = TRAZO;
	}
	
	double max_intervalo = MAX_TEMP;
	double min_intervalo = max_intervalo - INTERVALO;
	
	//por cada fila se va a pintar primero un intervalo representado por su 
	//maximo (al principio será 50) y su minimo (al principio será 50-3=47)
	//Después de pintar el primer vector, se pintará la fila completa de la 
	//matriz, que ya estará rellena con los huecos y los trazos. 
	//Una vez se ha pintado la primera fila, se calcula el siguiente vector
	//cuyo maximos será el minimo de antes y el nuevo minimo será el maximo
	//menos el intervalo. Y se volverá a pintar la fila completa del tablero...
	for(int i = 0; i < NUM_FILAS; i++){
		cout<<endl;
		//en total se van a ocupar 25 huecos para escribir cada intervalo
		cout<<" ("<<setw(10)<<max_intervalo<<","<<setw(10)<<min_intervalo<<") ";
		for(int j = 0; j < NUM_COLUMNAS; j++){
			cout<<tablero[i][j];
		}
		max_intervalo = min_intervalo;
		min_intervalo = max_intervalo - INTERVALO;
	}
	
	//el programa indicará, debajo del tablero, a qué semana corresponde cada 
	//columna. Para ello, primero pintará las 25 posiciones que hemos calculado
	//antes que servían para escribir los intervalos. A partir de las 25 
	//25 posiciones, empieza a pintarse el tablero. Cada 5 columnas del tablero
	//pondrá debajo 5, luego 10, luego 15... Para indicar a qué semana pertenece
	//cada columna cada 5 semanas
	cout<<endl<<setw(25)<<" ";
	int dia_columna = 0;
	while(dia_columna < NUM_COLUMNAS){
		dia_columna += 5;
		cout<<setw(5)<<dia_columna;
	}
	
	cout<<endl<<endl<<endl;
	
	//se pinta la grafica de los maximos. Se volverá a poner el tablero en 
	//huecos y se hará exactamente lo mismo que con las minimos, solamente
	//que ahora se pintarán las temperaturas del vector maximos[].
	
	cout<< endl<<" Medias de las maximas semanales: ";
	cout<<endl;
	 
	for(int i = 0; i < NUM_FILAS; i++){
		for(int j = 0; j < NUM_COLUMNAS; j++){
			tablero[i][j] = HUECO;
		}
	}
	
	for(int i = 0; i < SEMANAS_ANIO; i++){
		int interv = MIN_TEMP + INTERVALO;
		int fila = NUM_FILAS;
		
		while(maximos[i] > interv){
			fila--;
			interv = interv + INTERVALO;
		}
		fila--;
		tablero[fila][i] = TRAZO;
	}
	
	max_intervalo = MAX_TEMP;
	min_intervalo = max_intervalo - INTERVALO;
	
	for(int i = 0; i < NUM_FILAS; i++){
		cout<<endl;
		cout<<" ("<<setw(10)<<max_intervalo<<","<<setw(10)<<min_intervalo<<") ";
		for(int j = 0; j < NUM_COLUMNAS; j++){
			cout<<tablero[i][j];
		}
		max_intervalo = min_intervalo;
		min_intervalo = max_intervalo - INTERVALO;
	}
	
	cout<<endl<<setw(25)<<" ";
	dia_columna = 0;
	while(dia_columna < NUM_COLUMNAS){
		dia_columna += 5;
		cout<<setw(5)<<dia_columna;
	}
	
	cout<<endl<<endl<<endl;
	
	return 0;
}
