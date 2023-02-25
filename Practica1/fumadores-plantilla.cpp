#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores

const int num_fumadores = 3 ;

//indica cuántos ingredientes hay listos de cada tipo, al principio ninguno
Semaphore ingrediente_disponible[num_fumadores] = {0, 0, 0};
Semaphore mostr_vacio = 1; //1 true, 0 false

//-------------------------------------------------------------------------
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

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  )
{
  int i;
  while(true){
    i = producir_ingrediente();
    sem_wait(mostr_vacio); //para poner el ingrediente en el mostrador, debe esperar que esté vacío
    cout << "puesto ingrediente " << i << endl;
    // manda una señal de que el ingrediente que estaba produciendo, ya está listo
    sem_signal(ingrediente_disponible[i]);
  }
}

//-------------------------------------------------------------------------
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

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
     //cada fumador espera a que su ingrediente esté listo
     sem_wait(ingrediente_disponible[num_fumador]);
     cout << "El fumador " << num_fumador << " retira su igrediente. " << endl;

     //ya ha recogio el fumado i el ingrediente i, así que ya está vacío el mostrador
     sem_signal( mostr_vacio );
     fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main()
{
   thread fumadores[num_fumadores];
   thread estanquero( funcion_hebra_estanquero);

   for(int i = 0; i < num_fumadores; i++){
     fumadores[i] = thread( funcion_hebra_fumador, i);
   }

   //los join no se utilizan pq son bucles infinitos
   for(int i = 0; i < num_fumadores; i++){
     fumadores[i].join();
   }

   estanquero.join();
}
