#include <cassert>
#include <randomsearch.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Create random solutions until maxevals has been achieved, and returns the
 * best one.
 *
 * @param problem The problem to be optimized
 * @param maxevals Maximum number of evaluations allowed
 * @return A pair containing the best solution found and its fitness
 */
ResultMH RandomSearch::optimize(Problem *problem, int maxevals) {
  assert(maxevals > 0);
  tSolution best;
  float best_fitness = -1;

  //cout << "Fitness Random Search: ";
  for (int i = 0; i < maxevals; i++) {
    tSolution solution = problem->createSolution();
    
    float fitness = problem->fitness(solution);
    // cout << "------ Fitness: " << fitness << endl;

    if (fitness > best_fitness || best_fitness < 0) {
      best = solution;
      best_fitness = fitness;
    }

    // if (i % 100 == 0) {
    //   cout << fitness << " ";
    // }
  }

  return ResultMH(best, best_fitness, maxevals);
}
