#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const unsigned
   num_items = 40 ,   // número de items
	 tam_vec   = 10 ;   // tamaño del buffer
unsigned
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)

//variables compartidas y valores iniciales
int vec[tam_vec] = {0}; //vec intermedio
Semaphore libres = tam_vec;
Semaphore ocupadas = 0;
Semaphore que_pase_la_siguiente = 1;
Semaphore produce_dato = 1;
Semaphore puedes_consumir = 1; //la primera hebra consumidora puede consumir cuando ocupadas!=0
Semaphore comprueba = 1;
int primera_libre = 0;

const int n_productoras = 2;
const int n_consumidoras = 2;
int items_producidos[n_productoras] = {0};
int contador_consum =0 ;

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato(int nh)
{
  //int p = (num_items/n_productoras);
  //for(int i = p*nh; i <= nh*p + (p-1); i++){
     this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

     sem_wait( produce_dato );
     const unsigned dato_producido = siguiente_dato ;
     siguiente_dato++ ;
     sem_signal( produce_dato );

     cont_prod[dato_producido] ++ ;
     items_producidos[nh]++;
     cout << "Hebra " << nh << " ha producido: " << dato_producido << endl << flush ;
     return dato_producido ;
  //}
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato, int nh )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << " por hebra " << nh << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora( int nh )
{
  int p = (num_items/n_productoras);
   for( unsigned i = p*nh ; i <= p*nh + (p-1) ; i++ )
   {
      int dato = producir_dato(nh) ;
      //esperar a que libres != 0
      sem_wait( libres ); //libres es el numero de entradas libres del buffer (init. tam_buffer)
      sem_wait( que_pase_la_siguiente );

      vec[primera_libre] = dato; //se añade el dato a la primera casilla no ocupada
      primera_libre++; //ahora hay una casilla más ocupada

      sem_signal(que_pase_la_siguiente);
      //mandar la señal de que ya se ha ocupado una casilla más
      sem_signal( ocupadas ); //ocupadas es el numero de entradas ocupadas del buffer (init. 0)
   }
   cout << "La hebra productora ha terminado. " << endl;
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( int nh )
{
  sem_wait(comprueba);
  while(contador_consum < num_items){
    contador_consum++;
  sem_signal(comprueba),
    //int dato ;
    //Esperar a que haya alguna casilla ocupada
    sem_wait( ocupadas );
    sem_wait( puedes_consumir );

    int dato = vec[primera_libre-1]; //leer la última casilla ocupada
    primera_libre--; //ahora hay una casilla menos ocupada

    sem_signal( puedes_consumir );
    //mandar la señal de que hay una casilla libre más
    sem_signal( libres );
    consumir_dato( dato, nh ) ;
  }
   // for( unsigned i = 0 ; i < num_items ; i++ )
   // {
   //    //int dato ;
   //    //Esperar a que haya alguna casilla ocupada
   //    sem_wait( ocupadas );
   //    //sem_wait( puedes_consumir );
   //
   //    int dato = vec[primera_libre-1]; //leer la última casilla ocupada
   //    primera_libre--; //ahora hay una casilla menos ocupada
   //
   //    //sem_signal( puedes_consumir );
   //    //mandar la señal de que hay una casilla libre más
   //    sem_signal( libres );
   //    consumir_dato( dato, nh ) ;
   //  }

    cout << "La hebra consumidora ha terminado. " << endl;
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO o FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

  thread hebras_productoras[n_productoras];
  thread hebras_consumidoras[n_consumidoras];

  for(int i = 0; i < n_productoras; i++){
    hebras_productoras[i] = thread( funcion_hebra_productora, i);
  }

  for(int i = 0; i < n_consumidoras; i++){
    hebras_consumidoras[i] = thread( funcion_hebra_consumidora, i);
  }

  for(int i = 0; i < n_productoras; i++){
    hebras_productoras[i].join();
  }

  for(int i = 0; i < n_consumidoras; i++){
    hebras_consumidoras[i].join();
  }

   test_contadores();
}
