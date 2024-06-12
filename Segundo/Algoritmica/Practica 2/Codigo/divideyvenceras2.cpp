#include <iostream>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdlib>
using namespace std;

//DECLARACIÓN DE FUNCIONES
void reservarVector(int tam, int * & v);
void reservarMatriz(int nFilas, int nColumnas, int ** & m);
void generarVector(int tam, int * v);
void mostrarMatriz(int nFilas, int nColumnas, int ** m);
void mostrarVector(int tam, int * v);
void liberarVector(int * & v);
void liberarMatriz(int nFilas, int nColumnas, int ** & m);
double uniforme();
void mezcla_DYV(int numVectores, int numElementos, int ** m, int * &mezcla);
void mezcla_DYV_recursivo(int vec_inicial, int vec_final, int numElementos, int ** m, int
* &mezcla);
void mezclaVectores(int * vec1, int * vec2, int dim1, int dim2, int * &mezcla);

//IMPLEMENTACIÓN DE FUNCIONES
int * fuerza_bruta (int num_elem, int num_vect, int **matriz){
    
    //Vector final ordenado con el resultado de mezclar todos los vectores
    int * vect_final=nullptr; //Inicializamos
    reservarVector(num_elem * num_vect, vect_final); //el vector final tiene dimension nk elementos

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

void mezcla_DYV(int numVectores, int numElementos, int ** m, int * &mezcla){
    mezcla_DYV_recursivo(0,numVectores-1,numElementos,m,mezcla);
}

void mezcla_DYV_recursivo(int vec_inicial, int vec_final, int numElementos, int ** m, int
* &mezcla){
    //PASO1: COMPROBAMOS QUE SIEMPRE VEC_FINAL > VEC_INICIAL
    if(vec_inicial < vec_final){
        //PASO2: OBTENEMOS EL NUMERO DE VECTORES QUE TENEMOS, ASI COMO EL VECTOR MEDIO
        int numVectores = vec_final-vec_inicial+1;
        int vec_medio = (vec_final+vec_inicial)/2;
        //OBTENEMOS DIMENSION PARA VECTORES AUXILIARES DE MEZCLA
        int dim2 = numVectores/2;
        int dim1 = numVectores - dim2;
        //PASO3: DECLARAMOS VECTORES AUXILIARES DONDE GUARDAREMOS RESULTADOS PREVIOS
        int * mezcla1 = nullptr; int * mezcla2 = nullptr;
        reservarVector(numElementos*(dim1),mezcla1);
        reservarVector(numElementos*(dim2),mezcla2);
        //LLAMADA RECURSIVA A FUNCION: CALCULA LA MEZCLA PARA K/2 VECTORES (DESDE 0 HASTA VEC_MEDIO)
        mezcla_DYV_recursivo(vec_inicial,vec_medio,numElementos,m,mezcla1);
        //LLAMADA RECURSIVA A FUNCION: CALCULA LA MEZCLA PARA K/2 VECTORES (DESDE VEC_MEDIO HASTA VEC_FINAL)
        mezcla_DYV_recursivo(vec_medio+1,vec_final,numElementos,m,mezcla2);
        //PASO 4: MEZCLAMOS LOS VECTORES OBTENIDOS ANTERIORMENTE
        mezclaVectores(mezcla1,mezcla2,dim1*numElementos,(dim2)*numElementos,mezcla);
        //PASO 5: LIBERAMOS MEMORIA
        liberarVector(mezcla1);
        liberarVector(mezcla2);
    }
    //EN CASO CONTRARIO AL PASO1: CASO BASE (SOLO MEZCLAMOS 1 VECTOR)
    else{
        for(int i=0; i<numElementos;i++)
            mezcla[i] = m[vec_inicial][i];
    }
}


void mezclaVectores(int * vec1, int * vec2, int dim1, int dim2, int * &mezcla){
    for(int i=0; i<dim1; i++)
        mezcla[i] = vec1[i];

    bool found;
    int k;

    for(int j=0; j<dim2; j++){
        k=0; found = false;
        while(!found && k<(dim1+dim2)){
            if(mezcla[k] >= vec2[j])
                found = true;
            else
            k++;
        }
        if(found){
            for(int p = dim1+j-1; p >= k; p--){
                mezcla[p+1] = mezcla[p];
            }
            mezcla[k] = vec2[j];
        }
        if(!found){
            mezcla[dim1+j] = vec2[j];
        }
    }
}

int main(int narg, char * argv[]){
    //PASO 0: DECLARACION DE VARIABLES NECESARIAS
    int ** M = nullptr; //MATRIZ DE ALMACENAMIENTO DE VECTORES
    //int * fusion = nullptr; //VECTOR DE ALMACENAMIENTO DE MEZCLA VECTORES
    //PASO 1: CHECK ARGUMENTOS
    if(narg != 3){
        cerr << "ERROR [0] AL EJECUTAR PROGRAMA. NUMERO DE ARGUMENTOS INSUFICIENTE..." << endl;
        exit(EXIT_FAILURE);
    }

    //PASO 2: OBTENCION DE ARGUMENTOS
    int numElem = atoi(argv[1]);
    int numVec = atoi(argv[2]);
    int kn = numElem*numVec;

    //PASO 3: RESERVA DE MEMORIA
    reservarMatriz(numVec,numElem,M);
    //reservarVector(kn,fusion);
    //PASO 4: GENERAR VECTORES ALEATORIOS
    int * aux = nullptr;
    reservarVector(kn,aux);
    generarVector(kn,aux);

    //cout << "Ejecutando el programa con divide y vencerás" << endl;
    //samplingKnuth
    srand(time(0));
    for(int i=0; i<numVec; i++){
        int t=0;
        int m=0;
        while(m<numElem){
            double u = uniforme();
            if((kn-t)*u >= (numElem - m)) 
                t++;
            else{
                M[i][m] = aux[t];
                t++;
                m++;
            }
        }
    }

    //mostrarMatriz(numVec,numElem,M);
    //PASO 5: REALIZAR TEST
    int *mezcla=nullptr;
    reservarVector(numVec*numElem,mezcla);
    double t_ejecucion = 0, t_transcurrido = 0;
    clock_t tantes, tdespues;

    tantes = clock();
    mezcla_DYV(numVec,numElem,M,mezcla);
    tdespues = clock();
    t_transcurrido = (double)(tdespues-tantes);

    t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);
    //mostrarVector(numVec*numElem,mezcla);
    liberarVector(mezcla);
    liberarVector(aux);
    liberarMatriz(numVec,numElem,M);
    //PASO 8: MOSTRAR RESULTADOS
    cout << numVec << "\t" << numElem << "\t" << t_ejecucion;

    //Ejecutamos con fuerza bruta
    //cout << endl;
    //cout << "Ejecutando el programa con fuerza bruta" << endl;
    
    int **T=nullptr;
    int *vect_final=nullptr;
    reservarMatriz(numVec,numElem,T);
    int * aux2 = nullptr;
    reservarVector(kn,aux2);
    generarVector(kn,aux2);

    srand(time(0));
    for (int i=0; i<numVec; i++) {
        int t=0;
        int m=0;
        while (m<numElem) {
            double u=uniforme();
            if ((kn-t)*u >= (numElem-m)) t++;
            else {
                T[i][m]=aux2[t];
                t++;
                m++;
            }
        }
    }

    //mostrarMatriz(numVec,numElem,T);
    reservarVector(numVec*numElem,vect_final);
    t_ejecucion = 0, t_transcurrido = 0;

    tantes = clock();
    vect_final = fuerza_bruta(numElem,numVec,T);
    tdespues = clock();
    t_transcurrido = (double)(tdespues-tantes);

    t_ejecucion = t_transcurrido / (CLOCKS_PER_SEC);
    //mostrarVector(numVec*numElem,vect_final);

    liberarVector(vect_final);
    liberarVector(aux2);
    liberarMatriz(numVec,numElem,T);
    //PASO 8: MOSTRAR RESULTADOS
    cout << "\t" << t_ejecucion << endl;


    return 0;
}


void reservarVector(int tam, int * & v){
    //COMPROBAMOS QUE TAM ES POSITIVO
    if(tam < 1){
        cerr << "ERROR [P3.1] AT reservarVector(). TAM NO ES UN ENTERO POSITIVO. EXITING..." << endl;
        exit(EXIT_FAILURE);
    }

    //COMPROBAMOS QUE v ESTA A nullptr
    if(v != nullptr){
        liberarVector(v);
    }

    //INICIALIZAMOS VECTOR
    v = new int [tam];

    //COMPROBAMOS QUE NO HA HABIDO ERRORES
    if(v == nullptr){
        cerr << "ERROR [P3.2] AT reservarVector(). NO SE HA PODIDO RESERVAR MEMORIA PARA DIMENSION [" << tam << "] EXITING..." << endl;
        exit(EXIT_FAILURE);
    }

    //INICIALIZAR VECTORES
    for(int i=0;i<tam;i++)
        v[i] = 0;
}

void reservarMatriz(int nFilas, int nColumnas, int ** &m){
    //COMPROBAMOS QUE NFILAS y NCOLUMNAS SON POSITIVOS
    if(nFilas < 1 || nColumnas < 1){
        cerr << "ERROR [P3.1] AT reservarMatriz(). NFILAS O NCOLUMNAS NO ES UN ENTERO POSITIVO. EXITING..." << endl;
        exit(EXIT_FAILURE);
    }
    
    //COMPROBAMOS QUE m ESTA A nullptr
    if(m != nullptr){
        liberarMatriz(nFilas,nColumnas,m);
    }

    //INICIALIZAMOS VECTOR DE PUNTEROS
    m = new int * [nFilas];

    //COMPROBAMOS QUE NO HA HABIDO ERRORES
    if(m == nullptr){
        cerr << "ERROR [P3.2] AT reservarMatriz(). NO SE HA PODIDO RESERVAR MEMORIA PARA DIMENSION [" << nFilas << "x" << nColumnas << "] EXITING..." << endl;
        exit(EXIT_FAILURE);
    }

    //RELLENAMOS EL VECTOR DE PUNTEROS
    for(int i=0; i<nFilas; i++){
        m[i] = new int [nColumnas];

        //COMPROBACION DE ERRORES
        if(m[i] == nullptr){
            cerr << "ERROR [P3.3] AT reservarMatriz(). NO SE HA PODIDO RESERVAR MEMORIA PARA COMPONENTE [" << i << "] EXITING..." << endl;
            for(int j=0; j<i; j++)
                delete [] m[j];
            delete [] m;
            m = nullptr;
            exit(EXIT_FAILURE);
        }
    }
}


void generarVector(int tam, int * v){
    //COMPROBACION DE DIMENSION CORRECTA
    if(tam < 1){
        cerr << "ERROR [P4.1] AT generarVector(). TAM NO ES UN NUMERO ESTRICTAMENTE POSITIVO. EXITING..." << endl;
        exit(EXIT_FAILURE);
    }

    //COMPROBACION DE MATRIZ NO NULA
    if(v == nullptr){
        cerr << "ERROR [P4.2] AT generarVector(). VECTOR INTRODUCIDO NO VALIDA. EXITING..." << endl;
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<tam;i++)
        v[i] = i;
}


void mostrarMatriz(int nFilas, int nColumnas, int ** m){
    for(int i=0; i<nFilas; i++){
        for(int j=0; j<nColumnas; j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}


void mostrarVector(int tam, int * v){
    for(int i=0; i<tam; i++)
        cout << v[i] << " ";
    cout << endl;
}


void liberarMatriz(int nFilas, int nColumnas, int ** & m){
    //COMPROBAMOS VALOR DIMENSION
    if(nFilas < 1 || nColumnas < 1){
        cerr << "ERROR [P6.1] AT liberarMatriz(). NFILAS O NCOLUMNAS NO ES UN ENTERO POSITIVO. EXITING..." << endl;
        exit(EXIT_FAILURE);
    }
    //LIBERAMOS MEMORIA SI MATRIZ NO ES nullptr
    if(m != nullptr){
        for(int i=0; i<nFilas; i++)
            delete [] m[i];
        delete [] m;
        m = nullptr;
    }
}


void liberarVector(int * & v){
    //LIBERAMOS MEMORIA SI NO ES nullptr
    if(v != nullptr){
        delete [] v;
        v = nullptr;
    }
}


double uniforme(){
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

