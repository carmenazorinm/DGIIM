/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 6: el programa lee la hora de inicio de una carrera y la distancia
	hasta la meta. Posteriormente, va a ir leyendo numeros de dorsales y las
	horas de llegada de cada uno de esos dorsales, y va a calcular el tiempo
	empleado, la velocidad y el ritmo de cada correor. Así lo hará hasta que 
	se introduzca un numero negativo en el dorsal.
*/

#include<iostream> //inclusion de recursos de E/S
#include<cmath> //inclusion de recursos matematicos (en este programa, fabs)

using namespace std;

struct Hora{
	int hora;
	int min;
	int seg;
};

int segundos_en_total (Hora hora1, Hora hora2){ 

//calcula los segundos totales de un hora y los resta a los segundos totales de
//otra hora. Si las horas son de dias diferentes, entonces el resultado será
//un numero negativo
	
	int segs_hora1 = hora1.hora*3600 + hora1.min*60 + hora1.seg;
	int segs_hora2 = hora2.hora*3600 + hora2.min*60 + hora2.seg;
	int seg_total = segs_hora2 - segs_hora1;
	
	return seg_total;
}
/*****************************************************************************/

int diferencia_tiempo (int segundos_totales){
	
	const int SEGUNDOS_EN_DIA = 3600*24;
	
//si los segundos totales calculados en la funcion segundos_en_total es un 
//numero negativo, significaría que se ha cambiado de día.

	if(segundos_totales<=0){
		segundos_totales = SEGUNDOS_EN_DIA + segundos_totales;
	}

//una vez ya tenemos los segundos totales reales, damos el resultado en horas, 
//minutos y segundos
	
	int hora_tot = segundos_totales/3600;
	int min_tot = (segundos_totales%3600)/60;
	int seg_tot = (segundos_totales%3600)%60;

	cout<< " "<< hora_tot << " horas, " << min_tot << " minutos y " << seg_tot;
	cout<< " segundos."; 
	cout<< endl;
	
	return segundos_totales; //devolvemos los segundos totales reales que se ha 
							//tardado en llegar a la meta. Ya no puede ser un
							//numero negativo.
}

/******************************************************************************/

double velocidad (double kilometros, int segundos_totales){
	
	double km_por_hora = (3600*kilometros)/segundos_totales;
	
	return km_por_hora;
}

double ritmo (double kilometros, int segundos_totales){
	
	double min_por_km = segundos_totales/(kilometros*60);
	
	return min_por_km;
}

/*****************************************************************************/
	
int main(){
	
	double distancia;
	int numero_dorsal;
	Hora hora_inicio, hora_llegada;
	
	//entrada de datos 
	
	do{
		cout<< endl;
		cout<< " Introduzca la hora de inicio: " << endl << " Hora: ";
		cin>>hora_inicio.hora;
	}while(hora_inicio.hora<0 || hora_inicio.hora>24);
	
	do{
		cout<< " Minuto: ";
		cin>>hora_inicio.min;
	}while (hora_inicio.min<0 || hora_inicio.min >=60);
	
	do{
		cout<< " Segundo: ";
		cin>> hora_inicio.seg;
	}while(hora_inicio.seg<0 || hora_inicio.seg>=60);
	
	do{
		cout<< " Introduzca una distancia: ";
		cin>>distancia;
	}while(distancia<=0);
	
	cout<<endl;
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
	
	//calculos
	
	while(numero_dorsal>=0){
		
		do{
			cout<< " Introduzca la hora de llegada: " << endl << " Hora: ";
			cin>>hora_llegada.hora;
		}while(hora_llegada.hora<0 || hora_llegada.hora>24);
	
		do{
			cout<< " Minuto: ";
			cin>>hora_llegada.min;
		}while (hora_llegada.min<0 || hora_llegada.min >=60);
	
		do{
			cout<< " Segundo: ";
			cin>> hora_llegada.seg;
		}while(hora_llegada.seg<0 || hora_llegada.seg>=60);
	
	int seg_en_total = segundos_en_total (hora_inicio, hora_llegada);//puede dar
																	//negativo
																	
	//salida
			
	cout<<endl;	
	cout<< " - El tiempo que se ha tardado en llegar es: ";
	
	seg_en_total= diferencia_tiempo(seg_en_total); //segundos totales reales
	
	cout<< " - Corre a una velocidad de: "<< velocidad(distancia, seg_en_total);
	cout<< " km/hora";
	cout<<endl;
	cout<< " - Corre con un ritmo de: "<< ritmo(distancia, seg_en_total);
	cout<<" min/km";
	cout<< endl<< endl;
	
	//vuelta a introducir datos de entrada
	
	cout<< " Introduzca un numero de dorsal: ";
	cin>>numero_dorsal;
	}
	
	return 0;
}
