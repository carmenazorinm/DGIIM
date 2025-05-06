#include "lsall.h"
#include "blsmall.h"
#include <cassert>
#include <iostream>
#include <util.h>
#include <snimp_problem.h>
#include <algorithm>
#include <random>

using namespace std;

// devuelve un vector con todos los vecinos posibles de la solución actual
vector<pair<int, int>> generarVecinosAleatorios(const tSolution &sol, const vector<int> &noSeleccionados) {
  vector<pair<int, int>> vecinos;
  for (int i = 0; i < (int)sol.size(); i++) {
    for (int j : noSeleccionados) {
      vecinos.emplace_back(i, j);
    }
  }
  random_shuffle(vecinos.begin(), vecinos.end());
  return vecinos;
}

// LSall: Primer-mejor hasta 1000 evaluaciones (o menos si se encuentra un óptimo local)
ResultMH LSall::optimize(Problem *problem, const int maxevals) {
  assert(maxevals > 0);
  Snimp *snimp = dynamic_cast<Snimp *>(problem);
  assert(snimp != nullptr);

  tSolution sel = snimp->createSolution();
  tFitness bestFitness = snimp->fitness(sel);
  int evals = 1;

  bool improvement = true;

  // cout << "Fitness LSall: ";
  while (improvement && evals < maxevals) {
    improvement = false;
    // calcula el conjunto de no seleccionados
    auto nodos_totales = snimp->nodos();
    vector<int> noSel;
    for (int n : nodos_totales) {
      if (find(sel.begin(), sel.end(), n) == sel.end()) {
        noSel.push_back(n);
      }
    }

    // Genera vecinos aleatorios
    auto vecinos = generarVecinosAleatorios(sel, noSel);

    // para cada solución vecina se mira si mejora el fitness
    for (auto [i, j] : vecinos) {
      tSolution nueva = sel;
      nueva[i] = j;
      tFitness fit = snimp->fitness(nueva);
      evals++;

      if (fit > bestFitness) { // mejora
        sel = nueva;
        bestFitness = fit;
        improvement = true;
        break;
      }

      // if (evals%100 == 0) {
      //   cout << fit << " ";
      // }

      if (evals >= maxevals) break;
    }
  }

  return ResultMH(sel, bestFitness, evals);
}

// BLsmall: Igual que LSall, pero para si 20 evaluaciones sin mejora o 1000 evaluaciones
ResultMH BLsmall::optimize(Problem *problem, const int maxevals) {
  assert(maxevals > 0);
  Snimp *snimp = dynamic_cast<Snimp *>(problem);
  assert(snimp != nullptr);

  tSolution sel = snimp->createSolution();
  tFitness bestFitness = snimp->fitness(sel);
  int evals = 1;
  int evalsSinMejora = 0;

  bool improvement = true;

  // cout << "Fitness BLsmall: ";

  while (improvement && evals < maxevals && evalsSinMejora < 20) {
    improvement = false;

    auto nodos_totales = snimp->nodos();
    vector<int> noSel;
    for (int n : nodos_totales) {
      if (find(sel.begin(), sel.end(), n) == sel.end()) {
        noSel.push_back(n);
      }
    }

    auto vecinos = generarVecinosAleatorios(sel, noSel);

    for (auto [i, j] : vecinos) {
      tSolution nueva = sel;
      nueva[i] = j;
      tFitness fit = snimp->fitness(nueva);
      evals++;

      if (fit > bestFitness) {
        sel = nueva;
        bestFitness = fit;
        improvement = true;
        evalsSinMejora = 0; // reset contador
        break;
      } else {
        evalsSinMejora++;
      }

      if (evals >= maxevals || evalsSinMejora >= 20) break;
    }
  }

  return ResultMH(sel, bestFitness, evals);
}

ResultMH BLsmall::optimize(Problem *problem, const tSolution &current, const tFitness fitness, const int maxevals) {
  assert(maxevals > 0);
  Snimp *snimp = dynamic_cast<Snimp *>(problem);
  assert(snimp != nullptr);

  tSolution sel = current;
  tFitness bestFitness = fitness;
  int evals = 0;
  int evalsSinMejora = 0;

  bool improvement = true;

  while (improvement && evals < maxevals && evalsSinMejora < 20) {
    improvement = false;

    // Nodos que no están en la solución actual
    auto nodos_totales = snimp->nodos();
    vector<int> noSel;
    for (int n : nodos_totales) {
      if (find(sel.begin(), sel.end(), n) == sel.end()) {
        noSel.push_back(n);
      }
    }

    // Generar vecinos aleatorios por intercambio
    auto vecinos = generarVecinosAleatorios(sel, noSel);

    for (auto [i, j] : vecinos) {
      tSolution nueva = sel;
      nueva[i] = j;
      tFitness fit = snimp->fitness(nueva);
      evals++;

      if (fit > bestFitness) {
        sel = nueva;
        bestFitness = fit;
        improvement = true;
        evalsSinMejora = 0;
        break;
      } else {
        evalsSinMejora++;
      }

      if (evals >= maxevals || evalsSinMejora >= 20) break;
    }
  }

  return ResultMH(sel, bestFitness, evals);
}
