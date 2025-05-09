// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación). Clase 'NodoGrafoEscena' y relacionadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"  
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 



// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );

   //cout << "Entra " << __FUNCTION__ << ": " << leerNombre() << endl ;

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = aplicacionIG->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = aplicacionIG->pila_materiales ; assert( pila_materiales != nullptr );

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if(tieneColor()) {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }
   
   if(aplicacionIG->iluminacion) {
      aplicacionIG->pila_materiales->push();
   }

   cauce->pushMM();

   for (EntradaNGE entrada: entradas) {
      if( entrada.tipo == TipoEntNGE::objeto) 
         entrada.objeto->visualizarGL();
      else if (entrada.tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entrada.matriz);
      else if(entrada.tipo == TipoEntNGE::material)
         aplicacionIG->pila_materiales->activar(entrada.material);
   }
   
   cauce->popMM();

   if(tieneColor())
      cauce->popColor();

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ......
   if(aplicacionIG->iluminacion) {
      aplicacionIG->pila_materiales->pop();
   }

}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   cauce->pushMM();

   for (EntradaNGE entrada: entradas) {
      if( entrada.tipo == TipoEntNGE::objeto) 
         entrada.objeto->visualizarGeomGL();
      else if (entrada.tipo == TipoEntNGE::transformacion)
         cauce->compMM(*entrada.matriz);
   }

   cauce->popMM();
}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......
   cauce->pushMM();
   for(int i = 0; i < entradas.size(); i++ ){
      if(entradas[i].tipo == TipoEntNGE::objeto) {
         entradas[i].objeto->visualizarNormalesGL();
      } else if(entradas[i].tipo == TipoEntNGE::transformacion) {
         cauce->compMM(*entradas[i].matriz);
      }
   }
   cauce->popMM();
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   int identificador = leerIdentificador();
   if(identificador != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(identificador));
   }

   cauce->pushMM();
   for(unsigned i = 0; i < entradas.size(); i++) {
      if(entradas[i].tipo == TipoEntNGE::objeto) {
         entradas[i].objeto->visualizarModoSeleccionGL();
      } else if(entradas[i].tipo == TipoEntNGE::transformacion) {
         cauce->compMM(*entradas[i].matriz);
      }
   }

   cauce->popMM();

   if(identificador != -1) {
      cauce->popColor();
   }

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);
   return entradas.size()-1 ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   
   if (indice >= entradas.size()) {
      std::cerr << "Error: indice fuera de rango" << std::endl;
      exit(1);
   } else if (entradas[indice].tipo != TipoEntNGE::transformacion) {
      std::cerr << "Error: la entrada no es de tipo transformacion" << std::endl;
      exit(1);
   } else if (entradas[indice].matriz == nullptr) {
      std::cerr << "Error: el puntero a la matriz es nulo" << std::endl;
      exit(1);
   }
   
   return entradas[indice].matriz ;
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   if (!centro_calculado) {
      vec3 centro = vec3(0.0,0.0,0.0);
      int cont = 0;
      mat4 matrizModelado(1.0f);

      for (unsigned i=0; i<entradas.size(); i++) {
         if (entradas[i].tipo==TipoEntNGE::objeto) {
            entradas[i].objeto->calcularCentroOC();
            vec3 aux = entradas[i].objeto->leerCentroOC();
            centro += vec3(matrizModelado*vec4(entradas[i].objeto->leerCentroOC(), 1.0f));
            cont++;
         } else if (entradas[i].tipo==TipoEntNGE::transformacion) {
            matrizModelado = matrizModelado*(*entradas[i].matriz);
         }
      }
      centro /= cont;
      ponerCentroOC(centro);
      centro_calculado = true;
   }

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   if (ident_busc == leerIdentificador()) {
      *objeto = this;
      centro_wc = leerCentroOC();
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   mat4 matrizmod = mmodelado;

   for(int i=0; i<entradas.size(); i++){
        if(entradas[i].tipo == TipoEntNGE::objeto){
            if(entradas[i].objeto->buscarObjeto(ident_busc, matrizmod, objeto, centro_wc)) return true;
        }
        else if(entradas[i].tipo == TipoEntNGE::transformacion) matrizmod = matrizmod*(*entradas[i].matriz);
   }


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

// -----------------------------------------------------------------------------
GrafoEstrellaX::GrafoEstrellaX(unsigned int n) {
   num_parametros = 1;

   int ident = 1;
   ponerNombre("Grafo Estrella X");

   unsigned ind_rot = agregar(rotate(float(M_PI),glm::vec3{1.0,0.0,0.0}));
   agregar(rotate(float(M_PI/2.0),glm::vec3{0.0,1.0,0.0}));

   NodoGrafoEscena *cono = new NodoGrafoEscena();
   cono->ponerIdentificador(ident);
   ident++;
   cono->agregar(translate(glm::vec3(1.3,0.0,0.0)));
   cono->agregar(rotate(float(3.0*M_PI/2.0),glm::vec3{0.0,0.0,1.0}));
   cono->agregar(scale(glm::vec3(0.14/2.0,0.15/3.0,0.14/2.0)));
   cono->agregar(new Cono(3,10)); // tendrá altura 3
   agregar(cono);

   for(int i = 0; i < n-1; i++) {
      //agregar(translate())
      agregar(rotate(float(2.0*M_PI/n),glm::vec3(0.0,0.0,1.0)));
      agregar(cono);
   }

   // hay que pensarlo como si primero rotaras, luego trasladaras y luego escalaras, pero lo pones en orden inverso
   agregar(scale(glm::vec3(1.3/0.5,1.3/0.5,1.3/0.5)));
   agregar(translate(glm::vec3(-0.5,-0.5,0.0)));
   //agregar(rotate(float(M_PI/2.0), glm::vec3{0.0,1.0,0.0}));
   agregar(new EstrellaZ(n));

   pm_rot = leerPtrMatriz(ind_rot);
   //agregar(cono);
}

void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float t_sec) {
   assert(iParam < leerNumParametros());
   float v;

   switch(iParam) {
      case 0:
         v = 0 + 2*M_PI*2.5*t_sec;
         *pm_rot = rotate(v, glm::vec3(1.0,0.0,0.0));
         break;
   }
}

// -----------------------------------------------------------------------------
GrafoCubos::GrafoCubos() {
   num_parametros = 1;

   int ident = 1;
   ponerNombre("Grafo Cubos");

   NodoGrafoEscena *cubo = new NodoGrafoEscena();
   unsigned ind_rot1 = cubo->agregar(rotate(float(M_PI),glm::vec3{1.0,0.0,0.0}));
   cubo->agregar(translate(glm::vec3(0.75,0.0,0.0)));
   cubo->agregar(scale(glm::vec3(0.75/2.0,0.5/2.0,0.5/2.0)));
   cubo->agregar(new Cubo()); // cada cubo tiene 2 de lado?
   cubo->ponerColor({255.0,255.0,0.0});
   agregar(cubo);

   NodoGrafoEscena *cara = new NodoGrafoEscena();
   cara->agregar(translate(glm::vec3(0.5,-0.5,-0.5)));
   cara->agregar(rotate(float(M_PI/2.0),glm::vec3(0.0,0.0,1.0)));
   //cara->ponerColor({0.0,255.0,255.0});
   cara->agregar(new RejillaY(30,8));
   agregar(cara);

   for(int i = 0; i < 3; i++) {
      agregar(rotate(float(M_PI/2.0), glm::vec3(0.0,0.0,1.0)));
      agregar(cara);
      agregar(cubo);
   }

   agregar(rotate(float(M_PI/2.0),glm::vec3(0.0,1.0,0.0)));
   agregar(cara);
   agregar(cubo);

   agregar(rotate(float(M_PI),glm::vec3(0.0,1.0,0.0)));
   agregar(cara);
   agregar(cubo);

   pm_rot1 = cubo->leerPtrMatriz(ind_rot1);
}

void GrafoCubos::actualizarEstadoParametro( const unsigned iParam, const float t_sec) {
   assert(iParam < leerNumParametros());
   float v;

   switch(iParam) {
      case 0:
         v = 0 + 2*M_PI*0.5*t_sec;
         *pm_rot1 = rotate(v, glm::vec3(1.0,0.0,0.0));
         break;
   }
}

// -----------------------------------------------------------------------------
Caja::Caja() {
   num_parametros = 1;

   int ident = 1;
   ponerNombre("Grafo Caja");

   NodoGrafoEscena *tapa = new NodoGrafoEscena();
   int ind_rot = tapa->agregar(rotate(float(0.0), glm::vec3(-1.0,1.0,0.0)));
   tapa->ponerIdentificador(ident);
   ident++;
   tapa->agregar(translate(glm::vec3(0.0,1.0,-1.0)));
   tapa->agregar(rotate(float(M_PI/2.0),glm::vec3(1.0,0.0,0.0)));
   tapa->agregar(scale(glm::vec3(2.0/1.0,2.0/sqrt(2.0),0.0)));
   tapa->agregar(new MallaTriangulo());
   agregar(tapa);

   NodoGrafoEscena *malla = new NodoGrafoEscena();
   malla->ponerIdentificador(ident);
   ident++;
   malla->agregar(translate(glm::vec3(1.0,-1.0,-1.0)));
   malla->agregar(rotate(float(M_PI/2.0),glm::vec3(0.0,0.0,1.0)));
   //malla->agregar(translate(glm::vec3(1.0,0.0,0.0)));
   malla->agregar(scale(glm::vec3(2.0,2.0,2.0)));
   malla->agregar(new RejillaY(12,10));
   agregar(malla);

   for(int i = 0; i < 3; i++) {
      agregar(rotate(float(M_PI/2.0),glm::vec3(0.0,1.0,0.0)));
      agregar(malla);
   }

   agregar(rotate(float(-M_PI/2.0), glm::vec3(0.0,0.0,1.0)));
   agregar(malla);

   pm_rot1 = tapa->leerPtrMatriz(ind_rot);
}

void Caja::actualizarEstadoParametro( const unsigned iParam, const float t_sec) {
   assert(iParam < leerNumParametros());
   float v;

   switch(iParam) {
      case 0:
         v = -M_PI/4.0 + sin(t_sec * M_PI / 2.0); // Oscilación con el tiempo

         glm::mat4 traslacion_al_origen = translate(glm::vec3(0.0, -1.0, 1.0));
         glm::mat4 rotacion = rotate(v, glm::vec3(1.0, 0.0, 0.0));
         glm::mat4 traslacion_de_vuelta = translate(glm::vec3(0.0, 1.0, -1.0));

         *pm_rot1 = traslacion_de_vuelta * rotacion * traslacion_al_origen;
         break;
   }
}

// -----------------------------------------------------------------------------
Cubos::Cubos() {
   num_parametros = 2;

   int ident = 1;
   ponerNombre("Grafo Cubos");

   NodoGrafoEscena *cubo2 = new NodoGrafoEscena();
   int ind_rot = cubo2->agregar(rotate(float(0.0), glm::vec3(1.0,1.0,1.0)));
   cubo2->ponerIdentificador(ident);
   ident++;
   cubo2->agregar(translate(glm::vec3(0.0,0.25,0.0)));
   cubo2->agregar(scale(glm::vec3(1.0,-0.5/2.0,1.0)));
   cubo2->agregar(new Cubo());
   agregar(cubo2);

   NodoGrafoEscena *cubo1 = new NodoGrafoEscena();
   int ind_esc = cubo1->agregar(scale(glm::vec3(1.0,1.0,1.0)));
   cubo1->ponerIdentificador(ident);
   ident++;
   cubo1->agregar(translate(glm::vec3(0.0,-0.25,0.0)));
   cubo1->agregar(scale(glm::vec3(1.0,-0.5/2.0,1.0)));
   cubo1->agregar(new Cubo());
   agregar(cubo1);

   pm_esc = cubo1->leerPtrMatriz(ind_esc);
   pm_rot = cubo2->leerPtrMatriz(ind_rot);
}

void Cubos::actualizarEstadoParametro( const unsigned iParam, const float t_sec) {
   assert(iParam < leerNumParametros());
   float v;

   switch(iParam) {
      case 1:
         *pm_esc = scale(glm::vec3(1.0,2.0*sin(t_sec*M_PI)*sin(t_sec*M_PI),1.0));
         break;
      case 0:
         v = -M_PI/4.0 + (M_PI/4.0)*sin(t_sec*M_PI/2.0);

         glm::mat4 traslacion_origen = translate(glm::vec3(-1.0,0.0,0.0));
         glm::mat4 rotacion = rotate(v,glm::vec3(0.0,0.0,1.0));
         glm::mat4 traslacion_vuelta = translate(glm::vec3(1.0,0.0,0.0));

         *pm_rot = traslacion_vuelta * rotacion * traslacion_origen;
         break;
   }
}

// *********************************************************************
P1Malla::P1Malla()
:  MallaInd("cubo 8 vétices a color")
{
   vertices =
      {  { -1.0, 0.0, +1.0 }, // 0 -> enfrente izquierda antes del pico
         { -2.0, 0.0, +1.0 }, // 1 -> enfrente izquierda extremo
         { 1.0, 0.0, +1.0 }, // 2 -> enfrente derecha despues del pico
         { 2.0, 0.0, +1.0 }, // 3 -> enfrente derecha extremo
         { -1.0, 0.0, -1.0 }, // 4 -> detras izquierda antes del pico
         { -2.0, 0.0, -1.0 }, // 5 -> detras izquierda extremo
         { +1.0, 0.0, -1.0 }, // 6 -> detras derecha despues del pico
         { +2.0, 0.0, -1.0 }, // 7 -> detras derecga  extremo
         { +0.0, 1.0, -1.0}, // 8 -> detras pico
         { +0.0, 1.0, +1.0}, //9 -> denfrente pico
      } ;



   triangulos =
      {  {0,5,4},{0,1,5},{0,9,4},{4,8,9},{2,6,9},{8,6,9},{2,6,3},{6,3,7}     } ;

    col_ver = {
      {0.3, 0.3, 0.3}, // 0
      {0.3, 0.3, 0.3}, // 1
      {0.3, 0.3, 0.3}, // 2
      {0.3, 0.3, 0.3}, // 3
      {0.3, 0.3, 0.3}, // 4
      {0.3, 0.3, 0.3}, // 5
      {0.3, 0.3, 0.3}, // 6
      {0.3, 0.3, 0.3}, // 7
      {1.0, 1.0, 1.0},
      {1.0, 1.0, 1.0},
   }; 
}

P2MallaTriangulada::P2MallaTriangulada(unsigned n){
   
   vertices = {};
   triangulos = {};

   for (int i = 0; i < n+1; i++) {
      vertices.push_back({-2.0,0.0,-i}); // 0
      vertices.push_back({-1.0,0.0,-i}); // 1
      vertices.push_back({0.0,1.0,-i}); // 2
      vertices.push_back({1.0,0.0,-i}); //3
      vertices.push_back({2.0,0.0,-i}); // 4
   }

   for(int piso = 0; piso < n; piso++) {
      for(int i = 0; i < 4; i++) {
         triangulos.push_back({i+piso*5, i+1+piso*5, i+5*(piso+1)}); // 0, 1, 5 -> 5, 6, 10
         triangulos.push_back({i+5*(piso+1), 1+i+piso*5, 1+i+5*(piso+1)}); // 5, 1, 6 -> 
      }
      // triangulos.push_back({0+piso*5, 1+piso*5, 0+5*(piso+1)}); // 0, 1, 5 -> 5, 6, 10
      // triangulos.push_back({0+5*(piso+1), 1+piso*5, 1+5*(piso+1)}); // 5, 1, 6 -> 
      // triangulos.push_back({1+piso*5, 2+piso*5, 1+5*(piso+1)}); // 1, 2, 6
      // triangulos.push_back({1+5*(piso+1), 2+piso*5, 2+5*(piso+1)}); // 6, 2 ,7
      // triangulos.push_back({2+piso*5, 3+piso*5, 2+5*(piso+1)}); // 2, 3, 7
      // triangulos.push_back({2+5*(piso+1), 3+piso*5, 3+5*(piso+1)}); // 7, 3, 8
      // triangulos.push_back({3+piso*5, 4+piso*5, 3+5*(piso+1)}); // 3, 4, 8
      // triangulos.push_back({3+5*(piso+1), 4+piso*5, 4+5*(piso+1)}); // 8, 4, 9
   }
   
}


NodoCubo24::NodoCubo24(){
   agregar( new Material( new Textura("window-icon.jpg") , 0.5, 0.3, 0.7, 100.0) );
   agregar( new Cubo24() );
}

NodoDiscoP4::NodoDiscoP4(){
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   agregar( new Material( new Textura("cuadricula.jpg") , 0.5, 0.3, 0.7, 100.0) );
   agregar( new MallaDiscoP4() );
}

NodoBeethoven::NodoBeethoven(const std::string& vetas_verticales) {
   agregar(new Material(new TexturaMadera("text-madera.jpg", vetas_verticales), 
                             0.5, 0.3, 0.7, 100.0));
        
   // Agregar la malla PLY del busto de Beethoven
   agregar(new MallaPLY("beethoven.ply"));
}

MiEsferaE1::MiEsferaE1(unsigned i, unsigned j) {
   fila = i+1;
   columna = j+1;
   agregar(new Material(0.5,0.5,1.0,50));
   agregar(new Esfera(20,20));
}

bool MiEsferaE1::cuandoClick(const glm::vec3 & centro_wc) {
   using namespace std;
   cout << "Se ha seleccionado la esfera número " << columna << " de la fila número " << fila << endl;
   return true;
}

GrafoEsferasP5::GrafoEsferasP5() {
   using namespace glm;
   const unsigned 
      n_filas_esferas = 8, 
      n_esferas_x_fila = 5;
   const float e = 0.4/n_esferas_x_fila;

   agregar(scale(vec3(e,e,e)));

   for(unsigned i = 0; i < n_filas_esferas; i++) {
      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena();
      for(unsigned j = 0; j < n_esferas_x_fila; j++) {
         MiEsferaE1 * esfera = new MiEsferaE1(i,j);
         esfera->ponerIdentificador(i*n_esferas_x_fila+j+1);

         fila_esferas->agregar(translate(vec3(2.2,0.0,0.0)));
         fila_esferas->agregar(esfera);
      }
      agregar(fila_esferas);
      agregar(translate(vec3(0.0,0.0,5.0)));
   }
}

MiEsferaE2::MiEsferaE2() {
   ponerColor({1.0,1.0,1.0});
   agregar(new Esfera(20,20));
}

bool MiEsferaE2::cuandoClick(const glm::vec3 & centro_wc) {
   using namespace glm;
   using namespace std;
   if(leerColor() == vec3(1.0,0.0,0.0)){
      cout << "poniendo color blanco" << endl;
      ponerColor(vec3(1.0,1.0,1.0));
   }
   else {
      cout << "poniendo color rojo" << endl;
      ponerColor(vec3(1.0,0.0,0.0));
   }
   return true;
}

GrafoEsferasP5_2::GrafoEsferasP5_2() {
   using namespace glm;
   const unsigned n_filas_esferas = 8, n_esferas_x_fila = 5;
   const float e = 2.5/n_esferas_x_fila;

   agregar(scale(vec3(e,e,e)));

   for(unsigned i = 0; i < n_filas_esferas; i++) {
      NodoGrafoEscena* fila_esferas = new NodoGrafoEscena();
      fila_esferas->agregar(translate(vec3(3.0,0.0,0.0)));

      for(unsigned j = 0; j < n_esferas_x_fila; j++) {
         MiEsferaE2* esfera = new MiEsferaE2();
         
         fila_esferas->agregar(translate(vec3(2.5,0.0,0.0)));
         fila_esferas->agregar(esfera);

         esfera->ponerIdentificador(i*n_esferas_x_fila + j + 1);
      }
      agregar(fila_esferas);
      agregar(rotate(float(2*M_PI/(n_filas_esferas)), vec3(0.0,1.0,0.0)));
   }
}

//___________________EXAMEN DE INTERNET____________________

PiramideRayada::PiramideRayada(){
   // agregar( new Material( new Textura("textura-examen.jpg") , 0.5, 0.3, 0.7, 100.0) );
   agregar(new Material(new TexturaRayas("textura-examen.jpg", "diagonal"), 
                             0.5, 0.3, 0.7, 100.0));
   agregar( new Piramide() );
}

AnilloEXP5::AnilloEXP5(unsigned int n) {
   using namespace glm;
   using namespace std;
   const unsigned n_esferas = n;

   // la esfera tiene radio 1 y su centro esta en el origen
   agregar(translate(vec3(2.0,0.0,0.0)));

   for(int i = 1; i < n_esferas+1; i++) {
      EsferaEXP5* esfera = new EsferaEXP5(n);
      esfera->ponerIdentificador(i);
      agregar(esfera);
      agregar(rotate(float(2.0*M_PI/n_esferas), vec3(0.0,1.0,0.0)));
   }
}

EsferaEXP5::EsferaEXP5(unsigned int n) {
   using namespace std;
   using namespace glm;
   pm_tras = leerPtrMatriz(agregar(translate(vec3(0.0))));
   agregar(new Esfera(20,20));
}

bool EsferaEXP5::cuandoClick(const glm::vec3 & centro_wc) {
   using namespace glm;
   using namespace std;
   cout << "Click" << endl;
   *pm_tras = translate(vec3(0.0,1.0,0.0));
   return true;
}