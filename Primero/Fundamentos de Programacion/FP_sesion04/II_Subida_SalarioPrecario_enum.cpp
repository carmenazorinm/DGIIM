/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 20: el prgrama leerá una edad y un salario y a partir de ahi 
	devolvera un nuevo salario con las subidas correspondientes.
	
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

int main(){
	
	int edad_persona;
	double salario;
	double salario_final;
	
	//entrada de datos
	
	cout<< endl;
	cout<< " Introduzca su edad: ";
	cin>> edad_persona;
	
	cout<< " Introduzca su salario mensual: ";
	cin>> salario;
	cout<< endl << endl;
	
	//calculos
	
	if (edad_persona<0){
		
		cout<< " El valor de la edad es incorrecto";
	}
	else{
	
	//segun la edad
	
	enum class EdadRango {dentro_rango, fuera_rango};
	
	EdadRango edad;
	
	const int EDAD_MINIMA = 35;
	const int EDAD_MAXIMA = 65;
	bool primer_requisito = (edad_persona<EDAD_MINIMA) || 
						(edad_persona>EDAD_MAXIMA);
	
	if (primer_requisito){
		
		edad = EdadRango::dentro_rango;
		
		const double SUBIDA_4PORCIENTO = 1.4;
		salario_final = salario*SUBIDA_4PORCIENTO;
	}
	
	else{
		
		edad = EdadRango::fuera_rango;
		
		salario_final = salario;
	}
	
	//segun el salario
	
	enum class TipoSalario {muy_bajo, bajo, normal};
	
	TipoSalario tipo_de_salario;
	
	const int SALARIO_MUY_BAJO = 300;	
	bool segundo_requisito = salario<SALARIO_MUY_BAJO;
	if (segundo_requisito){
		
		tipo_de_salario = TipoSalario::muy_bajo;
		
		const double SUBIDA_3PORCIENTO = 1.3;
		salario_final = salario_final*SUBIDA_3PORCIENTO;
	}

	const int SALARIO_BAJO = 900;
	bool tercer_requisito = (salario<SALARIO_BAJO)&&
							(salario>=SALARIO_MUY_BAJO);
	if (tercer_requisito){
			
		tipo_de_salario = TipoSalario::bajo;
			
		const double SUBIDA_15PORCIENTO = 1.15;
		salario_final = salario_final*SUBIDA_15PORCIENTO;
	}
	
	bool gran_salario = (salario>=SALARIO_BAJO);
	if (gran_salario){
		
		tipo_de_salario = TipoSalario::normal;
	}
	
	switch (edad){
		
		case(EdadRango::fuera_rango):
			cout<< " No se aplica ninguna subida de salario.";
			break;
		
		case(EdadRango::dentro_rango):
			cout<< " Se le aplica una subida del 4% a su salario."<< endl;
			
			switch (tipo_de_salario){
				
				case (TipoSalario::muy_bajo):
					cout<< " Se le aplica una subida del 3% adicional"<< endl;
					cout<< " Su salario final es de "<< salario_final;
					cout<< " euros";
					break;
				
				case (TipoSalario::bajo):
					cout<< " Se le aplica una subida del 1.5% adicional"<<endl;
					cout<< " Su salario final es de "<< salario_final;
					cout<< " euros";
					break;
				
				case (TipoSalario::normal):
					cout<< " No se le aplican más subidas"<< endl;
					cout<< " Su salario final es de "<< salario_final;
					cout<< " euros";
					break;
			}
			
			break;		
	}
	}
	cout<< endl << endl;
	
	return 0;
}
