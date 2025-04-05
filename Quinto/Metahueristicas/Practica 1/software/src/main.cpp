#include <iostream>
#include <problem.h>
#include <random.hpp>
#include <string>
#include <util.h>
#include <graph.h>
// Real problem class
#include "pincrem.h"
#include "snimp_problem.h"

// All all algorithms
#include "brutesearch.h"
#include "greedy.h"
#include "randomsearch.h"
#include "lsall.h"
#include "blsmall.h"

using namespace std;
int main(int argc, char *argv[]) {
  //cout << "Hello, World!" << endl;

  string filename = "../datos/ca-GrQc.txt";
  // Read the graph from the file
  Graph graph = readGraphFromFile(filename);
  // graph.printGraph();

  long int seed;

  // Seed the random number generator
  if (argc == 1) {
    // Use a fixed seed for reproducibility
    seed = 42;
  } else {
    seed = atoi(argv[1]);
  }

  // Create the algorithms
  RandomSearch ralg = RandomSearch();
  LSall rlsall = LSall();
  BLsmall rblsmall = BLsmall();

  GreedySearch rgreedy = GreedySearch();
  // MH *mh = &rgreedy;
  // Create the specific problem
  Snimp rproblem = Snimp(graph.adjList);

  // Solve using evaluations
  vector<pair<string, MH *>> algoritmos = {
    make_pair("RandomSearch", &ralg),
    make_pair("Greedy", &rgreedy),
    make_pair("LSall", &rlsall),
    make_pair("BLsmall", &rblsmall)
  };

  Problem *problem = dynamic_cast<Problem *>(&rproblem);

  for(int ej = 0; ej < 5; ej++) {
    // cambiar la semilla
    seed = seed + 1;
    for (int i = 0; i < algoritmos.size(); i++) {
      Random::seed(seed);
      cout << algoritmos[i].first << endl;
      MH *mh = algoritmos[i].second;
      // calcular tiempo
      auto start = std::chrono::high_resolution_clock::now();
      ResultMH result = mh->optimize(problem, 1000);
      auto finish = std::chrono::high_resolution_clock::now();
      cout << "Best solution: " << result.solution << endl;
      cout << "Best fitness: " << result.fitness << endl;
      cout << "Evaluations: " << result.evaluations << endl;
      cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms" << endl;
    }
  }

  return 0;
}