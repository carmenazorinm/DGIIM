/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azor�n Mart� Grupo 2.2. 
	
	Matem�ticas e Ingenier�a Inform�tica
	
	Ejercicio 1: el programa lee enteros y los va guardando en el vector datos.
	Una vez est� el vector completado o se haya introducido un negativo, se 
	dejar�n de leer enteros. Con el vector ya hecho, se modificar� �ste
	para que se quede un vector sin numeros repetidos. Para ello utilizar� 
	una variable posicion_lectura que ir� leyendo todos los numeros anteriores
	a su posicion; y una variable posicion_escritura que se quedar� en una
	posicion fija hasta que se actualice el valor que le corresponde. 
*/

#include<iostream> //inclusion de E/S

using namespace std;

struct Partido
{
	char sigla; //"Nombre" del partido
	long votos; //Votos recibidos;
	int escanios = 0;  //Esca�os obtenidos;
};

int main(){

	int numero_partidos;
	int num_escanios;
	
	//Entradas
	
	do
	{
		cout << "Introduzca el numero de partidos que se presentan: ";
		cin >> numero_partidos;
	} while(numero_partidos <= 0);
	
	const int TOTAL_PARTIDOS = numero_partidos;
	
	Partido partidos[TOTAL_PARTIDOS];
	int contador_escanio[TOTAL_PARTIDOS];
	
	for (int i = 0; i < numero_partidos; i++){
		
		cout << " Informacion del partido: " << i+1 << endl;
		cout << " Sigla: ";
		cin >> partidos[i].sigla;
		partidos[i].sigla = toupper (partidos[i].sigla);
		
		cout << " Votos: ";
		cin >> partidos[i].votos;
	}
	
	do{
		cout << "Introduzca el numero de esca�os a repartir: ";
		cin >> num_escanios;
	} while(num_escanios <= 0);
	
	//Calculos
	
	while (num_escanios > 0){
		
		double mayor_cociente = 0;
		int partido_mayor_cociente;
		
		for (int k = 0; k < TOTAL_PARTIDOS; k++){
			if (partidos[k].votos > mayor_cociente){
				
				mayor_cociente = partidos[k].votos;
				partido_mayor_cociente = k;
			}
		}
		
		partidos[partido_mayor_cociente].escanios++;
		partidos[partido_mayor_cociente].votos 
							/= (partidos[partido_mayor_cociente].escanios + 1);
		
		num_escanios--;
	}
	
	//Salidas
	for (int t = 0; t < numero_partidos; t++)
	{
		cout << " Escanios del partido " << partidos[t]. sigla << ": ";
		cout << partidos[t].escanios;
		cout << endl;
	}
	
	
	return 0;
}
