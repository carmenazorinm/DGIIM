/* FUNDAMENTOS DE LA PROGRAMACION
	
	Carmen Azorín Martí Grupo 2.2. 
	
	Matemáticas e Ingeniería Informática
	
	Proyecto: Elecciones.
	
	Cálculo de los escaños que corresponden a varios partidos / coaliciones / 
	agrupaciones que se presentan en Andalucía. 
	
	Se emplea la Ley D'Hont para el resparto de escaños. 
	
	Los datos usados corresponden a los de la Elecciones autonómicas 2018 
	en la Comunidad Autónoma de Andalucía: 
	
	https://resultados.elpais.com/elecciones/2018/autonomicas/01/index.html
*/

#define VERBOSE
#define VERBOSE_DHONT
 
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

/***************************************************************************/
/***************************************************************************/
void Linea (int num_veces, char c) 
{
	for (int i=0; i<num_veces; i++) cout << c;
	cout << endl;
} 

/***************************************************************************/
/***************************************************************************/
void Cabecera (string msg, int num_veces, char c) 
{
	Linea (num_veces, c);	 
	cout << msg << endl;
	Linea (num_veces, c);	 

	cout << endl; 	
} 

/***************************************************************************/
/***************************************************************************/

int main ()
{
	const int MAX_PROVINCIAS = 100;
	const int MAX_PARTIDOS   = 100; 
	
	// Nombres de las circunscripciones electorales
	string nombres_provincias[MAX_PROVINCIAS];
	
	// Nombres de los partidos/coaliciones/agrupaciones electorales
	string nombres_partidos  [MAX_PARTIDOS];

	// Información agrupada sobre circunscripciones 
	struct InfoProvincia {
		
		// Info a priori
		int num_provincia; // Indice al array "nombres_provincias"
		int escagnos; 	// Num. de escaños a asignar
		int censados; 	// Votantes con derecho a voto
		
		// Datos leidos, resultado del recuento
		int nulos;   // Num. votos nulos
		int blancos; // Num. votos en blanco
		
		// Datos calculados
		int votos_a_partidos; // Votos destinados a partidos
		int validos;		  // Votos válidos = votos_a_partidos + blancos
		int emitidos;		  // Votos emitidos = validos + nulos
		int abstencion;		  // Abstencion = censados - emitidos
	};
	
	// Información de todas las provincias 
	InfoProvincia resumen_provincias [MAX_PROVINCIAS];
	
	// Datos del recuento
	int recuento [MAX_PROVINCIAS][MAX_PARTIDOS] = {0};
	
	// Totales globales sumando todas las circunscripciones
	struct InfoTotales {
	
		int escagnos;	// Total escaños 
		int censados; 	// Total censados 	

		int votos_a_partidos; // Total votos a partidos
		int blancos;	// Total votos nulos
		int nulos;		// Total votos en blanco 
		
		int validos;  	// Total votos validos			
		int emitidos;  	// Total votos emitidos
		int abstencion;	// Total abstencion	
	}; 
	
	// La variable "total" agrupa todos los totales. 
	// Los inicializamos todos a 0
	InfoTotales total = {0,0,0,0,0,0,0,0}; 
	
	
	/*************************************************************************/
	// ENTRADA DE DATOS / INICIALIZACIÓN DE ESTRUCTURAS DE DATOS
	/*************************************************************************/
	/*
		Bloque de inicialización: lectura / asignación de datos a 
		los arrays/matrices 

		En esta fase se asignarán los nombres a las circunscripciones 
		y a los partidos. También datoos generales de las circunscripciones 
		(censo y escaños a repartir). Finalmente se establecen los datos 
		obtenidos del recuento (votos blancos, nulos y a partidos). 
		
		En una versión posterior, este bloque debería cambiarse por otro que 
		leyera los datos desde un fichero de texto, por ejemplo. En ese caso 
		deberá establecerse previamente un formato que permita su lectura. 
	*/


	/*************************************************************************/	
	// Datos críticos: número de circunscripciones y número de partidos 
	// por circunscripción. 
	// En esta versión se asignan directamente. Si los datos se leyeran de 
	// un fichero, se leerían o calcularían.  
	
	int num_provincias =  8;
	int num_partidos   = 10;
	
	
	/*************************************************************************/
	// DATOS PREVIOS A LAS ELECCIONES
	
	// Nombres de provincias
	
	nombres_provincias[0]="ALMERIA"; 
	nombres_provincias[1]="CADIZ"; 
	nombres_provincias[2]="CORDOBA"; 
	nombres_provincias[3]="GRANADA"; 
	nombres_provincias[4]="HUELVA"; 
	nombres_provincias[5]="JAEN"; 
	nombres_provincias[6]="MALAGA"; 
	nombres_provincias[7]="SEVILLA"; 

	/*************************************************************************/
	// Nombres de partidos
	
	nombres_partidos[0] = "PSOE-A";
	nombres_partidos[1] = "PP";
	nombres_partidos[2] = "Cs";
	nombres_partidos[3] = "ADELANTE ANDALUCIA";
	nombres_partidos[4] = "VOX";
	nombres_partidos[5] = "PACMA";
	nombres_partidos[6] = "AxSI";
	nombres_partidos[7] = "EQUO-INICIATIVA";
	nombres_partidos[8] = "RECORTES CERO";
	nombres_partidos[9] = "OTROS";
	
	
	/*************************************************************************/
	// Datos generales previos al recuento (por provincia)

	// 0.- ALMERÍA
	resumen_provincias[0].num_provincia =  0;
	resumen_provincias[0].escagnos =      12; 	
	resumen_provincias[0].censados =  456913; 
	
	// 1.- CÁDIZ
	resumen_provincias[1].num_provincia =  1; 
	resumen_provincias[1].escagnos =      15; 	
	resumen_provincias[1].censados =  968815; 
	
	// 2.- CORDOBA
	resumen_provincias[2].num_provincia =  2; 
	resumen_provincias[2].escagnos =      12; 	
	resumen_provincias[2].censados =  628885; 
	
	// 3.- GRANADA
	resumen_provincias[3].num_provincia =  3; 
	resumen_provincias[3].escagnos =      13; 	
	resumen_provincias[3].censados =  701118; 
	
	// 4.- HUELVA
	resumen_provincias[4].num_provincia =  4; 
	resumen_provincias[4].escagnos =      11; 	
	resumen_provincias[4].censados =  389055;
	
	// 5.- JAÉN
	resumen_provincias[5].num_provincia =  5; 
	resumen_provincias[5].escagnos =      11; 	
	resumen_provincias[5].censados =  514281; 

	// 6.- MÁLAGA
	resumen_provincias[6].num_provincia =  6; 
	resumen_provincias[6].escagnos =      17; 	
	resumen_provincias[6].censados = 1129411; 

	// 7.- SEVILLA
	resumen_provincias[7].num_provincia =  7; 
	resumen_provincias[7].escagnos =      18; 	
	resumen_provincias[7].censados = 1505927; 
	
	
	/*************************************************************************/
	// DATOS DEL RECUENTO
	
	/*************************************************************************/
	// Datos generales del recuento (por provincia)

	// 0.- ALMERÍA
	resumen_provincias[0].nulos    =    3394;   
	resumen_provincias[0].blancos  =    2962; 
	
	// 1.- CÁDIZ	
	resumen_provincias[1].nulos    =    9471;   
	resumen_provincias[1].blancos  =    9142; 
	
	// 2.- CORDOBA	
	resumen_provincias[2].nulos    =    9367;   
	resumen_provincias[2].blancos  =    6442; 
	
	// 3.- GRANADA
	resumen_provincias[3].nulos    =   13711;   
	resumen_provincias[3].blancos  =    5749; 
	
	// 4.- HUELVA	
	resumen_provincias[4].nulos    =    5132;    
	resumen_provincias[4].blancos  =    3611; 

	// 5.- JAÉN	
	resumen_provincias[5].nulos    =    8245;   
	resumen_provincias[5].blancos  =    4053; 

	// 6.- MÁLAGA	
	resumen_provincias[6].nulos    =   10297;
	resumen_provincias[6].blancos  =    8907; 

	// 7.- SEVILLA
	resumen_provincias[7].nulos    =   21516;   
	resumen_provincias[7].blancos  =   16050; 
	
	
	/*************************************************************************/
	// Votos a partidos (por provincia y partido)
	
	// 0.- ALMERIA
	recuento [0][0] = 67088; recuento [0][1] = 70504; recuento [0][2] = 42258;
	recuento [0][3] = 24985; recuento [0][4] = 43468; recuento [0][5] =  3460;
	recuento [0][6] =   319; recuento [0][7] =   852; recuento [0][8] =   344;
	recuento [0][9] =  2578;
	
	// 1.- CADIZ
	recuento [1][0] = 121100; recuento [1][1] = 89517; recuento [1][2] = 106331;
	recuento [1][3] =  97647; recuento [1][4] = 57279; recuento [1][5] =  11405;
	recuento [1][6] =   8073; recuento [1][7] =  2055; recuento [1][8] =   1199;
	recuento [1][9] =   5488;
	
	// 2.- CORDOBA
	recuento [2][0] = 111501; recuento [2][1] = 83715; recuento [2][2] = 67352;
	recuento [2][3] =  64048; recuento [2][4] = 35096; recuento [2][5] =  5878;
	recuento [2][6] =   1602; recuento [2][7] =  1449; recuento [2][8] =   613;
	recuento [2][9] =   3859;

	// 3.- GRANADA
	recuento [3][0] = 111161; recuento [3][1] = 95220; recuento [3][2] = 75949;
	recuento [3][3] =  62206; recuento [3][4] = 46952; recuento [3][5] =  7336;
	recuento [3][6] =   1550; recuento [3][7] =  1739; recuento [3][8] =   938;
	recuento [3][9] =   3945;

	// 4.- HUELVA
	recuento [4][0] =  66671; recuento [4][1] = 47653; recuento [4][2] = 34271;
	recuento [4][3] =  30071; recuento [4][4] = 17573; recuento [4][5] =  3990;
	recuento [4][6] =   3197; recuento [4][7] =  1398; recuento [4][8] =   809;
	recuento [4][9] =   1719;

	// 5.- JAÉN
	recuento [5][0] = 112339; recuento [5][1] = 73532; recuento [5][2] = 50604;
	recuento [5][3] =  38473; recuento [5][4] = 27671; recuento [5][5] =  4093;
	recuento [5][6] =    958; recuento [5][7] =   696; recuento [5][8] =   367;
	recuento [5][9] =   4512;
		
	// 6.- MÁLAGA
	recuento [6][0] = 152279; recuento[6][1] = 142182; recuento[6][2] = 124573;
	recuento [6][3] =  98440; recuento[6][4] =  72455; recuento[6][5] =  15766;
	recuento [6][6] =   3156; recuento[6][7] =   2429; recuento[6][8] =   2305;
	recuento [6][9] =   6766;
		
	// 7.- SEVILLA
	recuento [7][0] = 267104; recuento[7][1] = 146952; recuento[7][2] = 158293;
	recuento [7][3] = 168170; recuento[7][4] =  95484; recuento[7][5] =  18525;
	recuento [7][6] =   5688; recuento[7][7] =   4253; recuento[7][8] =   2230;
	recuento [7][9] =   8104;
	

	/*************************************************************************/
	// CÁLCULOS
	/*************************************************************************/

	// Mostrar info previa al escrutinio
	
	Cabecera ("INFORMACION PREVIA", 80, '*'); 

	for (int prov=0; prov<num_provincias; prov++) {
		
		// Actualizar los totales de censados y escaños
		total.censados += resumen_provincias[prov].censados;
		total.escagnos += resumen_provincias[prov].escagnos;
	}

	// Linea de totales 
	cout <<"ANDALUCIA";
    cout << endl;
	cout << "  Escagnos : " << total.escagnos;  
	cout << setw(16) << " " << "  Votantes censados : " << total.censados; 
	cout << endl << endl; 
	

	/*************************************************************************/
	// Calcular resumen de escrutinio
		
	// Ciclo principal: por provincia
	
	for (int prov=0; prov<num_provincias; prov++) {
		
		// Votos a partidos

		//cout << "Calculando votos a partidos en provincia " << prov 
		//     << " (" << nombres_provincias[prov] << ")" << endl; 
		  
		resumen_provincias[prov].votos_a_partidos = 0;
		
		// Ciclo secundario: por partido
		
		for (int part=0; part<num_partidos; part++) {
			//cout << "PARTIDO " << setw(2) << part << "--> " 
			//     << setw(8) << recuento [prov][part] << endl; 
			resumen_provincias[prov].votos_a_partidos += recuento [prov][part];
		}
		//cout << endl; 
		
		// Datos calculados por provincia
		
		// 1) Válidos = votos a partidos + blancos 
		resumen_provincias[prov].validos = 
			resumen_provincias[prov].votos_a_partidos +  
			resumen_provincias[prov].blancos;
		
		// Emitidos =  votos a partidos + blancos + nulos = válidos  + nulos  
		resumen_provincias[prov].emitidos = 
			resumen_provincias[prov].validos + 
			resumen_provincias[prov].nulos;
			 
		// Abstención = censados - emitidos
		resumen_provincias[prov].abstencion = 
			resumen_provincias[prov].censados -  
			resumen_provincias[prov].emitidos; 
		
		
		// Actualizar los totales de nulos, blancos, votos a partidos, 
		// emitidos y abstenciones.
		
		total.nulos   += resumen_provincias[prov].nulos;
		total.blancos += resumen_provincias[prov].blancos;
		total.votos_a_partidos += resumen_provincias[prov].votos_a_partidos;
		
		total.validos    += resumen_provincias[prov].validos;
		total.emitidos   += resumen_provincias[prov].emitidos;
		total.abstencion += resumen_provincias[prov].abstencion; 
	}
	
	
	/*************************************************************************/
	// Mostrar resumen de escrutinio (por provincias y total)

	Cabecera ("ESCRUTINIO: RESUMEN POR CIRCUNSCRIPCION Y TOTAL", 80, '*'); 

 	cout << "               "; 
	cout << setw(10) << "CENSADOS" << setw(10) << "PARTIDOS";	
	cout << setw(10) << "NULOS" << setw(10) << "BLANCOS";	
	cout << setw(10) << "EMITIDOS" << setw(10) << "VALIDOS";	
	cout << setw(10) << "ABSTENC" << endl;
	
	cout << "                ";
	cout << setw(65) << setfill('-') << " ";
	cout << setfill(' '); 
	cout << endl;

	// Resumen total 
		
	cout << "    TOTALES =  ";
	cout << setw(7) << right << total.censados 
	     << setw(10) << total.votos_a_partidos
		 << setw(10) << total.nulos 
		 << setw(10) << total.blancos 
		 << setw(10) << total.emitidos 
		 << setw(10) << total.validos 
		 << setw(10) << total.abstencion << endl; 	  
	cout << endl; 	  
	
	
	/*************************************************************************/
	// Calcular distribucion de escaños por provincia
	/*************************************************************************/
	
	Cabecera ("ASIGNACION DE ESCAGNOS POR PROVINCIA (LEY D'HONT)", 80, '*'); 

	int num_escagnos, votos_validos_totales;
	
	// Se calculan los escaños y los votos validos totales de toda Andalucía, 
	// es decir, la suma de los datos de todas sus provincias
	for(int prov = 0; prov < num_provincias; prov++){
		
		num_escagnos += resumen_provincias[prov].escagnos; 
		votos_validos_totales += resumen_provincias[prov].validos;

     // Solo entran en competencia los partidos que hayan obtenido, 
	// al menos, el 3% de los datos válidos.
	int votos_validos_prov = resumen_provincias[prov].validos;
	double tres_porciento = static_cast<int> (0.03 * votos_validos_totales);

	
	cout << "................................................." << endl;
	cout << endl; 		     		 		     		
	cout << "Calculando escagnos en Andalucía " << prov 
	     << " (" << nombres_provincias[prov] << ")";
	cout << "--> Escagnos = " << setw(2)<< num_escagnos << endl;
	cout << endl;   
	cout << "Votos validos = " << setw(8)<< votos_validos_prov;
	cout << "   Umbral votos (3%) = " << setw(8) << tres_porciento << endl;
	
	// La informacion de cada partido que supere el 3% de los votos 
	// válidos en la circunscripción "prov" se guarda en un struct:
	
	struct info_partido_DHont {
	   	int num_partido; 	// Num. de partido (en "nombres_partidos")
	   	int votos;			// Votos recibidos
	   	int escagnos;		// Escaños conseguidos
	};
	
	// La información de todos los partidos se guarda en un array
	// de datos info_partido_DHont
	info_partido_DHont distribucion[MAX_PARTIDOS]; 
	
	
	#ifdef VERBOSE_DHONT
	cout << endl; 
	cout << "Preparando calculos DHont" << endl;
	cout << endl; 
	#endif
			
	int num_partidos_DHont = 0;
	
	// Se crea el vector que guarda los votos de cada uno de los partidos en 
	// Andalucía, es decir, la suma de los votos de cada partido en las 
	// distantas oprovincias de la comunidad.
	int votos_partidos[MAX_PARTIDOS];
	for (int i = 0; i < num_partidos; i++) {	
		for (int j = 0; j < num_provincias; j++) {
			votos_partidos[i] += recuento[j][i];	
		}	
	}
	
	for (int part=0; part<num_partidos; part++) {
				
		// Solo se consideran los partidos que hayan tenido un número 			
		// de votos superior al 3% de los votos válidos
			
		if (votos_partidos[part] > tres_porciento) {
			
	        distribucion[num_partidos_DHont].num_partido = part;
	        distribucion[num_partidos_DHont].votos = 
				votos_partidos[part];
	 		distribucion[num_partidos_DHont].escagnos = 0;  
			   
			num_partidos_DHont++;  		
				 		
			#ifdef VERBOSE_DHONT
			cout << "  Aceptado   partido " << setw(2) << part << " (" 
			     << setw(20) << nombres_partidos[part] << ") --> " 
				 << setw(8)  << votos_partidos[part] << " votos" << endl;
			#endif
		}
		else {
			#ifdef VERBOSE_DHONT
			cout << "  Descartado partido " << setw(2) << part << " (" 
			     << setw(20) << nombres_partidos[part] << ") --> " 
				 << setw(8)  << votos_partidos[part] << " votos" << endl;  		  		
			#endif
		}
		
	} 
	
  	cout << endl; 
  	
	cout << "  Se consideran " << setw(3) << num_partidos_DHont 
	     << " partidos en total." << endl; 
    cout << endl; 
    
   	
	#ifdef VERBOSE_DHONT
	cout << "  Partidos que pugnan por escagnos (antes de ordenar):"<< endl;
	cout << endl; 
			
	for (int part=0; part<num_partidos_DHont; part++) {
		
		int n = distribucion[part].num_partido;
		cout << setw(20) << nombres_partidos[n] << " --> ";
		cout << setw(8) << distribucion[part].votos << " votos." << endl;			
	}
	cout << endl; 
	#endif
 		
 		
	// Ordenar "distribucion" de acuerdo al campo "votos"
	// Criterio: decreciente
	// Algoritmo: ordenación por inserción
		
	for (int izda = 1; izda < num_partidos_DHont; izda++) {
		
		// "a_insertar" es el valor que se va a insertar en el
		// subvector izquierdo. Este subvector está ordenado y
		// comprende las posiciones entre 0 e "izda"-1
		
		info_partido_DHont a_insertar = distribucion[izda];
		
		// Se busca la posición en la zona ordenada (0..izda-1)
		int i = izda; 
		bool sigo = true; 
		
		while (i > 0 && sigo) {
			
			if (a_insertar.votos > distribucion[i-1].votos) {
				
				// Desplazar a la derecha los mayores que "a_insertar"
				
				distribucion[i] = distribucion[i-1];  		
				i--;
			}
			else sigo = false;
		}
		distribucion[i] = a_insertar; // Copiar en el hueco
	}
	
	#ifdef VERBOSE_DHONT
	cout << "  Partidos que pugnan por escagnos (tras ordenar):"<< endl;
	cout << endl; 
	
	for (int part=0; part<num_partidos_DHont; part++) {
		
		int n = distribucion[part].num_partido;
		cout << setw(20) << nombres_partidos[n] << " --> ";
		cout << setw(8) << distribucion[part].votos << " votos." << endl;			
	}
  	cout << endl; 
	#endif

	// Asignación de escaños
	//
	// Cada escaño se asigna de acuerdo al mayor cociente entre votos 
	// y escaños ya conseguidos más uno. 
	//
	// Esto es, el partido "p" para el que el cociente entre: 
	//	* 	los votos totales conseguidos, y 
	//	* 	el número de escaños que le han sido asignados hasta ese 
	//		momento más uno 
	// sea mayor consigue el escaño.

	double coc_max;   // cociente máximo 
	int partido_max;  // partido para el que se obtiene el cociente máximo
	
	for (int escagno = 0; escagno < num_escagnos; escagno++) {
				  			  
	   	coc_max = -1.0; // Primer máximo
    
    	// El máximo se calcula entre todos los partidos que han 
    	// superado el umbral del 3% de los votos válidos
    	
		for (int part=0; part<num_partidos_DHont; part++) {
	
			// Cociente para el partido "part" --> votos/escaños+1
			
			double coc_part = (1.0*distribucion[part].votos) / 
			                 (distribucion[part].escagnos+1);
			
			if (coc_part > coc_max ) {
				coc_max = coc_part;
                partido_max = part; 
			}
			
		} // for part
		
		// Asignación el escaño al partido "partido_max"
		distribucion[partido_max].escagnos++;
	
	}	
	
	// Presentación del resultado   
		  
    cout << "Distribucion de escagnos: " << endl;
    cout << endl;

	int suma_escagnos_andalucia_part = 0;
	
	for (int part = 0; part < num_partidos; part++) {
	   	
	   	int num_escagnos_part = distribucion[part].escagnos; 
	   	
	   	if (num_escagnos_part > 0) {
	
			cout << "  PARTIDO " << setw(2) << part << " (" 
				 << setw(20) << nombres_partidos[part] << ") --> " 
				 << setw(3)  << num_escagnos_part << endl; 
	
			suma_escagnos_andalucia_part += num_escagnos_part;
	   	} 
	}		
	cout << setw(40) << " " << "---" << endl;
	cout << setw(40) << " " << setw(3) << suma_escagnos_andalucia_part << endl;
	cout << endl;
	
	
	// Test de integridad 
	if (suma_escagnos_andalucia_part != num_escagnos) {
		cout << endl;
		cout << "ERROR DE INTEGRIDAD (1)" << endl;
		cout << endl; 		
		exit (1); 
	}
	}//for prov

	/************************************************************************/
	
	return 0;
	
}


