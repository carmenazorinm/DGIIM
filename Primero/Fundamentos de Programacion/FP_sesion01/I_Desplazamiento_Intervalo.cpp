/* FUNDAMENTOS DE LA PROGRAMACION

	Ejercicio 22:  Queremos construir una expresión numérica que desplace un 
	entero un número dado de posiciones, pero lo mantenga dentro de un intervalo
	Por ejemplo, si el intervalo fijado es [65, 90], el desplazamiento es de 3 
	unidades y el entero a desplazar es el 70, el resultado sería 73. Si el 
	entero fuese el 89 y el desplazamiento 3, el resultado sería 92. Al no estar
	el 92 dentro del intervalo, se realiza un ciclo de forma que el 91 se 
	transformaría en el 65 y el 92 en el 66.
	Se pide construir un programa que lea dos enteros minimo y maximo que 
	determinarán el intervalo [minimo, maximo] (supondremos que el usuario 
	introduce como maximo un valor mayor o igual que minimo). A continuación el
	programa leerá un valor entero desplazamiento (supondremos que el usuario 
	introduce un valor entre 0 y maximo - minimo). Finalmente, el programa leerá
	un entero a_desplazar (supondremos que el usuario introduce un número entre 
	minimo y maximo). El programa sumará al valor leido el desplazamiento y lo 
	convertirá en un entero dentro del intervalo [minimo, maximo] tal y como se 
	ha descrito anteriormente.
	
*/

#include <iostream> //inclusion de recursos de E/S
#include <cmath> //inclusion de recursos matematicos

using namespace std;

int main() //funcion principal
{
	int a_desplazar; //creo la variable del numero a desplazar
	int desplazamiento; //creo la variable del desplazamiento deseado
	int minimo; //creo la variable del minimo del intervalo
	int maximo; //creo la variable del maximo del intervalo
	int diferencia; //creo la variable de la diferencia del maximo - minimo
	
	//entrada de datos 
	
	cout<< endl << "Introduzca el entero minimo del intervalo: ";
	cin>> minimo;
	cout<< endl;
	
	cout<< "Introduzca el entero maximo del intervalo: ";
	cin>> maximo;
	cout<< endl;
	
	cout<< "Introduzca el desplazamiento deseado: ";
	cin>> desplazamiento;
	cout<< endl;
	
	cout<< "Introduzca el entero que quiere que sea desplazado: ";
	cin>> a_desplazar;
	cout<< endl << endl;
	
	//calculos
	
	diferencia = maximo - minimo; //calculo la diferencia para posicionar el 
	//intervalo en [0,diferencia]
	
	a_desplazar = a_desplazar + desplazamiento - minimo; //calculo el numero que
	// quiero desplazar + el desplazamiento y le resto el minimo del intervalo 
	//para hacer los calculos con respecto al intervalo [0,diferencia]
	a_desplazar = a_desplazar%(diferencia+1); //divido el numero entre la 
	//diferencia para poder obtener el resto. Le añado al divisor +1, para que 
	//concuerden los restos en la siguiente operacion
	a_desplazar = a_desplazar + minimo; //le sumo el minimo, para volver a 
	//posicionar el numero en el intervalo primitivo [minimo,maximo]
	
	//salida
	
	cout<< "El entero desplazado es " << a_desplazar << endl << endl;
	
	return(0);
}
