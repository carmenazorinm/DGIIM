#include <iostream>
#include <problem.h>
#include <random.hpp>
#include <string>
#include <util.h>
#include <graph.h>

// Real problem class
#include "snimp_problem.h"

// Nuevos algoritmos
#include "AGG1.h"
#include "AGG2.h"
#include "AGE1.h"
#include "AGE2.h"
#include "AM1.h"
#include "AM2.h"
#include "AM3.h"

using namespace std;

int main(int argc, char *argv[]) {
  string filename = "../datos/ca-GrQc.txt";

  // Leer el grafo desde el fichero
  Graph graph = readGraphFromFile(filename);

  long int seed;
  if (argc == 1) {
    seed = 42;
  } else {
    seed = atoi(argv[1]);
  }

  // Crear el problema
  Snimp rproblem = Snimp(graph.adjList);
  Problem *problem = dynamic_cast<Problem *>(&rproblem);

  // Crear el algoritmo AGG1
  AGG_sinorden agg1;
  // Crear el algoritmo AGG2
  AGG_conorden agg2;
  // Crear el algoritmo AGE_conorden
  AGE_conorden age1;
  // Crear el algoritmo AGE_sinorden
  AGE_sinorden age2;
  // Crear el algoritmo AM1
  AM1 am1;
  // Crear el algoritmo AM2
  AM2 am2;
  // Crear el algoritmo AM3
  AM3 am3;
  vector<pair<string, MH *>> algoritmos = {
    make_pair("AGG_sinorden", &agg1),
    make_pair("AGG_conorden", &agg2),
    make_pair("AGE_sinorden", &age2),
    make_pair("AGE_conorden", &age1),
    make_pair("AM1", &am1),
    make_pair("AM2", &am2),
    make_pair("AM3", &am3)    
  };

  // Ejecutar 5 veces con diferente semilla
  for (int ej = 0; ej < 5; ej++) {
    seed = seed + 1;

    for (auto &[nombre, mh] : algoritmos) {
      Random::seed(seed);
      cout << "Algoritmo: " << nombre << ", Ejecución: " << ej + 1 << ", Semilla: " << seed << endl;

      auto start = std::chrono::high_resolution_clock::now();
      ResultMH result = mh->optimize(problem, 1000);
      auto finish = std::chrono::high_resolution_clock::now();

      cout << "Best solution: " << result.solution << endl;
      cout << "Best fitness: " << result.fitness << endl;
      cout << "Evaluations: " << result.evaluations << endl;
      cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms" << endl;
      cout << "------------------------------" << endl;
    }
  }

  return 0;
}
