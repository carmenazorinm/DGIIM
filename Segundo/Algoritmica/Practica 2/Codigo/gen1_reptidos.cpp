#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

// generador de ejemplos para el problema del elemento en su posicion. Para rellenar el vector de tamanio n, genera todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; despues obtiene una permutacion aleatoria de ese vector, se queda con los n primeros elementos, y los ordena de forma creciente

double uniforme() //Genera un numero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

//FUERZA BRUTA
double fb (vector <int> v, int in, int f){
    bool encontrado = false;
    int variable;
    for (int i=0; i<=f && !encontrado; i++){

        if (v[i]==i){
            encontrado = true;
            variable = i;
      } 
    }

    if(encontrado)
        return variable;
    else 
        return 0.1;     //valor imposible
    
}



//DIVIDE Y VENCERAS
/*double dyv(vector <int> v, int i, int f){

    if(i>f)return 0.1;  //Si no se encuentra ninguno q coincida

    int m = (i+f)/2;    //Buscamos el medio del vector
    
    if(m < v[m])    //Dividimos el vector
        return dyv(v, i, m-1);  //buscamos recursivamente en la primera parte del vector
    else{
        if(m > v[m])
            return dyv(v, m+1,f); //buscamos recursivamente en la segunda parte del vector
        else
            return m;   //si v[i]=i
    }
    
}*/

/*double dyv(vector <int> v, int i, int f){

    if(i>=f){
        int m= i + (f-i)/2;//punto medio
        if (m==v[m])
            return m;
 
        int result=0.1;

        if ((m+1)<=v[f])
            result=dyv(v, (m+1), f);

        if (result!=0.1)
            return result;

        if (m-1>=v[i])
            return dyv(v,i,(m-1));
    }

    return 0.1;
}*/

int binarySearch(vector<int>arr, int left,
                        int right)
{
    if (right < left)
      return -1;
   int mid = (left + right) / 2;
   int midValue = arr[mid];  
   if (mid == arr[mid])
      return mid;
   int leftindex = min(mid - 1, midValue);
   int l = binarySearch(arr, left, leftindex);
   if (l >= 0)
      return l;
   int rightindex = max(mid + 1, midValue);
   int r = binarySearch(arr, rightindex, right);
   return r;
}

/*int dyv(vector <int> v, int low, int high){
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if (mid == v[mid])
            return mid;
        int res = 0.1;
        if (mid + 1 <= v[high])
            res = dyv(v, (mid + 1), high);
        if (res != 0.1)
            return res;
        if (mid - 1 >= v[low])
            return dyv(v, low, (mid - 1));
    }
 
    return 0.1;

}*/

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

//generamos un vector con enteros [-(n-1), n-1]
  for (int j=0; j<m; j++)
      aux[j] = rand()%(2*(n-1)) - (n-1);
      
//me quedo con los n primeros del vector
for (int j=0; j<n; j++) T[j]=aux[j];
//for (int j=0; j<n; j++) cout << T[j] << " ";
//cout<<endl; 

//Y ahora ordeno el vector T
vector<int> myvector (T, T+n);
vector<int>::iterator it;

sort(myvector.begin(),myvector.end());

 //for (it=myvector.begin(); it!=myvector.end(); ++it)
    //cout << " " << *it;

  //cout << endl;


//Captura el valor del reloj antes de la llamada a dyv
clock_t tantes1=clock();

//Llamamos al algoritmo dyv
double busqueda_dyv=binarySearch(myvector, 0, myvector.size()-1);

//Captura el valor del reloj despues de la ejecucion de dyv
clock_t tdespues1=clock();

cout<< "Algoritmo divide y venceras:"<<endl;
if (busqueda_dyv==0.1) 
    cout<< "No se ha encontrado indice"<<endl; 
else
    cout << "Se ha encontrado coincidencia: "<<endl << "v[" << busqueda_dyv << "]="<< myvector[busqueda_dyv]<<endl;

double tiempo_dyv=(double)(tdespues1 - tantes1) / CLOCKS_PER_SEC;
cout << "" << tiempo_dyv ; 
    

///////////////////////////////////////////////////////////////////////////


//Captura el valor del reloj antes de la llamada de fuerza bruta
clock_t tantes2=clock(); 

//Lo realizamos por fuerza bruta
double busqueda_fb=fb(myvector, 0, myvector.size()-1);

//Captura el valor del reloj despues de la ejecucion de fuerza bruta
clock_t tdespues2=clock();

double tiempo_fb=(double)(tdespues2 - tantes2) / CLOCKS_PER_SEC;
cout << "\t" << tiempo_fb<<endl; 

cout<< "Algoritmo fuerza bruta:"<<endl;

if (busqueda_fb==0.1) 
    cout<< "No se ha encontrado indice"<<endl; 
else
    cout << "Se ha encontrado coincidencia: "<<endl << "v[" << busqueda_fb << "]="<< myvector[busqueda_fb]<<endl;



delete [] aux;

}