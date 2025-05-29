#include "BMB.h"
#include "blsmall.h"
#include <iostream>
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>
#include <snimp_problem.h>

using namespace std;

ResultMH BMB::optimize(Problem *problem, int maxevals)
{
    const int num_reinicios = 10;
    int evals_total = 0;

    tSolution bestSol;
    tFitness bestFitness = std::numeric_limits<tFitness>::lowest(); // el fitness más bajo posible

    for (int i = 0; i < num_reinicios && evals_total < maxevals; ++i)
    {
        // if (i % 1 == 0 || i % 10 == 0)
        //     cout << "Eval: " << evals_total << "Mejor fitness BMB: " << bestFitness << endl;
        // generar solución aleatoria inicial
        tSolution s0 = problem->createSolution();

        // aplicar BL a esa solución (máx 100 evaluaciones por reinicio)
        BLsmall bl;
        ResultMH result = bl.optimize(problem, s0, problem->fitness(s0), 100);

        evals_total += result.evaluations;

        if (result.fitness > bestFitness)
        {
            bestFitness = result.fitness;
            bestSol = result.solution;
        }
    }

    return ResultMH(bestSol, bestFitness, evals_total);
}