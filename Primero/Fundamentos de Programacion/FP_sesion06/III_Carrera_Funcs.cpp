/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 14: el programa lee una hora de inicio y una distancia. A partir
	de ahí, va leyendo dorsales de jugadores y su hora de llegada. Calcula
	mediante la funcion diferencia_tiempo, el tiempo tardado en hacer la 
	carrera. Y con las funciones velocidad y ritmo, calculan los km/h y los
	minutos por kilómetro de la cada corredor. Se leerán dorsales hasta que
	se lea un numero negativo.
	
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

void diferencia_tiempo (int segundos_totales){
	
	const int SEGUNDOS_EN_DIA = 3600*24;
	
	bool cambio_dia = segundos_totales<=0;
	if(cambio_dia){
		segundos_totales = SEGUNDOS_EN_DIA + segundos_totales;
	}
	
	int hora_tot = segundos_totales/3600;
	int min_tot = (segundos_totales%3600)/60;
	int seg_tot = (segundos_totales%3600)%60;

	cout<< " "<< hora_tot << " horas, " << min_tot << " minutos y " << seg_tot;
	cout<< " segundos."; 
	cout<< endl;
	
}

double velocidad (double kilometros, int segundos_totales){
	
	double km_por_hora = (3600*kilometros)/segundos_totales;
	
	return km_por_hora;
}

double ritmo (double kilometros, int segundos_totales){
	
	double min_por_km = segundos_totales/(kilometros*60);
	
	return min_por_km;
}


	
int main(){
	
	double distancia;
	int hora_inicial;
	int min_inicial;
	int seg_inicial;
	
	int numero_dorsal;
	int hora_llegada;
	int min_llegada;
	int seg_llegada;
	
	//entrada de datos 
	
	do{
		cout<< endl;
		cout<< " Introduzca la hora de inicio: " << endl << " Hora: ";
		cin>>hora_inicial;
	}while(hora_inicial<0 || hora_inicial>24);
	
	do{
		cout<< " Minuto: ";
		cin>>min_inicial;
	}while (min_inicial<0 || min_inicial >=60);
	
	do{
		cout<< " Segundo: ";
		cin>> seg_inicial;
	}while(seg_inicial<0 || seg_inicial>=60);
	
	do{
		cout<< " Introduzca una distancia: ";
		cin>>distancia;
	}while(distancia<0);
	
	cout<<endl;
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
	
	//calculos
	
	while(numero_dorsal>=0){
		
		do{
			cout<< endl;
			cout<< " Introduzca la hora de llegada: " << endl << " Hora: ";
			cin>>hora_llegada;
		}while(hora_llegada<0 || hora_llegada>24);
	
		do{
			cout<< " Minuto: ";
			cin>>min_llegada;
		}while (min_llegada<0 || min_llegada >=60);
	
		do{
			cout<< " Segundo: ";
			cin>> seg_llegada;
		}while(seg_llegada<0 || seg_llegada>=60);
	
	int segs_iniciales_total = hora_inicial*3600 + min_inicial*60 + seg_inicial;
	int segs_llegada_total = hora_llegada*3600 + min_llegada*60 + seg_llegada;
	int seg_total = segs_llegada_total - segs_iniciales_total;
		
	cout<<endl;	
	cout<< " - El tiempo que se ha tardado en llegar es: ";
	diferencia_tiempo(seg_total);
	
	cout<< " - Corre a una velocidad de: "<< velocidad(distancia, seg_total);
	cout<<endl;
	cout<< " - Corre con un ritmo de: "<< ritmo(distancia, seg_total);
	cout<< endl<< endl;
	
	//vuelta a introducir datos de entrada
	
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
	}
	
	return 0;
}
