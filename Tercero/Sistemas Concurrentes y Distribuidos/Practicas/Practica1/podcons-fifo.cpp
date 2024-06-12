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
Semaphore libres = tam_vec; //al principio todas las casillas del buffer están libres
Semaphore ocupadas = 0; // al principio no hay ninguna casilla ocupada -> la hebra hebra_consumidora
                        // no puede actuar todavía, hasta que la productora no haya incluido un dat
                        // en el buffer.
int primera_ocupada = 0; //indica la primera casilla con datos no leidos del buffer
int primera_libre = 0; //la primera casilla en la que la producta puede escribir

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato()
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   cout << "producido: " << dato_producido << endl << flush ;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

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

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;
      //si hay entrdas libres, puede añadir un dato al buffer
      sem_wait( libres ); //libres es el numero de entradas libres del buffer (init. tam_buffer)
      vec[primera_libre] = dato;
      primera_libre = ((primera_libre+1)%tam_vec);
      //ahora ya tenemos una casilla ocupada más en el buffer
      sem_signal( ocupadas ); //ocupadas es el numero de entradas ocupadas del buffer (init. 0)
   }
   cout << "La hebra productora ha terminado. " << endl;
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato ;
      //esperar a que haya casillas ocupadas para intentar leer el dato del buffer
      sem_wait( ocupadas );

      dato = vec[primera_ocupada]; //coge la casilla first
      primera_ocupada = ((primera_ocupada+1)%tam_vec); //ahora la casilla first ya se ha leído, será la siguiente
      //si se ha extraido una casilla del buffer, hay una casilla más libre
      sem_signal( libres );
      consumir_dato( dato ) ;
    }

    cout << "La hebra consumidora ha terminado. " << endl;
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO o FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}
