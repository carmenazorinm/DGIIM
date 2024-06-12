#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

// generador de ejemplos para el problema del elemento en su posici�n. Para rellenar el vector de tama�o n, genera todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; despu�s obtiene una permutaci�n aleatoria de ese vector, se queda con los n primeros elementos, y los ordena de forma creciente

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

double dyv(vector<int> v, int i, int j){

    if(i>j)return 0.1;  //Si no se encuentra ninguno q coincida

    int m = (i+j)/2;    //Buscamos el medio del vector
    
    if(m < v[m])    //Dividimos el vector
        return dyv(v, i, m-1);  //buscamos recursivamente en la primera parte del vector
    else{
        if(m > v[m])
            return dyv(v, m+1, j); //buscamos recursivamente en la segunda parte del vector
        else
            return m;   //si v[i]=i
    }
}

int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int m=2*n-1;

  int * T = new int[n];
  assert(T);
int * aux = new int[m];
  assert(aux);

srand(time(0));
//genero todos los enteros entre -(n-1) y n-1
for (int j=0; j<m; j++) aux[j]=j-(n-1);

//algoritmo de random shuffling the Knuth (permutacion aleatoria) 
for (int j=m-1; j>0; j--) {
   double u=uniforme();
   int k=(int)(j*u);
   int tmp=aux[j];
   aux[j]=aux[k];
   aux[k]=tmp;
}
//me quedo con los n primeros del vector
for (int j=0; j<n; j++) T[j]=aux[j];
for (int j=0; j<n; j++) cout << T[j] << " ";
cout<<endl; 

//Y ahora ordeno el vector T
vector<int> myvector (T, T+n);
vector<int>::iterator it;

sort(myvector.begin(),myvector.end());

 for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

//divide y vencerás

double busqueda = dyv(myvector, 0, myvector.size()-1);
if(busqueda != 0.1)
  cout << "Indice encontrado: " << endl << "v[" << busqueda << "]="<< myvector[busqueda]<<endl;
else 
  cout<< "No se ha encontrado"<<endl; 

delete [] aux;
}