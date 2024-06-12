/* FUNDAMENTOS DE LA PROGRAMACIÓN

	Carmen Azorín Martí Grupo 2,2

	Ejercicio 17:Queremos construir un programa que simule un juego inspirado 
	en el de los triles (del que procede el nombre de trilero). Suponemos que 
	hay dos participantes y cada uno tiene una caja etiquetada con su nombre. 
	Dentro de cada caja hay una cantidad de dinero y el objetivo es intercambiar
	las cantidades que hay dentro. Por ahora, sólo se pide construir un programa
	que haga lo siguiente:
		• Debe leer desde teclado dos variables caja_izda y caja_dcha.
		• A continuación debe intercambiar sus valores y finalmente, mostrarlos.
	Observe que se desea intercambiar el contenido de las variables, de forma 
	que caja_izda pasa a contener lo que tenía caja_dcha y viceversa. El 
	siguiente código no es válido ya que simplemente engaña al usuario pero las 
	cajas no se quedan modificadas:
		cout << "La caja izquierda vale " << caja_dcha << "\n";
		cout << "La caja derecha vale " << caja_izda;
	Estaríamos tentados a escribir el siguiente código:
		caja_izda = caja_dcha;
		caja_dcha = caja_izda;
	pero no funciona correctamente ¿Por qué?
	Proponga una solución e impleméntela.
*/

#include<iostream> //inclusion recursos de E/S
#include<cmath> //inclusion recursos matematicos

using namespace std;

int main() //funcion principal
{
	double caja_izda;
	double caja_izda_verdad; //creo la variable que guarda el valor de caja_izda
	
	double caja_dcha;
	
	//entrada de datos
	
	cout<< endl << "Introduzca una cantidad de dinero para la caja izquierda: ";
	cin>> caja_izda;
	cout<< endl << endl;
	
	cout<< "Introduzca una cantidad de dinero para la caja derecha: ";
	cin>> caja_dcha;
	cout<< endl << endl;
	
	//calculos
	
	caja_izda_verdad = caja_izda;
	
	caja_izda = caja_dcha;
	caja_dcha = caja_izda_verdad;
	
	//salida
	
	cout<< "La caja izquierda vale " << caja_izda << endl << endl;
	cout<< "La caja derecha vale " << caja_dcha << endl << endl;
	
	return(0); 
}
