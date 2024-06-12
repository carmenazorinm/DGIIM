#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"
#include <chrono>
#include <mutex>

using namespace std ;
using namespace scd ;

constexpr int num_lectores   = 3,  // numero de procesos lectores
              num_escritores = 3;  // numero de procesos escritores

mutex mtx;

// -----------------------------------------------------------------------------

void leer(int numLector){
    chrono::milliseconds duracion_lectura(aleatorio<500,1000>());

    mtx.lock();
    cout << "[Lector " << numLector << "]: Leyendo datos... (" << duracion_lectura.count() << " milisegundos)" << endl;
    mtx.unlock();
    this_thread::sleep_for(duracion_lectura);
}

// -----------------------------------------------------------------------------

void escribir(int numEscritor){
    chrono::milliseconds duracion_escritura(aleatorio<500,1000>());

    mtx.lock();
    cout << "[Escritor " << numEscritor << "]: Escribiendo datos... (" << duracion_escritura.count() << " milisegundos)" << endl;
    mtx.unlock();
    this_thread::sleep_for(duracion_escritura);
}

// -----------------------------------------------------------------------------

void espera(){
    chrono::milliseconds duration(aleatorio<500,1000>());
    this_thread::sleep_for(duration);
}


// -----------------------------------------------------------------------------
// ---------------------- Monitor de Lectura y Escritura -----------------------
// -----------------------------------------------------------------------------

class Lec_Esc : public HoareMonitor{
private:
    int n_lec;         // numero de lectores leyendo
    bool escrib;       // true si hay algun escritor escribiendo, false si no
    CondVar lectura,   // variable condicion que indica cuando se puede leer (cola de lectores)
            escritura; // variable condicion que indica cuando se puede escribir (cola de escritores)

public:
    Lec_Esc();  // constructor
    // precidimientos invocados por los lectores
    void ini_lectura();
    void fin_lectura();
    // procedimientos invocados por los escritores
    void ini_escritura();
    void fin_escritura();
};

// -----------------------------------------------------------------------------

Lec_Esc::Lec_Esc(){
    n_lec = 0;
    escrib = false;
    lectura = newCondVar();
    escritura = newCondVar();
}

// -----------------------------------------------------------------------------

void Lec_Esc::ini_lectura(){
    if (escrib){   // si hay algun proceso escribiendo, se mete en la cola de lectura
        lectura.wait();
    }
    n_lec++;          // aumentamos el contador de procesos leyendo
    lectura.signal(); // desbloquea en cadena los siguientes lectores
}

// -----------------------------------------------------------------------------

void Lec_Esc::fin_lectura(){
    n_lec--;           // disminuye el numero de procesos leyendo
    if (n_lec == 0){   // si ya no hay mas procesos para escribir, se le da paso a los escritores
        escritura.signal();
    }
}

// -----------------------------------------------------------------------------

void Lec_Esc::ini_escritura(){
    if (n_lec > 0 || escrib){ // si hay procesos leyedo, o hay alguno escribiendo,
        escritura.wait();     // se mete en la cola de escribtura
    }
    escrib = true;  // indicamos que hay un proceso escribiendo
}

// -----------------------------------------------------------------------------

void Lec_Esc::fin_escritura(){
    escrib = false; // indicamos que ha terminado de escribir
    if (!lectura.empty()) // si hay algun proceso esperando a leer, se le da paso
        lectura.signal();
    else                  // si no hay ningun proceso esperando a leer, se desbloquea al siguiente escritor
        escritura.signal();
}

// -----------------------------------------------------------------------------
// funcion que ejecutaran las hebras lectoras
void funcion_hebra_lector(MRef<Lec_Esc> monitor, int numLector){
    while (true){
        espera();
        monitor->ini_lectura();
        leer(numLector);
        monitor->fin_lectura();

    }
}

// -----------------------------------------------------------------------------
// funcion que ejecutaran las hebras escritoras
void funcion_hebra_escritora(MRef<Lec_Esc> monitor, int numEscritor){
    while (true){
        espera();
        monitor->ini_escritura();
        escribir(numEscritor);
        monitor->fin_escritura();

    }
}

// -----------------------------------------------------------------------------

int main(){
    cout << "----------------------------------------------------------------------" << endl
         << "------------------- Problema de lectura y escritura ------------------" << endl
         << "----------------------------------------------------------------------" << endl
         << flush ;

    MRef<Lec_Esc> lec_esc = Create<Lec_Esc>();

    thread hebras_lectoras[num_lectores],
           hebras_escritoras[num_escritores];


   for (int i = 0; i < num_escritores; i++)
       hebras_escritoras[i] = thread(funcion_hebra_escritora, lec_esc, i);

    for (int i = 0; i < num_lectores; i++)
        hebras_lectoras[i] = thread(funcion_hebra_lector, lec_esc, i);

    for (int i = 0; i < num_lectores; i++)
        hebras_lectoras[i].join();

    for (int i = 0; i < num_escritores; i++)
        hebras_escritoras[i].join();
}
