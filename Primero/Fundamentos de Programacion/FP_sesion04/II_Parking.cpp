/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 16: el programa leerá dos horas diferentes y calculará su 
	diferencia para conseguir el tiempo total dentro del parking. A partir de
	ahi, calculará mediante if y else, el precio total.
	
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	int hora_inicial;
	int minuto_inicial;
	int hora_final;
	int minuto_final;
	double precio;
	
	//entrada de datos
	
	cout<<endl;
	cout<< " Introduzca una hora de entrada: ";
	cin>> hora_inicial;
	
	cout<< " Introduzca un minuto de entrada: ";
	cin>> minuto_inicial;
	
	cout<< " Introduzca una hora de salida: ";
	cin>> hora_final;
	
	cout<< " Introduzca un minuto de salida: ";
	cin>> minuto_final;
	
	//calculos
	
	bool siguiente_dia = (hora_final <= hora_inicial);
	
	if (siguiente_dia){
		
		const int FINAL_DIA = 24;
		hora_final = hora_final + FINAL_DIA;
		
	}
	
	const int PASAR_A_SEGUNDOS = 60;
	int tiempo_en_parking = 
		(hora_final-hora_inicial)*PASAR_A_SEGUNDOS
		+ (minuto_final-minuto_inicial);
		
	//ya se ha calculado el tiempo en el parking, ahora se va a calcular 
	//el precio
		
	const double PRECIO_30 = 0.0412;
	const double PRECIO_90 = 0.037;
	const double PRECIO_120 = 0.0311;
	const double PRECIO_660 = 0.0305;
	const double PRECIO_24H = 24;
	
	const int TREINTA_MIN = 30;
		
	bool mas_30_min = (tiempo_en_parking -TREINTA_MIN) > 0;
	
	if (mas_30_min){ //si se está más de 30 minutos en el parking
		
		tiempo_en_parking = tiempo_en_parking - TREINTA_MIN;
		precio = TREINTA_MIN * PRECIO_30;
		
	const int NOVENTA_MIN = 90 - TREINTA_MIN;	
	bool mas_90_min = (tiempo_en_parking - NOVENTA_MIN) > 0;
	if (mas_90_min){ //si se está más de 90 minutos en el parking
		
		tiempo_en_parking = tiempo_en_parking - NOVENTA_MIN;
		precio = precio + NOVENTA_MIN * PRECIO_90;
		
	const int MIN_120 = 120 -90;
	bool mas_120_min = (tiempo_en_parking - MIN_120) > 0;
	if (mas_120_min){ //si se está más de 120 minutos en el parking
		
		tiempo_en_parking = tiempo_en_parking - MIN_120;
		precio = precio + MIN_120*PRECIO_120;
		
	const int MIN_660 = 660-120;
	bool mas_660_min = (tiempo_en_parking - MIN_660) > 0;
	if (mas_660_min){ //si se está mas de 660 min en el parking
		
		precio = PRECIO_24H;
	}
	else{ //si se está menos de 660 min en el parking
		
		precio = precio + tiempo_en_parking * PRECIO_660;
		//cout<< " Debe pagar " << precio << " euros" << endl << endl;
	}
	}
		
	
	else{ //si se está menos de 120 minutos en el parking
	
		precio = precio + tiempo_en_parking * PRECIO_120;
		//cout<< " Debe pagar " << precio << " euros" << endl << endl;
	}}
	
	else{ // si se está menos de 90 minutos en el parking
		
		precio = precio + tiempo_en_parking * PRECIO_90;
		//cout<< " Debe pagar " << precio << " euros" << endl << endl;
	}
		
	}
	
	else{ //si se está menos de 30 minutos en el parking
		
		precio = tiempo_en_parking * PRECIO_30;
		//cout<< " Debe pagar " << precio << " euros" << endl << endl;
	}
	
	cout<< " Debe pagar " << precio << " euros" << endl << endl;
	
	return 0;
	
}
