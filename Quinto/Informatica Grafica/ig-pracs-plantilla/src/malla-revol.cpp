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
   using namespace std;

   // Practica 4
   vector<vec3> normales_m;

   //aristas
   for(int i = 0; i < perfil.size(); i++) {
      float v_1 = (perfil[i+1] -perfil[i])[0];
      float v_2 = (perfil[i+1]-perfil[i])[1];
      vec3 m_i(vec3(v_2, -v_1, 0.0f));

      if(length(m_i) != 0.0) {
         m_i = normalize(m_i);
      }
      normales_m.push_back(m_i);
   }

   // vertices
   vector<vec3> normales_n;
   normales_n.push_back(normales_m[0]);
   for(int i = 1; i < perfil.size()-1; i++) {
      normales_n.push_back(normalize(normales_m[i-1]+normales_m[i]));
   }
   normales_n.push_back(normales_m[perfil.size()-2]);

   //vectores d y t
   vector<float> d, t, sumas_parciales;
   float suma_total;

   for(int i = 0; i < perfil.size()-1; i++) {
      d.push_back(sqrt(length(perfil[i+1]-perfil[i])));
   }

   sumas_parciales.push_back(0.0f);
   for(int i = 0; i < perfil.size(); i++) {
      sumas_parciales.push_back(sumas_parciales[i-1]+d[i-1]);
   }

   suma_total = sumas_parciales[perfil.size()-1];
   t.push_back(0.0f);
   for(int i = 0; i < perfil.size(); i++) {
      t.push_back(sumas_parciales[i]/suma_total);
   }
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < perfil.size(); j++) {
         float rotacion =2.0*M_PI*i/(num_copias-1);
         glm::vec3 q(cos(rotacion)*perfil[j][0], perfil[j][1], sin(rotacion)*perfil[j][0]);
         vertices.push_back(q);

         // practica 4
         vec3 aux = vec3(normales_n[j][0]*cos(rotacion), normales_n[j][1], -normales_n[j][0]*sin(rotacion));
         if(length(aux) != 0.0) {
            normalize(aux);
         }
         nor_ver.push_back(aux);
         cc_tt_ver.push_back({float(i)/(num_copias-1),1-t[j]});
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
   std::vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Cilindro::Cilindro(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // el cilindro tendrá radio 2 y altura num_verts_per-1?
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
   // tiene altura num_verts_per y radio 2
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

   /*
   std::vector<glm::vec3> perfil;
   for (int i=0; i<num_verts_per; i++){
      perfil.push_back({cos(i*(M_PI*2.0/(num_verts_per-1))), sin(i*(M_PI*2.0/(num_verts_per-1))), 0.0});
   }

   inicializar(perfil, nperfiles);
   */
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
Palo::Palo(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // el palo tendrá radio 0.5 y altura 5*(num_verts_per-1)/num_verts_per
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


