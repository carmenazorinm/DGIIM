
#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

void reposta()
{
  cout << "Estoy repostando" << endl;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<100,300>() ));
}

void conduce()
{
  cout << "Estoy conduciendo" << endl;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<100,300>() ));
}

class Gasolinera: public HoareMonitor
{
private:
  int uso_gasolina;
  int uso_gasoil;
  CondVar gasolina;
  CondVar gasoil;

public:
  Gasolinera();
  void entra_coche_gasoil(int i);
  void sale_coche_gasoil(int i);
  void entra_coche_gasolina(int i);
  void sale_coche_gasolina(int i);
};

Gasolinera::Gasolinera()
{
  uso_gasolina = 0;
  uso_gasoil = 0;
  gasolina = newCondVar();
  gasoil = newCondVar();
}

void Gasolinera::entra_coche_gasolina(int i)
{
  if(uso_gasolina == 3)
    gasolina.wait();
  uso_gasolina++;
  cout << "El coche "  << i <<" reposta con gasolina" << endl;
}

void Gasolinera::entra_coche_gasoil(int i)
{
  if(uso_gasoil == 2)
    gasoil.wait();
  uso_gasoil++;
  cout << "El coche " << i <<" reposta con          gasoil" << endl;
}

void Gasolinera::sale_coche_gasolina(int i)
{
  uso_gasolina--;
  cout << "El coche " << i << " termina surtidor gasolina " << endl;
  if(uso_gasolina+1 == 3)
    gasolina.signal();
}

void Gasolinera::sale_coche_gasoil(int i)
{
  uso_gasoil--;
  cout << "El coche " << i << " termina surtidor gasoil " << endl;
  if(uso_gasoil+1 == 2)
    gasoil.signal();
}


void funcion_gasoil(MRef<Gasolinera> monitor, int i)
{
  while(true)
  {
    monitor->entra_coche_gasoil(i);
    reposta();
    monitor->sale_coche_gasoil(i);
    conduce();
  }
}

void funcion_gasolina(MRef<Gasolinera> monitor, int i)
{
  while(true)
  {
    monitor->entra_coche_gasolina(i);
    reposta();
    monitor->sale_coche_gasolina(i);
    conduce();
  }
}

int main()
{
  MRef<Gasolinera> monitor = Create<Gasolinera>();
  const int n_gasoil = 4;
  const int n_gasolina = 6;
  thread gasoil[n_gasoil];
  thread gasolina[n_gasolina];

  for(int i = 0; i < n_gasolina; i++)
  {
    gasolina[i] = thread(funcion_gasolina, monitor,i);
  }

  for(int i = 0; i < n_gasoil; i++)
  {
    gasoil[i] = thread(funcion_gasoil, monitor,i);
  }

  for(int i = 0; i < n_gasolina; i++)
  {
    gasolina[i].join();
  }

  for(int i = 0; i < n_gasoil; i++)
  {
    gasoil[i].join();
  }
}
