// CARMEN AZORIN MARTI 48768328W A1

#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_jugadores= 2 ,              // número de jugadores (peach y mario)
   num_procesos  = num_jugadores+1,   // número de procesos total (jugadores y el npc)
   id_npc   = num_jugadores,
   id_peach=0,
   id_mario=1,
   etiq_mario=0,
   etiq_peach=1;


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------

void funcion_jugadores( int id )
{
	int valores[2] = {0,0};
	int valor, longitud;
	MPI_Status estado ;
	int etiqueta;
	string nom_jugador = "";
  int n_veces = 0;
  while ( n_veces < 5 )
  {
    //Primero cuento cuantas
    int kilos=0;
     MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);//mira si hay algun mensaje y espera bloqueado hasta que lo haya
     MPI_Get_count(&estado, MPI_INT, &longitud);

     MPI_Recv ( &valores, longitud, MPI_INT, id_npc, MPI_ANY_TAG, MPI_COMM_WORLD,&estado );

     if (id==id_mario){//si se lo ha mandado a mario
     	nom_jugador = "Mario ";
     	etiqueta=etiq_mario;
     }else{//se lo ha mandado a peach
     	nom_jugador = "Peach ";
     	etiqueta=etiq_peach;
     }

     if (longitud==2){	//le ha mandado dos tartas
     		cout<< nom_jugador << "ha recibido dos tartas de: "<< valores[0]<< " y otra de "<< valores[1]<<endl;
     		kilos=valores[0]+valores[1];
     	}else{//solo ha mandado una tarta
     		cout<< nom_jugador << "ha recibido una tarta de: "<<valores[0] <<endl;
     		kilos=valores[0];
     	}

     	//COMEN
     	cout << "Jugador " << nom_jugador << " comienza a comer" << endl;
   	sleep_for( milliseconds( aleatorio<100,300>() ) );
    int kilos_comidos = random() % kilos;
    cout << "Jugador " << nom_jugador << " come en total " << kilos_comidos << endl;

 	//envia los kilos comidos
   	MPI_Ssend (&kilos_comidos, 1, MPI_INT, id_npc, etiqueta, MPI_COMM_WORLD);
    n_veces++;

  }
}
// ---------------------------------------------------------------------
void funcion_npc( )
{
  int valor, id_jugadores ;  // valor recibido, identificador del jugador
  MPI_Status estado ;       // metadatos de las dos recepciones
  int etiqueta;
  int kilos_peach[2]={aleatorio<1,10>(),aleatorio<1,10>()};
  int kilos_mario[2]={aleatorio<1,10>(),aleatorio<1,10>()};
  int n_veces = 0;

  int puntos_mario=0;
  int puntos_peach=0;

  while ( n_veces < 5 )
  {
  //mando a peach
  	for (int i=0; i<2; i++){
  		kilos_peach[i]=aleatorio<1,10>();
  	}
  	for (int i=0; i<2; i++){
  		kilos_mario[i]=aleatorio<1,10>();
  	}
  	int tartas_a_mandar_peach=aleatorio<1,2>(); // elijo cuantas tartas voy a mandar
  	cout << "Se mandan valores" << endl;
    // mandar los kilos a peach
  	MPI_Ssend (&kilos_peach, tartas_a_mandar_peach, MPI_INT, id_peach, 0, MPI_COMM_WORLD);


  	//mando a mario

  	int tartas_a_mandar_mario=aleatorio<1,2>(); // elijo cuantas tartas mandar a mario
  	  	// cout << "Se mandan valores" << endl;
        // mandar los kilos con el n_tartas a mario
  	MPI_Ssend (&kilos_mario, tartas_a_mandar_mario, MPI_INT, id_mario, 0, MPI_COMM_WORLD);

  	int kg_mario=0;
  	int kg_peach=0;
  	//REcibe los kilos que han comido cada jugador
  	MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,&estado );
  	if (estado.MPI_TAG==etiq_mario){
  		kg_mario=valor;
  	}else{
  		kg_peach=valor;
  	}
    // recibe los kilos del otro jugador
  	MPI_Recv ( &valor, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,&estado );
  	if (estado.MPI_TAG==etiq_mario){
  		kg_mario=valor;
  	}else{
  		kg_peach=valor;
  	}

  	//COMprobacion resultados
  	if (kg_mario>kg_peach){
  		cout<<"GANA MARIO"<<endl;
      puntos_mario++;
  	}else if(kg_mario < kg_peach){
  		cout<<"GANA PEACH"<<endl;
      puntos_peach++;
    }
    else
      cout << "EMPATE" << endl;

    n_veces++;


    sleep_for( milliseconds( aleatorio<1000,3000>() ) );
  }

  cout << "EL JUEGO HA TERMINADO, EL GANADOR ES.... ";
  if(puntos_mario > puntos_peach){
    cout << "MARIO!!!";
  }else if(puntos_mario == puntos_peach){
    cout << "EMPATE";
  }else{
    cout << "PEACH!!!";
  }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio == id_npc)    {      // si es par
         funcion_npc( ); //   es un filósofo
      }else
      	 funcion_jugadores(id_propio);
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
