#include "AGE2.h"
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>
#include <snimp_problem.h>

using namespace std;

ResultMH AGE_sinorden::optimize(Problem *problem, int maxevals) {
    const int popSize = 30;
    const double Pm = 0.1;
    int evals = 0;

    // Inicializar poblacion
    vector<tSolution> poblacion;
    vector<float> fitnesses;
    for (int i = 0; i < popSize; ++i) {
        tSolution sol = problem->createSolution();
        float fit = problem->fitness(sol);
        evals++;
        poblacion.push_back(sol);
        fitnesses.push_back(fit);
    }

    tSolution bestSol = poblacion[0];
    float bestFit = fitnesses[0];

    while (evals < maxevals) {
        // Seleccion de 2 padres por torneo k=3
        auto torneo = [&](const vector<float>& fits) -> int {
            int i1 = Random::get(0, popSize - 1);
            int i2 = Random::get(0, popSize - 1);
            int i3 = Random::get(0, popSize - 1);
            int best = (fits[i1] > fits[i2]) ? i1 : i2;
            return (fits[best] > fits[i3]) ? best : i3;
        };

        int idx1 = torneo(fitnesses);
        int idx2 = torneo(fitnesses);

        // Cruce en dos puntos sin orden con reparacion (Pc = 1 en AGE)
        auto [h1, h2] = dynamic_cast<Snimp*>(problem)->crossover2Puntos(poblacion[idx1], poblacion[idx2]);

        // Mutacion con Pm
        if (Random::get(0.0, 1.0) < Pm) {
            h1 = dynamic_cast<Snimp*>(problem)->mutate(h1);
        }
        if (Random::get(0.0, 1.0) < Pm) {
            h2 = dynamic_cast<Snimp*>(problem)->mutate(h2);
        }

        // Evaluar hijos
        float fit1 = problem->fitness(h1); evals++;
        float fit2 = problem->fitness(h2); evals++;

        tSolution mejorHijo = (fit1 > fit2) ? h1 : h2;
        float fitMejorHijo = max(fit1, fit2);

        // Sustituir el peor si el hijo es mejor
        auto itWorst = min_element(fitnesses.begin(), fitnesses.end());
        int idxWorst = distance(fitnesses.begin(), itWorst);

        if (fitMejorHijo > *itWorst) {
            poblacion[idxWorst] = mejorHijo;
            fitnesses[idxWorst] = fitMejorHijo;
        }

        if (fitMejorHijo > bestFit) {
            bestFit = fitMejorHijo;
            bestSol = mejorHijo;
        }
    }

    return ResultMH(bestSol, bestFit, evals);
}
