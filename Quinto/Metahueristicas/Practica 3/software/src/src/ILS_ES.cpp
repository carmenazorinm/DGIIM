#pragma once
#include "mh.h"
#include "snimp_problem.h"
#include "ILS_ES.h"
#include "ES.h"
#include <iostream>

ResultMH ILS_ES::optimize(Problem *problem, int maxevals)
{
    Snimp *snimp = static_cast<Snimp *>(problem);
    int evals_total = 0;

    // crear solución inicial y evaluar
    tSolution s0 = snimp->createSolution();
    tFitness f0 = snimp->fitness(s0);
    evals_total++;

    // aplicar ES sobre la solución inicial
    ES es;
    ResultMH result = es.optimize(snimp, s0, f0, 100);
    evals_total += result.evaluations;

    tSolution bestSol = result.solution;
    tFitness bestFitness = result.fitness;

    // repetir 9 veces: mutar y aplicar ES
    for (int i = 0; i < 9 && evals_total < maxevals; ++i)
    {
        // if (i % 1 == 0)
        //     cout << "Eval: " << evals_total << "Mejor fitness COMB: " << bestFitness << endl;
        // mutar la mejor solución encontrada
        tSolution mutated = snimp->mutate(bestSol,0.2);
        tFitness fmut = snimp->fitness(mutated);
        evals_total++;

        // aplicar ES sobre la mutada
        ResultMH resultMut = es.optimize(snimp, mutated, fmut, 100);
        evals_total += resultMut.evaluations;

        // criterio del mejor
        if (resultMut.fitness > bestFitness)
        {
            bestFitness = resultMut.fitness;
            bestSol = resultMut.solution;
        }
    }

    return ResultMH(bestSol, bestFitness, evals_total);
}
