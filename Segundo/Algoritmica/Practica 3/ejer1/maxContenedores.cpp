#include<iostream>
#include<algorithm>
#define MAXN 1000005
using namespace std;

// Para compilar: g++ maxContenedores.cpp -o maxContenedores -std=gnu++0x


/*
  Se tiene un buque mercante con capacidad c de carga y un conjunto de n contenedores wi
  con sus pesos respectivos pi. Todos estos datos se le piden al usuario. Este algoritmo
  maximiza el número de contenedores cargados de forma óptima.
*/
int main()
{
    // Declaración de datos
    int w[MAXN];
    int c,n;
    int sum = 0; 
    int tmp = 0;

    // Pedimos los datos de los pesos al usuario
    cout << "Capacidad contenedora: ";
    cin >> c;
    cout << endl << "Numero contenedores: ";
    cin >> n;
    cout << endl;
	 
    for(int i= 1; i <= n; ++i){
        cout << "Peso del contenedor " << i << ": ";
        cin >> w[i];
        cout << endl;
    }
    
    // Ordenamos los pesos de los contenedores de menor a mayor
    sort(w+1,w+1+n);


    // Aplicamos la técnica Greedy
    for(int i = 1; i <= n; ++i){
        tmp += w[i];
        if(tmp <= c)
            ++sum;
        else
            break;
    }


    // Mostramos solucion óptima
    cout << "Numero de contenedores: "<< sum << endl;

    return 0;
}
