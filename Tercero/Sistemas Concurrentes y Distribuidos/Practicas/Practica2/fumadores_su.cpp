#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int
    num_fumadores = 3;

constexpr int
   min_ms    = 5,     // tiempo minimo de espera en sleep_for
   max_ms    = 20 ;   // tiempo máximo de espera en sleep_for


// -----------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)
int producir_ingrediente()
{
  // calcular milisegundos aleatorios de duración de la acción de fumar)
  chrono::milliseconds duracion_produ( aleatorio<10,100>() );

  // informa de que comienza a producir
  cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

  // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
  this_thread::sleep_for( duracion_produ );

  const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

  // informa de que ha terminado de producir
  cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

  return num_ingrediente ;
}

// -----------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra
void fumar( int num_fumador )
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

// -----------------------------------------------------------------------------

class Estanco : public HoareMonitor
{
 private:
 int ingrediente;  // ingrediente que produce el estanquero

 static const int sin_ingrediente = -1; // valor auxiliar para indicar que no hay ningun ingrediente

 CondVar                       // colas condicion:
   cola_fumar[num_fumadores],  // cola para fumar, una para cada fumador
   cola_mostrador;             // cola para el estanquero

 public:                              // constructor y métodos públicos
   Estanco() ;                        // constructor
   void obtenerIngrediente(int i);    // obtiene el ingrediente del fumador i
   void ponerIngrediente(int i);      // coloca el ingrediente del fumador i en el mostrador
   void esperarRecogidaIngrediente(); // retardo de recoger ingrediente
} ;

// -----------------------------------------------------------------------------

Estanco::Estanco(){
    ingrediente = sin_ingrediente;
    cola_mostrador = newCondVar();
    for (int i = 0; i < num_fumadores; i++)
        cola_fumar[i] = newCondVar();
}

// -----------------------------------------------------------------------------

void Estanco::obtenerIngrediente(int i){
    if (i != ingrediente){
        cola_fumar[i].wait();
    }

    cout << "Fumador " << i << " obtiene su ingrediente" << endl;
    ingrediente = sin_ingrediente;
    cola_mostrador.signal();
}

void Estanco::ponerIngrediente(int i){
    ingrediente = i;
    cout << "Estanquero coloca en el mostrador el ingrediente " << i << endl;
    cola_fumar[i].signal();
}

void Estanco::esperarRecogidaIngrediente(){
    cout << "Estanquero espera a que recojan el ingrediente" << endl;
    if (ingrediente != sin_ingrediente)
        cola_mostrador.wait();
}



// -----------------------------------------------------------------------------

void funcion_hebra_fumador (MRef<Estanco> estanco, int num_fumador){
    while (true){
        estanco->obtenerIngrediente(num_fumador);
        fumar(num_fumador);
    }
}

// -----------------------------------------------------------------------------

void funcion_hebra_estanquero (MRef<Estanco> estanco){
    int i;
    while (true){
        int ingrediente = producir_ingrediente();
        estanco->ponerIngrediente(ingrediente);
        estanco->esperarRecogidaIngrediente();
    }
}

// -----------------------------------------------------------------------------

int main()
{
   cout << "----------------------------------------------------------------------" << endl
        << "           Problema de los fumadores múltiples (Monitor SU).          " << endl
        << "----------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Estanco> estanco = Create<Estanco>() ;

   thread hebras_fumadoras[num_fumadores],
          hebra_estanquero;

   // crear y lanzar las hebras
   for (int i = 0; i < num_fumadores; i++)
      hebras_fumadoras[i] = thread(funcion_hebra_fumador, estanco, i);

   hebra_estanquero = thread(funcion_hebra_estanquero, estanco);

   // esperar a que terminen las hebras
   for (int i = 0; i < num_fumadores; i++)
      hebras_fumadoras[i].join();

   hebra_estanquero.join();
}
