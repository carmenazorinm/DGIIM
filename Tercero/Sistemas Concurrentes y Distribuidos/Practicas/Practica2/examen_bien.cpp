
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

int vidas[3]={3,3,3};
int n_jugadores = 3;
bool bloqueados[3] = {false, false, false};
int n_bloqueadas = 0;
Semaphore sem = 1;

class Campo : public HoareMonitor
{
private:
  const static int n_jugadores = 3;
  int n_jugadores_vivos;
  int campo[n_jugadores][n_jugadores]; // true si hay jugador ocuapndo casilla
  CondVar espera;

public:
  Campo();
  bool moverme(int i, int j, int jugador, int x, int y);
  void mostrar_campo();
  void enemigo(int col);
  void libera_jugadores();
  void espera_jugador();
  bool bloqueado(int i);
  void actua_bloqueada(int i);
};

Campo::Campo()
{
  n_jugadores_vivos = n_jugadores;

  for(int i = 0; i < n_jugadores; i++){
    //esperar_recup_vida[i]  = newCondVar();
    for(int j = 0; j < n_jugadores; j++){
      campo[i][j] = -1;
    }
    campo[i][i] = i;
  }
  espera = newCondVar();
}

void Campo::libera_jugadores()
{
  for(int i = 0; i < n_jugadores-1; i++){
    espera.signal();
  }
}

void Campo::espera_jugador()
{
  espera.wait();
}

void Campo::mostrar_campo(){
  for(int i = 0; i < n_jugadores; i++){
    cout << endl;
    for(int j = 0; j < n_jugadores; j++){
      cout << "[\t" << campo[i][j] << "\t]";
    }
  }

  cout << endl << endl;
}

bool Campo:: moverme(int fila, int columna, int i, int x, int y)
{
  if(campo[fila][columna] > -1 || bloqueados[i]){
    return false;
  }

  //la hebra i abandona su casilla
  campo[x][y] = -1;
  cout << "hebra " << i << " se mueve a casilla [" << fila << "][" << columna << "]" << endl;

  //la hebra i se mueve  a la casilla que quería
  campo[fila][columna] = i;
  mostrar_campo();

  return true;
}

void Campo::enemigo(int col)
{
  this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,3000>() ));
  int jugador = -1;
  for(int i = 0; i < n_jugadores; i ++){
    if(campo[i][col] > -1){
      jugador = campo[i][col];
      vidas[jugador]--;
      bloqueados[jugador] = true;
      campo[i][col] = -1;
      n_bloqueadas++;
      if(vidas[jugador] > 0)
        cout << "EL JUGADOR " << jugador << " HA SIDO ELIMINADO (" << vidas[jugador] << " vidas restantes)" <<endl;
      else
        cout << "EL JUGADOR " << jugador << " HA SIDO ELIMINADO (sin vidas restantes)" <<endl;

    }
  }
  if(jugador == -1)
  cout << "NINGUN JUGADOR HA SIDO ELIMINADO" << endl;

  mostrar_campo();
}

void Campo::actua_bloqueada(int i)
{
  if(n_bloqueadas == n_jugadores){
    for(int j = 0; j < n_jugadores; j++){
        campo[j][j] = j;
          bloqueados[j] = false;
    }
    n_bloqueadas = 0;
    cout << "JUGADOR " << i << " LIBERA AL RESTO DE JUGADORES" << endl;
    libera_jugadores();
    mostrar_campo();
  }else{
    cout << "JUGADOR " << i <<" SE BLOQUEA TEMPORALMENTE" << endl;
    espera_jugador();
  }
}

bool Campo::bloqueado(int i){
  return bloqueados[i];
}


void funcion_jugador(MRef<Campo>monitor, int i)
{
  // vector vidas.
  // pos x actual
  int x = i; //si soy la hebra 0, comienzo en la casilla [0,0]
  // pos y actual
  int y = i;
  while(vidas[i]>0){
    //sem.sem_wait();
    if(monitor->bloqueado(i)){
      //coprobamos que no estan todas bloqueadas
      monitor->actua_bloqueada(i);
      x = i;
      y = i;
      //sem.sem_signal();
    }else{
      int columna = aleatorio<0,2>();
      int fila = aleatorio<0,2>();
      this_thread::sleep_for( chrono::milliseconds( aleatorio<100,300>() ));
      // me devuelve si me he movido.
      bool movido = monitor->moverme(fila,columna,i,x, y);
      // movido = monitor->moverme(fila, columna, i, x, y)
      // para actualizar mi x e y.
      if(movido){
        x = fila;
        y = columna;
      }
    }


    // Compruebo si me han golpeado.
    // miro el monitor,
    // golpeado = monitor -> golpeado(i)
    // me bloquea
  }
}



void funcion_enemigo(MRef<Campo> monitor)
{
  bool quedan_jugadores_vivos ;
  do{
    quedan_jugadores_vivos = false;
    int columna = aleatorio<0,2>();
    monitor->enemigo(columna);
    for(int i = 0; i < n_jugadores; i++){
      if(vidas[i]>0)
        quedan_jugadores_vivos = true;
    }
  }while(quedan_jugadores_vivos);
}

int main()
{
  MRef<Campo> monitor = Create<Campo>();

  thread jugador[n_jugadores];
  for(int i = 0; i < n_jugadores;i++){
    jugador[i] = thread(funcion_jugador, monitor, i);
  }

  this_thread::sleep_for( chrono::milliseconds( aleatorio<100,3000>() ));

  thread enemigo(funcion_enemigo, monitor);
  enemigo.join();
  for(int i = 0; i < n_jugadores;i++){
    jugador[i].join();
  }

}
