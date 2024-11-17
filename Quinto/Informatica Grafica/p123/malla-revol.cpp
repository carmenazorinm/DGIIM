// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas creadas por revolución de un perfil (implementación). Clase 'MallaRevol' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
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
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {
         float rotacion =2.0*M_PI*i/(num_copias-1);
         glm::vec3 q(cos(rotacion)*perfil[j][0], perfil[j][1], sin(rotacion)*perfil[j][0]);
         vertices.push_back(q);
      }
   }

   for (int i = 0; i < num_copias-1; i++) {
      for (int j = 0; j < perfil.size()-1; j++) {
         int k = i*perfil.size()+j;
         glm::uvec3 t1(k, k+perfil.size(), k+perfil.size()+1);
         glm::uvec3 t2(k, k+perfil.size()+1, k+1);
         triangulos.push_back(t1);
         triangulos.push_back(t2);
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   LeerVerticesPLY(nombre_arch, vertices);
   inicializar(vertices, nperfiles);

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Cilindro::Cilindro(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // el cilindro tendrá radio 2
   // si queremos cilindro radio r, altura h -> x = r/2, y = i*(h/num_verts_per)
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; i++) {
      glm::vec3 v(1,i,0);
      perfil.push_back(v);
   }
   inicializar(perfil,nperfiles);

   for(int i=0; i < vertices.size(); i++) {
      col_ver.push_back(glm::vec3({255.0/255.0,95.0/255.0,32.0/255.0}));
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Cono::Cono(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // si quisiera altura h y radio r -> y = h - x*(h/r) con la x dando pasos de distancia (r-0)/(num_verts_per-1)
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; i++) {
      glm::vec3 v(2.0*i/(num_verts_per-1), num_verts_per-1.0*num_verts_per*i/(num_verts_per-1), 0);
      perfil.push_back(v);
   }
   inicializar(perfil,nperfiles);

   for(int i=0; i < vertices.size(); i++) {
      col_ver.push_back(glm::vec3({239.0/255.0,184.0/255.0,16.0/255.0}));
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Esfera::Esfera(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // la esfera tendrá radio 1. 
   // Si quisiera radio r, multiplicar las coord por r
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; i++) {
      float angulo = 2.0*M_PI*i/(num_verts_per);
      glm::vec3 v(cos(angulo), sin(angulo), 0);
      perfil.push_back(v);
   }
   inicializar(perfil,nperfiles);

   for(int i=0; i < vertices.size(); i++) {
      col_ver.push_back(glm::vec3({239.0/255.0,184.0/255.0,16.0/255.0}));
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Palo::Palo(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // el palo tendrá radio 0.5
   // si queremos cilindro radio r, altura h -> x = r/2, y = i*(h/num_verts_per)
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; i++) {
      glm::vec3 v(0.05,i*(5.0/num_verts_per),0);
      perfil.push_back(v);
   }

   inicializar(perfil,nperfiles);

   for(int i=0; i < vertices.size(); i++) {
      col_ver.push_back(glm::vec3({149.0/255.0,95.0/255.0,32.0/255.0}));
   }
}



