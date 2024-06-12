
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

int producirIngrediente(){
  this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,2000>() ));
  int ingre = aleatorio<0,2>();
  return ingre;
}

void Fumar(int fumador){
  cout << "El fumador " << fumador << " está fumando. " << endl;
  this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,2000>() ));
  cout << "El fumador " << fumador << " ha terminado de fumar. " << endl;
}

class Estanco : public HoareMonitor
{
  private:
    static const int sin_ingrediente = -1;
    int ingrediente_mostrador;
    CondVar cola_fumador[3];
    CondVar esperar_mostrador_vacio;

  public:
    Estanco();
    void obtenerIngrediente(int num_fumador);
    void ponerIngrediente(int ingrediente);
    void esperarRecogidaIngrediente();
};

Estanco::Estanco(){
  ingrediente_mostrador = sin_ingrediente;
  for(int i = 0; i < 3; i++)
      cola_fumador[i] = newCondVar();
  esperar_mostrador_vacio = newCondVar();
}

void Estanco :: obtenerIngrediente(int num_fumador){
  if(num_fumador != ingrediente_mostrador){
    cola_fumador[num_fumador].wait();
  }
  ingrediente_mostrador = sin_ingrediente;
  cout << "El fumador " << num_fumador << " recoge su ingrediente. " << endl;
  esperar_mostrador_vacio.signal();
}

void Estanco :: ponerIngrediente(int ingrediente){
  ingrediente_mostrador = ingrediente;
  cout << "Ingrediente " << ingrediente << " en el mostrador. " << endl;
  cola_fumador[ingrediente].signal();
}

void Estanco :: esperarRecogidaIngrediente(){
  if(ingrediente_mostrador != sin_ingrediente){
    esperar_mostrador_vacio.wait();
  }
}

void funcion_hebra_fumador(MRef<Estanco> monitor, int num_fumador){
  while(true){
    monitor->obtenerIngrediente(num_fumador);
    Fumar(num_fumador);
  }
}

void funcion_hebra_estanquero(MRef<Estanco> monitor){
  int ingrediente;
  while(true){
    ingrediente = producirIngrediente();
    monitor->ponerIngrediente(ingrediente);
    monitor->esperarRecogidaIngrediente();
  }
}

int main(){
   cout << "--------------------------------------------------------------------" << endl
       << "Problema del fumador únicos (Monitor SU, buffer LIFO). " << endl
       << "--------------------------------------------------------------------" << endl
       << flush ;
   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Estanco> monitor = Create<Estanco>() ;

   thread fumadores[3];
   thread estanqueros[1];

   for(int i = 0; i < 3; i++){
     fumadores[i] = thread( funcion_hebra_fumador, monitor, i);
   }

   for(int i = 0; i < 1; i++){
     estanqueros[i] = thread( funcion_hebra_estanquero, monitor);
   }

   for(int i = 0; i < 3; i++){
     fumadores[i].join();
   }

   for(int i = 0; i < 1; i++){
     estanqueros[i].join();
   }
}
