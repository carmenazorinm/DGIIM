// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Funciones y método de gestión de la selección (implementación). 
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las funciones de gestión de identificadores
// **   + FijarColVertsIdent
// **   + LeerIdentEnPixel
// ** Implementación del método de 'AplicacionIG'
// **   + Seleccion 
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
#include "camara.h"
#include "fbo.h"
#include "seleccion.h"
#include "grafo-escena.h"



// ----------------------------------------------------------------------------------
// calcula un color usando un identificador entero no negativo

glm::vec4 ColorDesdeIdent( const int ident )  // 0 ≤ ident < 2^24
{
   using namespace glm ;
   assert( 0 <= ident );

   // decodificar: extraer los tres bytes menos significativos del valor entero.
   const unsigned char
      byteR = ( ident            ) % 0x100U,  // rojo  = byte menos significativo
      byteG = ( ident / 0x100U   ) % 0x100U,  // verde = byte intermedio
      byteB = ( ident / 0x10000U ) % 0x100U;  // azul  = byte más significativo

   //log(" RGB == ",(unsigned int)byteR,", ",(unsigned int)byteG,", ", (unsigned int)byteB);

   // Fijar el color normalizando desde [0..255] hacia [0..1]
   // (otra posibilidad es pasarle los bytes directamente a 'glVertexAttrib4Nubv')
   // (ver: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttrib.xhtml)

   return vec4 { float(byteR)/255.0f, float(byteG)/255.0f, float(byteB)/255.0f, 1.0f };
}

// ----------------------------------------------------------------------------------
// leer un identificador entero codificado en el color de un pixel en el
// framebuffer activo actualmente

int LeerIdentEnPixel( int xpix, int ypix )
{
   // COMPLETAR: práctica 5: leer el identificador codificado en el color del pixel (x,y)
   // .....(sustituir el 'return 0' por lo que corresponda)
   unsigned char bytes[3];

   glReadPixels(xpix,ypix, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void*)bytes);

   return int(bytes[0]) + ( int(0x100U)*int(bytes[1]) ) + ( int(0x10000U)*int(bytes[2]) );

}

// -------------------------------------------------------------------------------
// Función principal de selección, se llama al hacer click con el botón izquierdo
//
// (x,y) = posición donde se ha hecho click en coordenadas del sistema de ventanas (enteras)
//
// devuelve: true si se ha seleccionado algún objeto, false si no


bool AplicacionIG::seleccion( int x, int y ) 
{
   
   using namespace std ;
   using namespace glm ;

   // comprobar algunas precondiciones
   assert( 0 < ventana_tam_x );
   assert( 0 < ventana_tam_y );
   Escena * escena = escenas[ind_escena_act] ;
   assert( escena != nullptr );

   // COMPLETAR Práctica 5: ejecutar 'cuandoClick' para el objeto en el pixel (x,y), si hay alguno.
   //
   // Se deben completar cada uno de estos pasos(del 1 al 6):  
   
   // (1) Crear y activar el objeto framebuffer (puntero 'fbo' de la clase 'AplicacionIG') 
   //      * Si el puntero 'fbo' es nulo, crear el framebuffer usando su constructor (necesita 
   //        el tamaño actual de la ventana en dos parámetros)
   //      * Activar el framebuffer, con su método 'activar'.
   if(aplicacionIG->fbo == nullptr){
      aplicacionIG->fbo = new Framebuffer(ventana_tam_x, ventana_tam_y);
   }
   aplicacionIG->fbo->activar(ventana_tam_x, ventana_tam_y);


   // (2) Visualizar la escena actual en modo selección. Se usará el método 'visualizarGL_Seleccion' de la clae 'Escena'
   escena->visualizarGL_Seleccion();


   // (3) Leer el identificador del pixel en las coordenadas (x,y), se usa 'LeerIdentEnPixel'.
   int identificador = LeerIdentEnPixel(x,y);


   // (4) Desactivar el FBO (vuelve a activar el FBO por defecto, con nombre '0'), 
   //     se usa el método 'desactivar' del FBO
   aplicacionIG->fbo->desactivar();


   // (5) Si el identificador del pixel es 0, imprimir mensaje y terminar (devolver 'false')
   if(identificador==0) {
      cout << "El identificador del objeto en el píxel es 0." << endl;
      return false;
   }


   // (6) Buscar el identificdor en el objeto raiz de la escena y ejecutar 'cuandoClick',
   //     Para ello se dan estos pasos:
   //
   //     * Recuperar el objeto raiz de la escena
   //     * Buscar el identificador leído en el objeto raiz (usar método 'buscarObjeto' de 'Objeto3D')
   //     * Si se encuentra, ejecutar el método 'cuandoClick' del objeto encontrado y devolver 
   //       el mismo valor devuelto por 'cuandoClick'.
   Objeto3D* raiz = escena->objetoActual();
   Objeto3D* objeto = nullptr;
   vec3 centro_wc = vec3(0.0f);
   if(raiz->buscarObjeto(identificador, mat4(1.0f), &objeto, centro_wc)){
      return objeto->cuandoClick(centro_wc);
   }


   // si el flujo de control llega aquí, es que no se encuentra ese identificador, devolver false:
   cout << "El identificador del objeto en el pixel no se encuentra en el objeto raíz que se está visualizando." << endl ;
   return false;
}
