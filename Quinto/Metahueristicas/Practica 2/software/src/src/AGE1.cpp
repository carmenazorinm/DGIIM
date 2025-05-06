#include "AGE1.h"
#include <iostream>
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>
#include <snimp_problem.h>

using namespace std;

ResultMH AGE_conorden::optimize(Problem *problem, int maxevals) {
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

    // Buscamos la mejor solucion inicial
    for (int i = 1; i < popSize; ++i) {
        if (fitnesses[i] > bestFit) {
            bestFit = fitnesses[i];
            bestSol = poblacion[i];
        }
    }

    while (evals < maxevals) {
        //if(evals %40 == 0) cout << "Eval: " << evals << "Mejor fitness AGE_conorden: " << bestFit << endl;

        // Seleccion de 2 padres por torneo k=3
        vector<tSolution> padres;
        for (int i = 0; i < 2; ++i) {
            int i1 = Random::get(0, popSize - 1);
            int i2 = Random::get(0, popSize - 1);
            int i3 = Random::get(0, popSize - 1);

            int best = (fitnesses[i1] > fitnesses[i2]) ? i1 : i2;
            best = (fitnesses[best] > fitnesses[i3]) ? best : i3;
            padres.push_back(poblacion[best]);
        }

        // Cruce con orden (Pc = 1 en AGE)
        auto [h1, h2] = dynamic_cast<Snimp*>(problem)->crossoverOrden(padres[0], padres[1]);

        // Mutacion con Pm
        if (Random::get<double>(0.0, 1.0) < Pm) {
            h1 = dynamic_cast<Snimp*>(problem)->mutate(h1);
        }
        if (Random::get<double>(0.0, 1.0) < Pm) {
            h2 = dynamic_cast<Snimp*>(problem)->mutate(h2);
        }

        // Evaluar hijos
        float fit1 = problem->fitness(h1); 
        evals++;
        float fit2 = problem->fitness(h2); 
        evals++;

        tSolution mejorHijo = (fit1 > fit2) ? h1 : h2;
        float fitMejorHijo = max(fit1, fit2);

        // Sustituir el peor si el hijo es mejor 
        auto itWorst = min_element(fitnesses.begin(), fitnesses.end()); // es un iterador
        int idxWorst = distance(fitnesses.begin(), itWorst);

        if (fitMejorHijo > *itWorst) {
            poblacion[idxWorst] = mejorHijo;
            fitnesses[idxWorst] = fitMejorHijo;
        }

        // Buscamos la mejor solucion
        if (fitMejorHijo > bestFit) {
            bestFit = fitMejorHijo;
            bestSol = mejorHijo;
        }
    }

    return ResultMH(bestSol, bestFit, evals);
}
