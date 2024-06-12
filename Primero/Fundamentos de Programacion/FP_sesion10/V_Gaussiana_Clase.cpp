/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 7: el programa crea un objeto de la clase Gaussiana y lee su
	esperanza y su desviacion tipica. A partir de ahí, va pintando los valores 
	que se le van dando a la abscisa y a la ordenada desde el valor inicial al 
	valor final con x creciendo cada vez un valor determinado por INCREMENTO. 
	Para ello utiliza el método GaussianaX. Además, pinta su distribucion
	acumulada hasta el valor de x mediante dos métodos CDF1 y CDF2.
*/

#include<iostream>
#include<cmath>

using namespace std;

class Gaussiana{
	//PRE: la desviacion debe ser mayor que 0.
	private:
		double esperanza;
		double desviacion;
			
	public:
		Gaussiana(double valor_esperanza, double valor_desviacion):
			esperanza(valor_esperanza), desviacion(valor_desviacion)
			{}
		
		void ToString(double x){
			
			double y = GaussianaX(x);
			double cdf1 =  CDF1(x);
			double cdf2 = CDF2(x);
		
			cout << endl;
			cout << endl << "(" << x << ", " << y<<")";
			cout << endl << "CDF 1: " << cdf1;
			cout << endl << "CDF 2: " << cdf2;
				
		}
	
	private:
		double GaussianaX(double x){
			const double PI = 6 * asin(0.5);	

			return exp(-0.5 * pow((x - esperanza)/desviacion, 2)) / 
				   (desviacion * sqrt(2*PI));
		}

		double CDF1(double x){
			double const SALTO_INTEGRAL = 0.025;
			const double PI = 6 * asin(0.5);
			double x_cdf = esperanza - 3*desviacion; 
			double cdf;
			double y;
	
			//calcula la integral
			while (x_cdf <= x){
				y = exp (-0.5 * pow ((x_cdf - esperanza)/desviacion, 2)) / 
													(desviacion * sqrt(2*PI));
				cdf = cdf + y;
				x_cdf= x_cdf + SALTO_INTEGRAL;
			}
			cdf = cdf*SALTO_INTEGRAL;
			return cdf;	
		}

		double CDF2(double x){
			const double B0 = 0.2316419;
			const double B1 = 0.319381530;
			const double B2 = -0.356563782;
			const double B3 = 1.781477937;
			const double B4 = -1.821255978;
			const double B5 = 1.330274429;	
	
			double t = 1/(1+B0*fabs(x));
			double g_x = GaussianaX(fabs(x));
			double cdf;
	
			cdf = 1-g_x*(B1*t+B2*pow(t,2)+B3*pow(t,3)+B4*pow(t,4)+B5*pow(t,5));
			if (cdf<0)
				cdf = 1 - cdf;
			return cdf;
		}
};

/*****************************************************************************/
bool ComprobarQueEsReal (string cadena){
	
	int j = 0;
	bool es_real = true;
	
	if(cadena.at(0) == '+' || cadena.at(0) == '-')
		j++;
	
	while(es_real && j<cadena.length()){
		
		char caracter_posicion_j = cadena.at(j);
		es_real = (caracter_posicion_j>='0' && caracter_posicion_j <='9')||
					caracter_posicion_j == '.';
					
		j++;
	}
		
	return es_real; //true si es un positivo y false si no lo es.	
}

double LeeReal (string titulo){
	
	string respuesta;
	bool es_valido;
	
	do{
		cout<< titulo;
		cin>>respuesta;
		es_valido = ComprobarQueEsReal(respuesta);
	}while(!es_valido);
	
	double real = stod(respuesta); //convierte el string respuesta en un int
	return real;
}

/*****************************************************************************/

int main(){
	
	const double PI = 6 * asin(0.5);
	const double INCREMENTO = 0.025;
	double desviacion_tipica;
	double esperanza;
	
	//ENTRADA DE DATOS
	
	do{
		desviacion_tipica = LeeReal(" Desviacion tipica: ");
	} while (desviacion_tipica <= 0);
	esperanza = LeeReal(" Esperanza: ");
	
	//CALCULOS
	
	Gaussiana g(esperanza, desviacion_tipica);
	
	double inicio = esperanza - 3*desviacion_tipica;
	double x = inicio;
	double final = esperanza + 3*desviacion_tipica;
	
	//SALIDA 
	
	//Para cada valor de la x, pinta su distribucion acumulada y su g(x)
	while (x <= final){
		g.ToString(x);	
		x= x+ INCREMENTO; 
	}
	
	return 0;
}



