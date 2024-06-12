#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//................................................
// VARIABLES GLOBALES
Semaphore gasolina_libre = {3}; //al principio hay 3 de gasolina libres
Semaphore gasoil_libre = {2}; //al principio hay 2 de gasoillibres
int surtidores_en_uso = 0;

//.......................................................
void repostar ( )
{
  cout << "Estoy repostando... " << endl;
  this_thread::sleep_for( chrono::seconds( aleatorio<10,15>() ));
  cout << "Ya puedo conducir!! " << endl;
}

//......................................................
void conducir( )
{
  this_thread::sleep_for( chrono::seconds( aleatorio<10,15>() ));
}

//.......................................................
void funcion_hebra_gasolina( )
{
  while(true){
    sem_wait( gasolina_libre );
    surtidores_en_uso++;
    repostar();
    surtidores_en_uso--;
    sem_signal( gasolina_libre);

    cout << "Me voy a conducir con gasolina :) " << endl;
    conducir();
  }
}

//......................................................
void funcion_hebra_gasoil( )
{
  while(true){
    sem_wait( gasoil_libre );
    surtidores_en_uso++;
    repostar();
    surtidores_en_uso--;
    sem_signal( gasoil_libre);

    cout << "Me voy a conducir con gasoil :) " << endl;
    conducir();
  }
}

//.........................................................
int main(){
  thread hebras_gasoil[4], hebras_gasolina[6];

  for(int i = 0; i < 4; i++)
    hebras_gasoil[i] = thread( funcion_hebra_gasoil );

  for(int i = 0; i < 6; i++)
    hebras_gasolina[i] = thread( funcion_hebra_gasolina );

  for(int i = 0; i < 4; i++)
    hebras_gasoil[i].join();

  for(int i = 0; i < 6; i++)
    hebras_gasolina[i].join();
}
