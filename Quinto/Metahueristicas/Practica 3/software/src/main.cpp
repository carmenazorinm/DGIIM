#include <iostream>
#include <problem.h>
#include <random.hpp>
#include <string>
#include <util.h>
#include <graph.h>

// Real problem class
#include "snimp_problem.h"

// Nuevos algoritmos
#include "ES.h"
#include "BMB.h"
#include "ILS.h"
#include "ILS_ES.h"
#include "grasp_nobl.h"
#include "grasp_sibl.h"

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

  ES es;
  BMB bmb;
  ILS ils;
  ILS_ES comb;
  GRASP_NOBL grasp_nobl;
  GRASP_SIBL grasp_sibl;


  vector<pair<string, MH *>> algoritmos = {
    make_pair("ES", &es),
    make_pair("BMB", &bmb),
    make_pair("ILS", &ils),
    make_pair("COMB", &comb),
    make_pair("GRASP_NOBL", &grasp_nobl),
    make_pair("GRASP_SIBL", &grasp_sibl)
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
