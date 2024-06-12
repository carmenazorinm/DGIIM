
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

class Campo : public HoareMonitor
{
private:
  const static int n_jugadores = 3;
  int n_jugadores_vivos;
  int campo[n_jugadores][n_jugadores]; // true si hay jugador ocuapndo casilla
  int casilla_actual[n_jugadores];
  CondVar esperar_hebra[n_jugadores];
  bool hebra_espera[n_jugadores];
  int vidas[n_jugadores];
  CondVar desbloqueo;

public:
  Campo();
  void moverme(int i, int j, int jugador);
  void mostrar_campo();
  bool enemigo(int col);
  void comprobar(int i);
};

Campo::Campo()
{
  n_jugadores_vivos = n_jugadores;
  desbloqueo = newCondVar();

  for(int i = 0; i < n_jugadores; i++){
    hebra_espera[i] = false;
    esperar_hebra[i] = newCondVar();
    //esperar_recup_vida[i]  = newCondVar();
    for(int j = 0; j < n_jugadores; j++){
      campo[i][j] = -1;
    }
    campo[i][i] = i;
    casilla_actual[i] = i*n_jugadores+i;
  }
  for(int i = 0; i < n_jugadores; i++){
    vidas[i] = 1;
  }
}

void Campo::comprobar(int i)
{
  bool bloqueo = true;
  for(int j = 0; j < n_jugadores & bloqueo; j++){
    if(i != j){
      if(!hebra_espera[j] ){
        bloqueo = false;
      }
    }
  }

  if(bloqueo || hebra_espera[i]){
    int fila = aleatorio<0,2>();
    int columna = aleatorio<0,2>();
    moverme(fila, columna, i);
    comprobar(i);
  }

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

void Campo:: moverme(int fila, int columna, int i)
{
  if(vidas[i] == 0){
    desbloqueo.wait();
  }

  int sup_jugador = campo[fila][columna];
  if(sup_jugador>-1 & sup_jugador != i){
    cout << "hebra " << i << " espera a que " << sup_jugador << " se mueva " << endl;
    hebra_espera[sup_jugador] = true;
    comprobar(i);
    esperar_hebra[sup_jugador].wait();
  }
  if(vidas[i] == 0){
    desbloqueo.wait();
  }

  //la hebra i abandona su casilla
  campo[casilla_actual[i]/n_jugadores][casilla_actual[i]%n_jugadores] = -1;
  cout << "hebra " << i << " se mueve a casilla [" << fila << "][" << columna << "]" << endl;

  //la hebra i se mueve  a la casilla que quería
  campo[fila][columna] = i;
  casilla_actual[i] = fila*n_jugadores + columna;

  //la hebra i avisa de que se ha movido si es necesario
  if(hebra_espera[i]){
    hebra_espera[i] = false;
    esperar_hebra[i].signal();
  }
  mostrar_campo();
}

bool Campo::enemigo(int col)
{
  int jugador = -1;
  for(int i = 0; i < n_jugadores; i ++){
    if(campo[i][col] > -1){
      jugador = campo[i][col];
      vidas[jugador]--;
      n_jugadores_vivos--;
      cout << " EL JUGADOR " << jugador << " HA SIDO ELIMINADO (" << vidas[jugador] << " vidas restantes)" <<endl;
      campo[i][col] = -1;
      casilla_actual[jugador] = -1;
    }
  }
  if(jugador == -1)
  cout << "NINGUN JUGADOR HA SIDO ELIMINADO" << endl;

  mostrar_campo();
  return (n_jugadores_vivos >0);
}


void funcion_jugador(MRef<Campo>monitor, int i, int n_jugadores)
{
  // vector vidas.
  // pos x actual
  // pos y actual
  while(true){
    int columna = aleatorio<0,2>();
    int fila = aleatorio<0,2>();
    this_thread::sleep_for( chrono::milliseconds( aleatorio<100,3000>() ));
    // me devuelve si me he movido.
    movido = monitor->moverme(fila,columna,i);
    // movido = monitor->moverme(fila, columna, i, x, y)
    // para actualizar mi x e y.

    // Compruebo si me han golpeado.
    // miro el monitor,
    // golpeado = monitor -> golpeado(i)
    // me bloquea
  }
}



void funcion_enemigo(MRef<Campo> monitor)
{
  bool quedan_jugadores_vivos = true;
  while(quedan_jugadores_vivos){
    -
    -40.58+9+
    int columna = aleatorio<0,2>();
    quedan_jugadores_vivos =monitor->enemigo(columna);
  }
}

int main()
{
  MRef<Campo> monitor = Create<Campo>();
  int n_jugadores = 3;

  thread jugador[n_jugadores];
  for(int i = 0; i < n_jugadores;i++){
    jugador[i] = thread(funcion_jugador, monitor, i, n_jugadores);
  }
  thread enemigo(funcion_enemigo, monitor);
  enemigo.join();
  for(int i = 0; i < n_jugadores;i++){
    jugador[i].join();
  }

}
