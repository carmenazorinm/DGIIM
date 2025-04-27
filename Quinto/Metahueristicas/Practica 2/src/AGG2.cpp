#include "AGG2.h"
#include "snimp_problem.h"
#include <random.hpp>
#include <algorithm>
#include <numeric>
#include <set>
#include <chrono>

using namespace std;

ResultMH AGG_conorden::optimize(Problem *problem, int maxevals) {
    const int popSize = 30;
    const double Pc = 0.7;
    const double Pm = 0.1;
    int evals = 0;

    const int cromSize = problem->getSize();

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
        // Seleccion por torneo k=3
        vector<tSolution> padres;
        for (int i = 0; i < popSize; ++i) {
            int i1 = Random::get(0, popSize - 1);
            int i2 = Random::get(0, popSize - 1);
            int i3 = Random::get(0, popSize - 1);

            int best = (fitnesses[i1] > fitnesses[i2]) ? i1 : i2;
            best = (fitnesses[best] > fitnesses[i3]) ? best : i3;
            padres.push_back(poblacion[best]);
        }

        // Numero esperado de cruces
        int numCruces = ceil(Pc * (popSize / 2.0));
        vector<tSolution> hijos;

        for (int i = 0; i < popSize; i += 2) {
            if (i / 2 < numCruces) {
                auto [h1, h2] = dynamic_cast<Snimp*>(problem)->crossoverOrden(padres[i], padres[i + 1]);
                hijos.push_back(h1);
                hijos.push_back(h2);
            } else {
                hijos.push_back(padres[i]);
                hijos.push_back(padres[i + 1]);
            }
        }

        // Mutacion (número esperado de individuos a mutar)
        int numMutaciones = round(Pm * popSize);
        set<int> indices;
        while (indices.size() < numMutaciones) {
            indices.insert(Random::get(0, popSize - 1));
        }

        for (int i : indices) {
            hijos[i] = dynamic_cast<Snimp*>(problem)->mutate(hijos[i]);
        }

        // Evaluar nueva poblacion
        vector<float> newFitnesses;
        for (auto &h : hijos) {
            float fit = problem->fitness(h);
            newFitnesses.push_back(fit);
            evals++;
            if (fit > bestFit) {
                bestFit = fit;
                bestSol = h;
            }
        }

        // Elitismo: insertar mejor en lugar del peor si no está
        auto itWorst = min_element(newFitnesses.begin(), newFitnesses.end());
        int idxWorst = distance(newFitnesses.begin(), itWorst);
        hijos[idxWorst] = bestSol;
        newFitnesses[idxWorst] = bestFit;

        poblacion = hijos;
        fitnesses = newFitnesses;
    }

    return ResultMH(bestSol, bestFit, evals);
}