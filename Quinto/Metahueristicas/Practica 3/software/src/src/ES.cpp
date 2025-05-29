#include "ES.h"
#include <iostream>
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>
#include <snimp_problem.h>

using namespace std;

ResultMH ES::optimize(Problem *problem, int maxevals)
{
    srand(time(nullptr));

    Snimp *snimp = static_cast<Snimp *>(problem);
    const int m = snimp->getSolutionSize();
    const int max_vecinos = 5 * m;
    const int max_exitos = max_vecinos / 10;
    const int M = maxevals / max_vecinos;

    const double phi = 0.3;
    const double mu = 0.2;
    const double Tf = 1e-3;

    // creamos la solución inicial
    tSolution s = snimp->createSolution();
    tFitness fs = snimp->fitness(s);
    int evals = 1;

    // calculamos T0
    double T0 = (mu * fs) / (-log(phi));
    if (T0 <= Tf)
        T0 = Tf * 10; // Evitar T0 ≤ Tf

    // calculamos beta
    double beta = (T0 - Tf) / (M * T0 * Tf);
    double T = T0;

    tSolution bestSol = s;
    tFitness bestFitness = fs;

    for (int k = 0; k < M && evals < maxevals; ++k)
    {
        // if (k % 1 == 0)
        //     cout << "Eval: " << evals << "Mejor fitness ES: " << bestFitness << endl;
        int nVecinos = 0;
        int nExitos = 0;

        // condición de enfriamiento L(T)
        while (nVecinos < max_vecinos && nExitos < max_exitos && evals < maxevals)
        {
            // el vecino será de la mutación: coger una posición y ponerle un nuevo valor
            tSolution s_prime = snimp->mutate(s);
            tFitness f_prime = snimp->fitness(s_prime);
            ++evals;
            ++nVecinos;

            double delta = fs - f_prime;

            // delta será negativo si f(s') > f(s)
            if (delta < 0 || ((double)rand() / RAND_MAX) <= exp(-delta / T))
            {
                s = s_prime;
                fs = f_prime;
                ++nExitos;

                if (fs > bestFitness)
                {
                    bestSol = s;
                    bestFitness = fs;
                }
            }
        }

        // enfriamiento (Cauchy modificado)
        T = T / (1.0 + beta * T);

        // si no hay exitos -> parar
        if (nExitos == 0)
            break;
    }

    return ResultMH(bestSol, bestFitness, evals);
}

ResultMH ES::optimize(Problem *problem, const tSolution &current,
                      const tFitness fitness, const int maxevals)
{
    Snimp *snimp = static_cast<Snimp *>(problem);
    const int m = snimp->getSolutionSize();
    const int max_vecinos = 5 * m;
    const int max_exitos = max_vecinos / 10;
    const int M = maxevals / max_vecinos;

    const double phi = 0.3;
    const double mu = 0.2;
    const double Tf = 1e-3;

    tSolution s = current;
    tFitness fs = fitness;

    int evals = 0;

    // Calcular T0 según fórmula
    double T0 = (mu * fs) / (-log(phi));
    if (T0 <= Tf)
        T0 = Tf * 10; // Asegurar que T0 > Tf

    // Calcular beta (enfriamiento Cauchy modificado)
    double beta = (T0 - Tf) / (M * T0 * Tf);
    double T = T0;

    tSolution bestSol = s;
    tFitness bestFitness = fs;

    for (int k = 0; k < M && evals < maxevals; ++k)
    {
        // if(evals %15 == 0) cout << "Eval: " << evals << "Mejor fitness ES: " << bestFitness << endl;
        int nVecinos = 0;
        int nExitos = 0;

        while (nVecinos < max_vecinos && nExitos < max_exitos && evals < maxevals)
        {
            tSolution s_prime = snimp->mutate(s);
            tFitness f_prime = snimp->fitness(s_prime);
            ++evals;
            ++nVecinos;

            double delta = fs - f_prime;

            if (delta < 0 || ((double)rand() / RAND_MAX) <= exp(-delta / T))
            {
                s = s_prime;
                fs = f_prime;
                ++nExitos;

                if (fs > bestFitness)
                {
                    bestSol = s;
                    bestFitness = fs;
                }
            }
        }

        T = T / (1.0 + beta * T);
        if (nExitos == 0)
            break;
    }

    return ResultMH(bestSol, bestFitness, evals);
}
