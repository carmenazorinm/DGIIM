
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

const int n_jugadores = 4; //minimo 2
int galletas[n_jugadores] = {0,0,0,0};
bool bloqueados[n_jugadores] = {false, false, false, false};
int n_bloqueadas = 0;

int rellerna_plato = 3;


class Plato : public HoareMonitor
{
private:
  int tablero[n_jugadores][n_jugadores];
  CondVar bloqueado;

public:
  Plato();
  bool CogeGalleta(int i, int x, int y);
  void mostrar_plato();
  void actuaBloqueado(int n);
  bool comprobar_terminado();
  void pon_galletas();
};

Plato::Plato()
{
  for(int i = 0; i < n_jugadores; i++){
    for(int j = 0; j < n_jugadores; j++){
      tablero[i][j] = aleatorio<0,2>();
    }
  }

  bloqueado = newCondVar();
}

bool Plato::comprobar_terminado()
{
  bool terminado;
  if(rellerna_plato == 0){
    for(int i = 0; i < n_jugadores; i++){
      for(int j = 0; j < n_jugadores; j++){
        if(tablero[i][j] > 0){
          return false;
        }
      }
    }
  }else{
    return false;
  }

  return true;
}

void Plato::mostrar_plato(){
  for(int i = 0; i < n_jugadores; i++){
    cout << endl;
    for(int j = 0; j < n_jugadores; j++){
      cout << "[\t" << tablero[i][j] << "\t]";
    }
  }

  cout << endl << endl;
}

bool Plato::CogeGalleta(int n_hebra, int fila, int col)
{
  cout << "Jugador " << n_hebra << " intenta coger galleta [" << fila << ", " << col << "]" << endl;
  if(tablero[fila][col] > 0 & !bloqueados[n_hebra])
  {
    cout << "Jugador " << n_hebra << " consigue coger galleta [" << fila << ", " << col << "]" << endl;
    tablero[fila][col]--;
    galletas[n_hebra]++;
    mostrar_plato();
    return true;
  }
  else
  {
    bloqueados[n_hebra] = true;
    n_bloqueadas++;
    mostrar_plato();
    return false;
  }
}

void Plato::actuaBloqueado(int n)
{
  if(n_bloqueadas == n_jugadores)
  {
    cout << "Jugador " <<  n << " libera al resto de jugadores" << endl;
    for(int i = 0; i < n_jugadores-1; i++){
      bloqueado.signal();
    }
    for(int i = 0; i < n_jugadores; i++){
      bloqueados[i] = false;
    }
    n_bloqueadas = 0;
  }
  else
  {
    cout << "Jugador " << n << " se bloquea" << endl;
    bloqueado.wait();
  }
}

void Plato::pon_galletas()
{
  cout << "EL COCINERO AÑADE GALLETAS " << endl;
  int num_nuevas_galletas = aleatorio<1,5>();
  for(int i = 0; i < num_nuevas_galletas; i++){
    int fila =  aleatorio <0,3>();
    int columna = aleatorio<0,3>();
    tablero[fila][columna]++;
  }
}

void funcion_jugador(MRef<Plato> monitor, int n_hebra)
{
  do{
    this_thread::sleep_for( chrono::milliseconds( aleatorio<100,3000>() ));
    int fila = aleatorio<0,3>();
    int col = aleatorio<0,3>();
    bool conseguido = monitor->CogeGalleta(n_hebra, fila, col);
    if(!conseguido){
      monitor->actuaBloqueado(n_hebra);
    }
  }while(!(monitor->comprobar_terminado()));
  cout << "SE TERMINÓ EL JUEGO" << endl;
}

void funcion_cocinero(MRef<Plato> monitor)
{
  while(rellerna_plato > 0){
    monitor->pon_galletas();
    rellerna_plato--;
    this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,3000>() ));
  }
  cout << "EL COCINERO YA NO AÑADE MAS GALLETAS" << endl;
}

int main()
{
  MRef<Plato> monitor = Create<Plato>();
  thread jugadores[n_jugadores];

  for(int i = 0; i < n_jugadores; i++){
    jugadores[i] = thread(funcion_jugador, monitor, i);
  }

  thread cocinero(funcion_cocinero, monitor);
  cocinero.join();

  for(int i = 0; i < n_jugadores; i++){
    jugadores[i].join();
  }
}
