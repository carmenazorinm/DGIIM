#include "brutesearch.h"
#include <cassert>
#include <iostream>
#include <util.h>
#include <snimp_problem.h>

using namespace std;

ResultMH BruteSearch::optimize(Problem *problem, const int maxevals) {
  
  assert(maxevals > 0);
  Snimp *snimp = dynamic_cast<Snimp *>(problem);

  tSolution solution = snimp->createSolution();
  tFitness fitness = snimp->fitness(solution);
  tSolution bestSolution = solution;
  tFitness bestFitness = fitness;
  int evals = 0;

  while(bestFitness > fitness) {
    solution = bestSolution;
    fitness = bestFitness;
    for (int i = 0; i < snimp->getSolutionSize(); i++) {
      for(int nodo_cambio: snimp->nodos()) {
        if(solution[i] != nodo_cambio) {
          solution[i] = nodo_cambio;
          fitness = snimp->fitness(solution);
          evals++;
          if(fitness > bestFitness) {
            bestSolution = solution;
            bestFitness = fitness;
          }
          if(evals >= maxevals) break;
        }
      }
      if(evals >= maxevals) break;
    }
    if(evals >= maxevals) break;
  }

  return ResultMH(bestSolution, bestFitness, maxevals);
}
