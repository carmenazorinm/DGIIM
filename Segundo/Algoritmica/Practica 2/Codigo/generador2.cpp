#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include<bits/stdc++.h>
//#include <algorithm>
//#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

int* fuerza_bruta (int num_elem, int num_vect, int **matriz){
    
    //Vector final ordenado con el resultado de mezclar todos los vectores
    int* vect_final; //Inicializamos
    vect_final = new int [num_elem*num_vect];
    
    bool encontrado;
    int k;

    for (int i=0; i<num_elem; i++){
        vect_final[i]=matriz[0][i]; 
    }

    for (int i =1; i<num_vect; i++){
        for (int j=0; j<num_elem; j++){
           encontrado=false;
           k=0;
           while (!encontrado && k<num_elem*i+j){
                if (vect_final [k]> matriz[i][j])
                    encontrado=true; 
                else
                    k++;
            }
                
            if (encontrado){
                for (int p=num_elem*i+j-1; p>=k; p--){
                    vect_final[p+1]= vect_final[p];
                }
                vect_final[k]=matriz[i][j];
            }
            else {  // !encontrado
                vect_final[num_elem*i+j]=matriz[i][j];
            }
        }
    }
    return vect_final; 
}

void mezclar(int l, int r, int n, vector<int>& salida)
{
    // almacena el inicio de los dos vectores 
    int inic_i = l * n;
    int inic_d = ((l + r) / 2 + 1) * n;
 
    // almacena el tamaño de los dos vectores 
    int tam_i = ((l + r) / 2 - l + 1) * n;
    int tam_d = (r - (l + r) / 2) * n;
 
    // vectores temporales
    int vector_i[tam_i], vector_d[tam_d];
 
    // guardando los datos en el primer vector
    for (int i = 0; i < tam_i; i++)
        vector_i[i] = salida[inic_i + i];
 
    // guardando los datos en el segundo vector
    for (int i = 0; i < tam_d; i++)
        vector_d[i] = salida[inic_d + i];
 
    // contadores de los vectores
    int cont_i = 0, cont_d = 0;
 
    // cotador del vector salida
    int in = inic_i;
 
    // mezclar los dos vectores
    while (cont_i + cont_d < tam_i + tam_d) 
    {
        if ( cont_d == tam_d || (cont_i != tam_i && 
            vector_i[cont_i] < vector_d[cont_d]))
        {
            salida[in] = vector_i[cont_i];
            cont_i++;
            in++;
        }
        else{
            salida[in] = vector_d[cont_d];
            cont_d++;
            in++;
        }
    }
}

void divide(int l, int r, int n, vector<int>& salida,
            int** arr)
{
    if (l == r) {
        // inicializar el vector salida
        for (int i = 0; i < n; i++)
            salida[l * n + i] = arr[l][i];
    }
    else{
        // ordena la mitad izquierda
        divide(l, (l + r) / 2, n, salida, arr);
    
        // ordena la mitad derecha
        divide((l + r) / 2 + 1, r, n, salida, arr);
    
        // mezclar las dos mitades
        mezclar(l, r, n, salida);
    }
}

int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


int **T;
T =  new int * [k];
  assert(T);

 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
  assert(aux);

srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;

//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
for (int i=0; i<k; i++) {
   int t=0;
   int m=0;
   while (m<n) {
    double u=uniforme();
    if ((N-t)*u >= (n-m)) t++;
    else {
        T[i][m]=aux[t];
	t++;
	m++;
    }
  }
}

delete [] aux;

//Mostrar la matriz
// for (int i=0; i<k; i++) {
//  for (int j=0; j<n; j++)
//    cout << T[i][j] << " ";
//  cout << " " << endl;
// }

//Hasta aquí es lo que nos da la profesora
//Ahora ya se ha generado la matriz T con k vectores de n elementos

//DIVIDE Y VENCERAS
vector<int> salida(N);
double t_ejecucion = 0, t_transcurrido = 0;
clock_t tantes, tdespues;
tantes = clock();
divide(0, k - 1, n, salida, T);
tdespues = clock();
t_transcurrido = (double)(tdespues-tantes);

t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);

// for (int i = 0; i < n * k; i++)
//         cout << salida[i] << " ";
// cout << endl;

cout << k << "\t" << n << "\t" << t_ejecucion;

//FUERZA BRUTA
int* vect_final;
t_ejecucion = 0, t_transcurrido = 0;

tantes = clock();
vect_final = fuerza_bruta(n,k,T);
tdespues = clock();
t_transcurrido = (double)(tdespues-tantes);

t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);

// for (int i = 0; i < n * k; i++)
//         cout << vect_final[i] << " ";
// cout << endl;

cout << "\t" << t_ejecucion <<endl;

return 0;
}