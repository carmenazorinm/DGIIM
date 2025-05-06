#include <cassert>
#include <greedy.h>
#include <iostream>
#include <vector>
#include <snimp_problem.h>
#include <map>

using namespace std;

template <class T> void print_vector(string name, const vector<T> &sol) {
  cout << name << ": ";

  for (auto elem : sol) {
    cout << elem << ", ";
  }
  cout << endl;
}

/**
 * Create random solutions until maxevals has been achieved, and returns the
 * best one.
 *
 * @param problem The problem to be optimized
 * @param maxevals Maximum number of evaluations allowed
 * @return A pair containing the best solution found and its fitness
 */
ResultMH GreedySearch::optimize(Problem *problem, int maxevals) {
  assert(maxevals > 0);


  // casteo del problem a snimp
  Snimp *snimp = dynamic_cast<Snimp *>(problem);
  
  // calculo las heuristicas de cada nodo
  int num_nodos = snimp->getSize();
  map<int,float> heuristics;
  for (int nodo: snimp->nodos()) {
    heuristics[nodo] = snimp->heuristic(nodo);
  }
  
  // encontrar los 10 nodos de mejor heuristica
  vector<int> best;
  float best_fitness = -1;
  for (int i = 0; i < snimp->getSolutionSize(); i++) {
    int best_node = -1;
    float best_node_heuristic = -1;
    for (auto &pair : heuristics) {
      if (pair.second > best_node_heuristic) {
        best_node = pair.first;
        best_node_heuristic = pair.second;
      }
    }
    best.push_back(best_node);
    heuristics.erase(best_node);
  }

  best_fitness = snimp->fitness(best);
  return ResultMH(best, best_fitness, 1);
}
