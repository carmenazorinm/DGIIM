/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 31: se introduce una cantidad de dinero y una hora inicial y, a
	partir de ahi, se calcula el tiempo que se permite aparparcar en el parking
	con esa cantidad y a qué hora se saldría. 
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	int min_inic;
	int hora_inic;
	double cant_euros;
		
	const double EXMIN_HASTA_30 = 0.0412;
	const double EXMIN_HASTA_90 = 0.037;
	const double EXMIN_HASTA_120 = 0.0311;
	const double EXMIN_HASTA_600 = 0.0305;
	const double EXMIN_HASTA_900 = 0.0270;
	const double A_PARTIR_901 = 35;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca la hora actual: ";
	
	do{
	cout<< " Hora: ";
	cin>> hora_inic;
	}while (hora_inic<0 || hora_inic >24);
	
	do{
	cout<< " Minuto: ";
	cin>> min_inic;
	}while (min_inic<0 || min_inic>=60);
	
	do{
	cout<< " Intruduzca una cantidad de dinero: ";
	cin>> cant_euros;
	}while (cant_euros<0);

	//calculos
	
	int min_total = 0;

	if (cant_euros< A_PARTIR_901){
	
	double cant_que_queda = cant_euros;
	
	while ((cant_que_queda>=EXMIN_HASTA_30)&&(min_total<30)){
		
		cant_que_queda = cant_que_queda - EXMIN_HASTA_30;
		min_total++;
		
	}
	while ((cant_que_queda>=EXMIN_HASTA_90)&&(min_total<90)){
		
		cant_que_queda = cant_que_queda - EXMIN_HASTA_90;
		min_total++;
		
	}
	while ((cant_que_queda>=EXMIN_HASTA_120)&&(min_total<120)){
		
		cant_que_queda = cant_que_queda - EXMIN_HASTA_120;
		min_total++;
		
	}
	while ((cant_que_queda>=EXMIN_HASTA_600)&&(min_total<600)){
		
		cant_que_queda = cant_que_queda - EXMIN_HASTA_600;
		min_total++;
		
	}
	while ((cant_que_queda>=EXMIN_HASTA_900)&&(min_total<900)){
		
		cant_que_queda = cant_que_queda - EXMIN_HASTA_900;
		min_total++;
		
	}
	}
	
	const int MIN_DIA = 24*60;
	
	int min_total_inic = hora_inic*60 + min_inic;
	min_total = min_total + min_total_inic;
	
	bool distinto_dia = min_total>=MIN_DIA;
	if (distinto_dia)
		min_total = min_total - MIN_DIA;
		
	int hora_fin = min_total/60;
	int min_fin = min_total%60;
	
	//Salida
	
	if (cant_euros< A_PARTIR_901){
		if (distinto_dia){
			
			cout<<endl;
			cout<< " Usted puede estar hasta las " << hora_fin << ":";
			cout<< min_fin << " del dia siguiente";
		}else{
			
			cout<<endl;
			cout<< " Usted puede estar hasta las "<< hora_fin << ":"<< min_fin;
		}
	}else{
		
		cout<< endl;
		cout<< " Usted puede estar hasta las " << hora_inic << ":" << min_inic;
		cout<< " del siguiente dia.";
	}
	cout<< endl << endl;
		
	return 0;
}
