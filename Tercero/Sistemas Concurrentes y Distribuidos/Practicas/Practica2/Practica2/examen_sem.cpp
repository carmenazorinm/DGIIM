#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//Variables Globales
const int n_jugadores = 3;
int campo[n_jugadores][n_jugadores] = {-1};
int n_vidas[n_jugadores] = {3};
Semaphore comprobar_movimiento = 1;
Semaphore mostrar_campo = 1;

void mostrar_campo_pantalla(){
  for(int i = 0; i < n_jugadores; i++){
    cout << endl;
    for(int j = 0; j < n_jugadores; j++){
      cout << "[\t" << campo[i][j] << "\t]";
    }
  }

  cout << endl << endl;
}

void elimina_casilla(int k)
{
  for(int i = 0; i < n_jugadores; i++){
    for(int j = 0; j < n_jugadores; j++){
      if(campo[i][j] = k)
        campo[i][j] = -1;
    }
  }
}


void funcion_enemigo()
{
 this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,3000>() ));

}

void funcion_jugador(int n_hebra)
{
  int fila;
  int columna;
  do{
    columna = aleatorio<0,2>();
    fila = aleatorio<0,2>();
  comprobar_movimiento.sem_wait();
  }while(campo[fila][columna] > -1);
  comprobar_movimiento.sem_signal();

  this_thread::sleep_for( chrono::milliseconds( aleatorio<100,3000>() ));

  mostrar_campo.sem_wait();

  elimina_casilla(n_hebra);
  campo[fila][columna] = n_hebra;
  mostrar_campo_pantalla();

  mostrar_campo.sem_signal();


}


int main()
{
  //MRef<Campo> monitor = Create<Campo>();

  for(int i = 0; i < n_jugadores; i++){
    for(int j = 0; j < n_jugadores; j++){
      campo[i][j] = -1;
    }
    campo[i][i] = i;
  }

  thread jugador[n_jugadores];
  for(int i = 0; i < n_jugadores;i++){
    jugador[i] = thread(funcion_jugador, i);
  }
  thread enemigo(funcion_enemigo);
  enemigo.join();
  for(int i = 0; i < n_jugadores;i++){
    jugador[i].join();
  }

}
