// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates

#include "grafo-escena.h"
#include "malla-ind.h"
#include "ig-aux.h"
#include "malla-revol.h"
#include "modelo-jer.h"

using namespace std;
using namespace glm;

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY
CabezaLampara::CabezaLampara(
   const int num_verts_per,
   const unsigned nperfiles
) 
{
   // num_verts_per-3 vertices para la base y 3 para el semicono
   int vertices_base = num_verts_per-3;
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < vertices_base; i++) {
      float angulo = 2.0*M_PI*i/(vertices_base);
      glm::vec3 v(cos(angulo), -sin(angulo), 0);
      perfil.push_back(v);
   }
   // intersección base y cono
   glm::vec3 v1(1, 0, 0);
   perfil.push_back(v1);

   // final cono
   glm::vec3 v2(2, 2, 0);
   perfil.push_back(v2);
   
   // intersección cono y eje z
   glm::vec3 v3(0, 2, 0);
   perfil.push_back(v3);
   inicializar(perfil,nperfiles);
}

// -----------------------------------------------------------------------------------------------
AgarreLampara::AgarreLampara(double d)
:  MallaInd( "agarre lampara con d distancia entre cada una de las 4 intersecciones" )
{
    // cada palo de la lampara tiene 0.5 de grosor y 1.5 de longitud
    double grosor = 0.5;
    double longitud = 1.5;
    double h = sqrt(longitud*longitud - ((d - 0.5)/2.0)*((d - 0.5)/2.0));

    vertices = {};
    triangulos = {};
    cc_tt_ver = {};

    vertices.push_back({0,0,0});
    cc_tt_ver.push_back({0.0, 0.0});
    
    vertices.push_back({0.5,0,0});
    cc_tt_ver.push_back({1.0, 0.0});

    for(int i = 0; i <= 4; i++) {
        vertices.push_back({i*d + d*0.5, pow(-1,i)*h,0});
        cc_tt_ver.push_back({(double)i / 4.0, 1.0});
        
        vertices.push_back({i*d + d*0.5 + 0.5, pow(-1,i)*h,0});
        cc_tt_ver.push_back({(double)(i + 0.5) / 4.0, 1.0});
    }

    for(int i = 0; i <= 4; i++) {
        vertices.push_back({i*d + d*0.5, pow(-1,i+1)*h,0});
        cc_tt_ver.push_back({(double)i / 4.0, 0.5});
        
        vertices.push_back({i*d + d*0.5 + 0.5, pow(-1,i+1)*h,0});
        cc_tt_ver.push_back({(double)(i + 0.5) / 4.0, 0.5});
    }

    for(int i = 0; i <= 9; i++) {
        triangulos.push_back({i,i+1,i+2});
    }
    triangulos.push_back({0,1,12});
    triangulos.push_back({1,12,13});
    for(int i = 12; i <= 19; i++) {
        triangulos.push_back({i,i+1,i+2});
    }
}
// -----------------------------------------------------------------------------------------------
Lampara::Lampara ()
{
    unsigned ident = 1;
    ponerNombre("Lampara");
    NodoGrafoEscena *lampara = new NodoGrafoEscena();

    /*LAMPARA: cabeza de lampara*/
    NodoGrafoEscena *cabeza = new NodoGrafoEscena();
    TexturaXY* texturaCabeza = new TexturaXY("texturaLuz.jpg");
    Material* materialCabeza = new Material(texturaCabeza, 0.5, 0.6, 0.5, 50.0);
    materialCabeza->ponerNombre("texturaCabeza");
    cabeza->ponerColor({255.0,255.0,0.0});
    cabeza->ponerIdentificador(ident);
    ident++;
    cabeza->agregar(translate(vec3(-1,0,0)));
    cabeza->agregar(rotate(float(M_PI/2),vec3{0.0,0.0,1.0}));
    unsigned ind_rot_cabeza = cabeza->agregar(rotate(0.0f,vec3{0.0,1.0,0.0}));
    unsigned ind_rot2_cabeza = cabeza->agregar(rotate(0.0f,vec3{1.0,0.0,0.0}));
    cabeza->agregar(materialCabeza);
    cabeza->agregar(new CabezaLampara(20,9));

    /*LAMPARA: agarre de lampara estático*/ 
    NodoGrafoEscena *agarre = new NodoGrafoEscena();
    Textura* texturaAgarre = new TexturaXY("text-madera.jpg");
    Material* materialAgarre = new Material(texturaAgarre, 1.0,0.65, 0.25,50.0);
    materialAgarre->ponerNombre("texturaAgarre");
    agarre->ponerColor({0.0,0.0,0.0});
    agarre->ponerIdentificador(ident);
    ident++;
    //unsigned ind_tras_agarre = agarre->agregar(translate(vec3(0,1,0)));
    agarre->agregar(materialAgarre);
    agarre->agregar(new AgarreLampara(2.0));

    /*LAMPARA: cuerda de lampara*/
    NodoGrafoEscena *cuerda = new NodoGrafoEscena();
    NodoGrafoEscena *palo = new NodoGrafoEscena();
    NodoGrafoEscena *esfera2 = new NodoGrafoEscena();
    NodoGrafoEscena *esfera3 = new NodoGrafoEscena();
    NodoGrafoEscena *esfera4 = new NodoGrafoEscena();
    NodoGrafoEscena *esfera5 = new NodoGrafoEscena();
    NodoGrafoEscena *cono = new NodoGrafoEscena();

    TexturaXY* texturaCuerda = new TexturaXY("texturaCuerda.jpg");
    Material* materialCuerda = new Material(texturaCuerda, 0.7, 0.7, 0.7, 50.0);
    materialCuerda->ponerNombre("texturaCuerda");

    palo->ponerIdentificador(ident);
    ident++;
    palo->agregar(scale(vec3(0.5,0.5,0.5)));
    palo->agregar(translate(vec3(0.0,-4.5,0.0)));
    palo->agregar(materialCuerda);
    palo->agregar(new Palo(10,10));
    esfera2->ponerIdentificador(ident);
    ident++;
    esfera2->agregar(translate(vec3(0.0,-0.5,0.0)));
    esfera2->agregar(scale(vec3(0.1,0.1,0.1)));
    esfera2->agregar(materialCuerda);
    esfera2->agregar(new Esfera(50,100));
    esfera3->ponerIdentificador(ident);
    ident++;
    esfera3->agregar(translate(vec3(0.0,-1.0,0.0)));
    esfera3->agregar(scale(vec3(0.1,0.1,0.1)));
    esfera3->agregar(materialCuerda);
    esfera3->agregar(new Esfera(50,100));
    esfera4->ponerIdentificador(ident);
    ident++;
    esfera4->agregar(translate(vec3(0.0,-1.5,0.0)));
    esfera4->agregar(scale(vec3(0.1,0.1,0.1)));
    esfera4->agregar(materialCuerda);
    esfera4->agregar(new Esfera(50,100));
    esfera5->ponerIdentificador(ident);
    ident++;
    esfera5->agregar(translate(vec3(0.0,-2.0,0.0)));
    esfera5->agregar(scale(vec3(0.1,0.1,0.1)));
    esfera5->agregar(materialCuerda);
    esfera5->agregar(new Esfera(50,100));
    cono->ponerIdentificador(ident);
    ident++;
    cono->agregar(translate(vec3(0.0,-2.5,0.0)));
    cono->agregar(scale(vec3(0.1,0.1,0.1)));
    cono->agregar(new Cono(3,10));

    unsigned ind_tras_palo = cuerda->agregar(translate(vec3(0.0,0.0,0.0)));
    cuerda->agregar(palo);
    cuerda->agregar(esfera2);
    cuerda->agregar(esfera3);
    cuerda->agregar(esfera4);
    cuerda->agregar(esfera5);
    cuerda->agregar(cono);

    /*LAMPARA: cilindro de conexión*/
    NodoGrafoEscena *cilindro = new NodoGrafoEscena();
    cilindro->ponerIdentificador(ident);
    ident++;
    cilindro->agregar(rotate(float(M_PI/2.0),vec3{0.0,1.0,0.0}));
    cilindro->agregar(scale(vec3(0.2,0.2,0.2)));
    cilindro->agregar(translate(vec3(0.0,-1.0,0)));
    cilindro->agregar(new Cilindro(3,10));

    lampara->agregar(cabeza);
    lampara->agregar(agarre);
    lampara->agregar(cuerda);
    lampara->agregar(cilindro);
    pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);
    pm_rot2_cabeza = cabeza->leerPtrMatriz(ind_rot2_cabeza);
    pm_tras_palo = cuerda->leerPtrMatriz(ind_tras_palo);
    agregar(lampara);
}

unsigned Lampara::leerNumParametros() const {
    return 3;
}

void Lampara::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    switch(iParam) {
        case 0:
            *pm_rot_cabeza *= rotate(float(M_PI/500),vec3{0.0,0.0,1.0});
            break;
        case 1:
            *pm_rot2_cabeza *= rotate(float(M_PI/500),vec3{1.0,0.0,0.0});
            break;
        case 2:
            *pm_tras_palo = translate(vec3(0.0,0.1*sin(2*M_PI*t_sec),0.0));
            break;
    }
}