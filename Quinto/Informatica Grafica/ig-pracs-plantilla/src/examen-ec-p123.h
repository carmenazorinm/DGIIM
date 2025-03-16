// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "grafo-escena.h"
#include "malla-ind.h"

using namespace std;
using namespace glm;

class Ejercicio1 : public MallaInd {
    public: 
        Ejercicio1();
};

class Ejercicio2 : public MallaInd {
    public:
        Ejercicio2(int n);
};

class Ejercicio3 : public NodoGrafoEscena {
    protected:
        glm::mat4 *pm_rot, *pm_esc = nullptr;
       unsigned num_parametros;
   public:
      unsigned leerNumParametros() const { return num_parametros; };
      void actualizarEstadoParametro( const unsigned iParam, const float t_sec);
      Ejercicio3(float w, float h);
};


#endif
