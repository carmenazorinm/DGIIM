/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 43: el programa leerá una hora inicial y una distancia. Despues
	preguntara por la hora de llegada de un corredor con dorsal numero_dorsal.
	Para este corredor se calculará el tiempo utilizado en recorrer los km, 
	la velocidad a la que iba y su ritmo. Posteriormente, preguntará por otro
	corredor con dorsal diferente y volverá a dar sus datos. El programa se 
	repetirá hasta que el numero_dorsal<0.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	int num_corredor=0;
	
	double distancia;
	int hora_inicial;
	int min_inicial;
	int seg_inicial;
	
	int numero_dorsal;
	int hora_llegada;
	int min_llegada;
	int seg_llegada;
	
	int hora_final;
	int min_final;
	int seg_final;
	
	int seg_total;
	const int SEGUNDOS_EN_DIA = 3600*24;
	double km_por_hora;
	double min_por_km;
	
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
	
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
	
	//calculos
	
	int segs_iniciales_total = hora_inicial*3600 + min_inicial*60 + seg_inicial;
	
	while(numero_dorsal>=0){
		
		num_corredor++;
		
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
		
	int segs_llegada_total = hora_llegada*3600 + min_llegada*60 + seg_llegada;
	seg_total = segs_llegada_total - segs_iniciales_total;
	
	bool cambio_dia = seg_total<=0;
	if(cambio_dia){
		seg_total = SEGUNDOS_EN_DIA + seg_total;
	}
	
	hora_final = seg_total/3600;
	min_final = (seg_total%3600)/60;
	seg_final = (seg_total%3600)%60;
	
	km_por_hora = (3600*distancia)/seg_total;
	min_por_km = seg_total/(distancia*60);
	
	//salida
	
	cout<<endl;
	cout<< " Los datos del corredor numero " << num_corredor;
	cout<< " con dorsal numero "<< numero_dorsal << " son:"<< endl;
	cout<< " - Tiempo tardado en hacer "<< distancia << " km: ";
	cout<< hora_final << " horas, " << min_final << " minutos y " << seg_final;
	cout<< " segundos." << endl;
	cout<< " - Velocidad de " << km_por_hora << " km/h" << endl;
	cout<< " - Ritmo de " << min_por_km << " min/km"<< endl << endl;
	
	//vuelta a introducir datos de entrada
	
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
		
	}
	
	return 0;
}
