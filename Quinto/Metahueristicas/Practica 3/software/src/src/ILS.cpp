#include "ILS.h"
#include "blsmall.h"
#include <iostream>
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>
#include <snimp_problem.h>

using namespace std;

ResultMH ILS::optimize(Problem *problem, int maxevals)
{
    Snimp *snimp = static_cast<Snimp *>(problem);
    int evals_total = 0;

    //crear solución inicial y evaluarla
    tSolution s0 = snimp->createSolution();
    tFitness f0 = snimp->fitness(s0);
    evals_total++;

    // aplicar BL a la solución inicial
    BLsmall bl;
    ResultMH result = bl.optimize(snimp, s0, f0, 100);
    evals_total += result.evaluations;

    tSolution bestSol = result.solution;
    tFitness bestFitness = result.fitness;

    // Repetir 9 veces: mutar y aplicar BL
    for (int i = 0; i < 9 && evals_total < maxevals; ++i)
    {
        // if (i % 1 == 0)
        //     cout << "Eval: " << evals_total << "Mejor fitness ILS: " << bestFitness << endl;
        // mutamos la mejor solución encontrada
        tSolution mutated = snimp->mutate(bestSol,0.2); // cambiamos el 20% de los valores

        // evaluar y aplicar BL
        ResultMH newResult = bl.optimize(snimp, mutated, snimp->fitness(mutated), 100);
        evals_total += newResult.evaluations + 1;

        // siempre se aplica mutación sobre la mejor solución (criterio del mejor)
        if (newResult.fitness > bestFitness)
        {
            bestFitness = newResult.fitness;
            bestSol = newResult.solution;
        }
    }

    return ResultMH(bestSol, bestFitness, evals_total);
}