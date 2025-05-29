#include "grasp_sibl.h"
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <limits>
#include <iostream>

ResultMH GRASP_SIBL::optimize(Problem *problem, int maxevals)
{
    Snimp *snimp = static_cast<Snimp *>(problem);
    int evals_total = 0;

    tSolution bestSol;
    tFitness bestFitness = std::numeric_limits<tFitness>::lowest();

    for (int i = 0; i < 10 && evals_total < maxevals; ++i)
    {
        // if (i % 1 == 0)
        //     cout << "Eval: " << evals_total << "Mejor fitness GRASP_SIBL: " << bestFitness << endl;
        tSolution sol = construirGreedyAleatorizado(snimp);
        tFitness fit = snimp->fitness(sol);
        ++evals_total;

        // Aplicar BL
        BLsmall bl;
        ResultMH result = bl.optimize(snimp, sol, fit, 100);
        evals_total += result.evaluations;

        if (result.fitness > bestFitness)
        {
            bestFitness = result.fitness;
            bestSol = result.solution;
        }
    }

    return ResultMH(bestSol, bestFitness, evals_total);
}

tSolution GRASP_SIBL::construirGreedyAleatorizado(Snimp *snimp)
{
    vector<int> todos = snimp->nodos();
    size_t m = snimp->getSolutionSize();

    std::random_shuffle(todos.begin(), todos.end());
    tSolution sel = {todos[0]};
    todos.erase(todos.begin());

    while (sel.size() < m)
    {
        unordered_map<int, float> heur;
        float heurMax = -1e9, heurMin = 1e9;

        for (int nodo : todos)
        {
            float h = snimp->heuristic(nodo);
            heur[nodo] = h;
            heurMax = std::max(heurMax, h);
            heurMin = std::min(heurMin, h);
        }

        float umbral = heurMax - ((float)rand() / RAND_MAX) * (heurMax - heurMin);
        vector<int> LRC;
        for (const auto &[nodo, h] : heur)
            if (h >= umbral)
                LRC.push_back(nodo);

        int elegido = LRC[rand() % LRC.size()];
        sel.push_back(elegido);
        todos.erase(std::remove(todos.begin(), todos.end(), elegido), todos.end());
    }

    return sel;
}
