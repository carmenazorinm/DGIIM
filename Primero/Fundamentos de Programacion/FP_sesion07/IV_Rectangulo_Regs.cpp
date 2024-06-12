/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Ejercicio 4: el programa leerá las coordenadas de un rectangulo y calculará
	cuál es la mínima circunferencia con área mayor que el área del rectangulo.
*/

#include<iostream> //inclusion de recursos de E/S

using namespace std;

struct Punto{	
	double abscisa;
	double ordenada;
};
struct Rectangulo{
	Punto sup_izq;
	Punto inf_dcha;
};
struct Circunferencia{
	Punto centro;
	double radio;
};

double CalcularAreaRectangulo(Rectangulo rectangulo){

	double base = rectangulo.inf_dcha.abscisa - rectangulo.sup_izq.abscisa;
	double altura = rectangulo.sup_izq.ordenada - rectangulo.inf_dcha.ordenada;	
	double area = base*altura;
	
	return area;
}

double CalcularAreaCircunferencia(Circunferencia circunferencia){
	
	const double PI = 3.14159265359;
	double area = PI*circunferencia.radio*circunferencia.radio;
	
	return area;
}

double CalcularMitad(double x, double y){//calcular el punto que está a mitad 
										 //de dos puntos
	
	double mitad = ((x-y)/2)+y;
	
	return mitad;
}


int main(){
	
	Rectangulo r;
	Circunferencia c;
	
	//entrada de datos
	
	do{
		cout<<endl;
		cout<< " Introduzca la coordenada superior izquierda del rectangulo: ";
		cout<<endl;
		cout<< " Abscisa: ";
		cin>>r.sup_izq.abscisa;
		cout<< " Ordenda: ";
		cin>>r.sup_izq.ordenada;
	
		cout<< " Introduzca la coordenada inferior derecha del rectangulo: ";
		cout<<endl;
		cout<< " Abscisa: ";
		cin>>r.inf_dcha.abscisa;
		cout<< " Ordenda: ";
		cin>>r.inf_dcha.ordenada;
	}while(r.sup_izq.abscisa>=r.inf_dcha.abscisa || 
									r.sup_izq.ordenada<=r.inf_dcha.ordenada);
									
	//calculos
	
	c.centro.abscisa = CalcularMitad(r.inf_dcha.abscisa, r.sup_izq.abscisa);
	c.centro.ordenada = CalcularMitad(r.sup_izq.ordenada, r.inf_dcha.ordenada);
	c.radio = 0.5;
	double area_rectangulo = CalcularAreaRectangulo(r);
	double area_circunferencia = CalcularAreaCircunferencia(c);
	
	while(area_circunferencia<=area_rectangulo){
		
		c.radio += 0.25;
		area_circunferencia = CalcularAreaCircunferencia(c);
	}
	
	//salidas
	
	cout<<endl;
	cout<<" La menor circunferencia con area mayor que el rectangulo tiene:";
	cout<<endl;
	cout<<" Centro en el punto ("<<c.centro.abscisa;
	cout<<","<<c.centro.ordenada<<")";
	cout<<endl;
	cout<<" Area de "<<area_circunferencia<<" uds^2";
	cout<< endl<< endl; 
	
	return 0;
}
