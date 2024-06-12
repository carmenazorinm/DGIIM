
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

mutex
   mtx ;

class Lec_Esc : public HoareMonitor
{
private:
  bool escrib; //true si un escritor esta escribiendo
  int n_lec; //numero de lectores leyendo
  CondVar lectura; //esperar cuando ya hay escritor escribiendo
  CondVar escritura; //esperar cuando ya hay otro escritor escribiendo o hay lectores leyedno

public:
  Lec_Esc();
  void ini_lectura();
  void fin_lectura();
  void ini_escritura();
  void fin_escritura();
};

Lec_Esc::Lec_Esc()
{
  escrib = false;
  n_lec = 0;
  lectura = newCondVar();
  escritura = newCondVar();
}

void Lec_Esc::ini_lectura()
{
  if(escrib)
    lectura.wait(); //espera a que termine de escribir para leer
  n_lec++;
  lectura.signal(); //señala que ya se puede leer por si habia alguien esperando
}

void Lec_Esc::fin_lectura()
{
  n_lec--;
  cout << "Terminé de leer!! " << endl;
  if(n_lec == 0)
    escritura.signal(); //señala que ya se puede escribir
}

void Lec_Esc::ini_escritura()
{
  if(n_lec > 0 || escrib)
    escritura.wait(); //esperar a que le señalen que puede escribir
  escrib=true;
}

void Lec_Esc::fin_escritura()
{
  escrib = false;
  cout << "                         Terminé de escribir!! " << endl;
  if(!lectura.empty())
    lectura.signal(); // señala que ya se puede leer
  else
    escritura.signal(); // señala que se puede escribir
}

void funcion_lector( MRef<Lec_Esc> monitor, int i )
{
  while(true)
  {
    monitor->ini_lectura();
    mtx.lock();
    cout << "Lector " << i << " leyendo... " << endl;
    mtx.unlock();
    this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,2000>() ));
    monitor->fin_lectura();
    this_thread::sleep_for( chrono::milliseconds( aleatorio<1000,2000>() ));
  }
}

void funcion_escritor(MRef<Lec_Esc> monitor, int i )
{
  while(true)
  {
    monitor->ini_escritura();
    //mtx.lock();
    cout << "                       Escritor " << i << " escribiendo... " << endl;
    //mtx.unlock();
    this_thread::sleep_for( chrono::milliseconds( aleatorio<10,20>() ));
    monitor->fin_escritura();
    this_thread::sleep_for( chrono::milliseconds( aleatorio<100,200>() ));
  }
}

int main()
{
  int n_lectores = 4;
  int n_escritores = 4;
  MRef<Lec_Esc> monitor = Create<Lec_Esc>() ;

  thread lectores[n_lectores];
  thread escritores[n_escritores];

  for(int i = 0; i < n_escritores; i++){
    escritores[i] = thread( funcion_escritor, monitor, i);
  }


  for(int i = 0; i < n_lectores; i++){
    lectores[i] = thread( funcion_lector, monitor, i);
  }

  for(int i = 0; i < n_lectores; i++){
    lectores[i].join();
  }

  for(int i = 0; i < n_escritores; i++){
    escritores[i].join();
  }
}
