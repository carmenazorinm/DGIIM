// Nombre: Carmen, Apellidos: Azorín Martí, Titulación: GIM.
// email: carmenazorin@correo.ugr.es, DNI: 48768328W

// Carmen Azorín Martí
// InfoMates

#include "examen-ec-p123.h"

using namespace std;
using namespace glm;

Ejercicio1::Ejercicio1() 
: MallaInd("Ejercicio 1 p123")
{
    vertices = {};
    triangulos = {};
    col_ver = {};

    vertices.push_back({0.0,0.0,0.0});
    for(int i  = 2; i<=6; i++) {
        vertices.push_back({i,0.0,0.0});
    }
    vertices.push_back({0.0,0.0,-1.0});
    vertices.push_back({2.0,0.0,-1.0});
    for(int i  = 3; i<=6; i++) {
        vertices.push_back({i,1.0,-1.0});
    }

    triangulos = {{0,1,6},{1,6,7},{1,2,7},{2,7,8},{2,3,8},{3,8,9},{3,4,9},{4,9,10},{4,5,10},{5,10,11}};

    col_ver = {{0.3,0.3,0.3},{0.3,0.3,0.3}, {1,1,1},{1,1,1},{1,1,1},{1,1,1},
    {0.3,0.3,0.3},{0.3,0.3,0.3}, {1,1,1},{1,1,1},{1,1,1},{1,1,1}};

}

Ejercicio2::Ejercicio2(int n) 
{
    vertices = {};
    triangulos = {};
    col_ver = {};

    vertices.push_back({0.0,0.0,0.0}); // 0
    col_ver.push_back({0.3,0.3,0.3});
    vertices.push_back({0.0,0.0,-1.0}); // 1
    col_ver.push_back({0.3,0.3,0.3});
    for(int r = 0; r < n; r++) {
        //vertices.push_back({0*cos(2.0*M_PI*r/n),0*sin(2.0*M_PI*r/n),0.0}); // CON 12 VERTICES
        for(int i  = 2; i<=6; i++) {
            vertices.push_back({i*1.0*cos(2.0*M_PI*r/n),i*1.0*sin(2.0*M_PI*r/n),0.0});
            if(i==2)
                col_ver.push_back({0.3,0.3,0.3});
            else   
                col_ver.push_back({1,1,1});
        }
        //vertices.push_back({0*cos(2.0*M_PI*r/n),0*sin(2.0*M_PI*r/n),-1.0}); // CON 12 VERTICES
        vertices.push_back({2.0*cos(2.0*M_PI*r/n),2.0*sin(2.0*M_PI*r/n),-1.0});
        col_ver.push_back({0.3,0.3,0.3});
        for(int i  = 3; i<=6; i++) {
            if(2.0*M_PI*r/n > M_PI/2.0 && 2.0*M_PI*r/n < 3.0*M_PI/2.0)
                vertices.push_back({i*1.0*cos(2.0*M_PI*r/n),-1.0+i*1.0*sin(2.0*M_PI*r/n),-1.0});
            else if(2.0*M_PI*r/n == M_PI/2.0)
                vertices.push_back({-1.0+i*1.0*cos(2.0*M_PI*r/n),i*1.0*sin(2.0*M_PI*r/n),-1.0});
            else if(2.0*M_PI*r/n == 3.0*M_PI/2.0)
                vertices.push_back({1.0+i*1.0*cos(2.0*M_PI*r/n),i*1.0*sin(2.0*M_PI*r/n),-1.0});
            else
                vertices.push_back({i*1.0*cos(2.0*M_PI*r/n),1.0+i*1.0*sin(2.0*M_PI*r/n),-1.0});
            col_ver.push_back({1,1,1});
        }
    }

    for(int r = 0; r < n*10; r+=10) {
        triangulos.push_back({0,1,2+r});
        triangulos.push_back({1,2+r,7+r});
        triangulos.push_back({2+r,3+r,7+r});
        triangulos.push_back({3+r,7+r,8+r});
        triangulos.push_back({3+r,4+r,8+r});
        triangulos.push_back({4+r,8+r,9+r});
        triangulos.push_back({4+r,5+r,9+r});
        triangulos.push_back({5+r,9+r,10+r});
        triangulos.push_back({5+r,6+r,10+r});
        triangulos.push_back({6+r,10+r,11+r});
    }

    /*CON 12 VERTICES
    for(int r = 0; r < n*12; r+=12) {
        triangulos.push_back({0+r,1+r,6+r});
        triangulos.push_back({1+r,6+r,7+r});
        triangulos.push_back({1+r,2+r,7+r});
        triangulos.push_back({2+r,7+r,8+r});
        triangulos.push_back({2+r,3+r,8+r});
        triangulos.push_back({3+r,8+r,9+r});
        triangulos.push_back({3+r,4+r,9+r});
        triangulos.push_back({4+r,9+r,10+r});
        triangulos.push_back({4+r,5+r,10+r});
        triangulos.push_back({5+r,10+r,11+r});
    }*/
}

Ejercicio3::Ejercicio3(float w, float h) {
    num_parametros = 2;

    int ident = 1;
    ponerNombre("Ejercicio 3 p123");

    //el cubo tendrá lado h
    // NodoGrafoEscena *cubo = new NodoGrafoEscena();
    // int id_rot = cubo->agregar(rotate(float(0),vec3(0.0,1.0,0.0)));
    // cubo->ponerIdentificador(ident);
    // ident++;
    // cubo->agregar(translate(vec3(w/2.0-h/2.0,h+h/2.0,0.0)));
    // cubo->agregar(scale(vec3(h/2.0,h/2.0,h/2.0)));
    // cubo->agregar(new Cubo());
    // agregar(cubo);

    // int id_esc = agregar(scale(vec3(1.0,1.0,1.0)));
    // agregar(translate(vec3(0.0,h/2.0,0.0)));
    // agregar(scale(vec3(w/2.0,h/2.0,w/2.0)));
    // agregar(new Cubo());

    // pm_rot = cubo->leerPtrMatriz(id_rot);
    // pm_esc = leerPtrMatriz(id_esc);

    NodoGrafoEscena *cubo = new NodoGrafoEscena();
    cubo->ponerIdentificador(ident);
    ident++;
    cubo->agregar(translate(vec3(w/2.0-0.2/2.0,h+0.2/2.0,0.0)));
    cubo->agregar(scale(vec3(0.2/2.0,0.2/2.0,0.2/2.0)));
    cubo->agregar(new Cubo());
    agregar(cubo);

    NodoGrafoEscena *tablero = new NodoGrafoEscena();
    int id_esc = tablero->agregar(scale(vec3(1.0,1.0,1.0)));
    tablero->ponerIdentificador(ident);
    ident++;
    tablero->agregar(scale(vec3(w/0.2,h/0.2,w/0.2)));
    tablero->agregar(translate(vec3(-w/2.0+0.2/2.0,-h,0.0)));
    tablero->agregar(cubo);
    agregar(tablero);

    int id_rot = cubo->agregar(rotate(float(0),vec3(0.0,1.0,0.0)));
    pm_rot = cubo->leerPtrMatriz(id_rot);
    pm_esc = tablero->leerPtrMatriz(id_esc);
}

void Ejercicio3::actualizarEstadoParametro(const unsigned iParam, const float t_sec) {
    assert(iParam < leerNumParametros());
    float v;

    switch(iParam) {
        case 0:
            v = 0 + 2.0*M_PI*t_sec;
            *pm_rot = rotate(v, vec3(0.0,1.0,0.0));
            break;
        case 1:
            *pm_esc = scale(vec3(1.0,1.0*sin(M_PI*t_sec)*sin(M_PI*t_sec),1.0));
            break;
    }
}