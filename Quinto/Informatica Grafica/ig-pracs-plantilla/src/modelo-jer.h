// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"

using namespace std;
using namespace glm;

// ---------------------------------------------------------------------
class CabezaLampara : public MallaRevol
{
   public:
   CabezaLampara(
      const int num_verts_per,
      const unsigned nperfiles
   );

};

// ---------------------------------------------------------------------
class AgarreLampara : public MallaInd
{
   public: 
      AgarreLampara(double distancia_interseccion);
};

// ---------------------------------------------------------------------
class Lampara : public NodoGrafoEscena
{
   protected:
      mat4 *pm_tras_palo = nullptr;
      mat4 *pm_rot_cabeza = nullptr;
      mat4 *pm_rot2_cabeza = nullptr;
   public:
      unsigned leerNumParametros() const;
      virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      Lampara();
};

#endif