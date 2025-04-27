#include <algorithm>
#include <snimp_problem.h>
#include <random.hpp>
#include <set>
#include <string>
#include <iostream>
#include <random.hpp>
#include <sstream>

using namespace std;

tFitness Snimp::fitness(tSolution &solution) { // solution es un vector de int
    stringstream ss;
    Random::serialize(ss);
    Random::seed(10);

    float fitness = 0;
    const int ENV = 10; // Numero de simulaciones
    const float PROB = 0.01;
    vector<int> nodos_infectados_iniciales = {};
    vector<int> nodos_infectados = {};
    vector<int> nodos_infectados_nuevos = {};
    for (int i = 0; i < ENV; i++) {
        // Inicializamos A y A* 
        nodos_infectados_iniciales = solution;
        nodos_infectados = solution;

        // Mientras haya nodos infectados nuevos
        while(nodos_infectados_iniciales.size() > 0) {
            nodos_infectados_nuevos = {};
            for(int j : nodos_infectados_iniciales) {
                
                // Por cada vecino del nodo j
                for (int neighbor : graph[j]) {
                    // Si el vecino no esta contagiado y la probabilidad de contagio se cumple
                    if (Random::get<double>(0,1) <= PROB && find(nodos_infectados.begin(), nodos_infectados.end(), neighbor) == nodos_infectados.end()) {
                        nodos_infectados_nuevos.push_back(neighbor);
                    }
                }
                
            }
            nodos_infectados.insert(nodos_infectados.end(), nodos_infectados_nuevos.begin(), nodos_infectados_nuevos.end());
            nodos_infectados_iniciales = nodos_infectados_nuevos;
        }
        fitness += nodos_infectados.size();
    }
    Random::deserialize(ss);
    return fitness/ENV*1.0;
}

tSolution Snimp::createSolution() {
    vector<int> infectedNodes;
    vector<int> availableNodes;

    for (const auto& node : graph) {
        availableNodes.push_back(node.first);
    }
    
    Random::shuffle(availableNodes.begin(), availableNodes.end());
    
    for (int i = 0; i < solSize && i < availableNodes.size(); ++i) {
        infectedNodes.push_back(availableNodes[i]);
    }
    
    return infectedNodes;
}

size_t Snimp::getSize() {
    return numNodes;
}

float Snimp::heuristic(int nodo) {
    float heuristica = 0;
    vector<int> vecinos = graph[nodo];
    for (int vecino : vecinos) {
        heuristica += graph[vecino].size();
    }
    return heuristica + graph[nodo].size();
}

vector<int> Snimp::nodos() {
    vector<int> keys;
    for(auto par: graph) {
        keys.push_back(par.first);
    }
    return keys;
}

bool Snimp::esValida( tSolution &sol) {
    set<int> s(sol.begin(), sol.end());
    return sol.size() == solSize && s.size() == solSize;
}

tSolution Snimp::mutate(tSolution &sol) {
    tSolution mutated = sol;
    set<int> currentNodes(sol.begin(), sol.end()); // para buscar rápido
    vector<int> allNodes = nodos(); // todos los nodos posibles

    // Construir lista de nodos no usados
    vector<int> unusedNodes;
    for (int node : allNodes) {
        if (!currentNodes.count(node)) {
            unusedNodes.push_back(node);
        }
    }

    if (unusedNodes.empty()) return mutated; // no hay mutación posible

    int pos = Random::get<int>(0, solSize - 1); // posición a mutar
    int newNode = unusedNodes[Random::get<int>(0, unusedNodes.size() - 1)];

    mutated[pos] = newNode;
    return mutated;
}

pair<tSolution, tSolution> Snimp::crossover2Puntos( tSolution &p1, tSolution &p2) {
    int n = solSize;
    // el segmento a reemplazar va desde punto1 hasta punto2
    int punto1 = Random::get(0, n - 2);
    int punto2 = Random::get(punto1 + 1, n - 1);

    tSolution hijo1(n, -1), hijo2(n, -1);
    set<int> usados1, usados2;

    // Copiar segmentos cruzados
    for (int i = punto1; i <= punto2; ++i) {
        hijo1[i] = p2[i];
        hijo2[i] = p1[i];
        usados1.insert(hijo1[i]);
        usados2.insert(hijo2[i]);
    }

    // Completar resto del hijo1 con genes de p1
    int idx1 = 0; // índice para recorrer p1
    for (int i = 0; i < n; ++i) {
        if (i >= punto1 && i <= punto2) continue; // ya está copiado
        while (idx1 < n && usados1.count(p1[idx1])) ++idx1; // avanzar hasta encontrar un gen no usado
        if (idx1 < n) {
            hijo1[i] = p1[idx1];
            ++idx1; 
        }
    }

    // Completar resto del hijo2 con genes de p2
    int idx2 = 0;
    for (int i = 0; i < n; ++i) {
        if (i >= punto1 && i <= punto2) continue;
        while (idx2 < n && usados2.count(p2[idx2])) ++idx2;
        if (idx2 < n) {
            hijo2[i] = p2[idx2];
            ++idx2;
        }
    }

    // Reparar hijo1 si quedan -1
    if (count(hijo1.begin(), hijo1.end(), -1) > 0) {
        vector<int> restantes;
        for (int node : nodos()) {
            if (!usados1.count(node)) restantes.push_back(node);
        }
        Random::shuffle(restantes.begin(), restantes.end());

        int r = 0;
        for (int &v : hijo1) {
            if (v == -1 && r < restantes.size()) {
                v = restantes[r++];
            }
        }
    }

    // Reparar hijo2 si quedan -1
    if (count(hijo2.begin(), hijo2.end(), -1) > 0) {
        vector<int> restantes;
        for (int node : nodos()) {
            if (!usados2.count(node)) restantes.push_back(node);
        }
        Random::shuffle(restantes.begin(), restantes.end());

        int r = 0;
        for (int &v : hijo2) {
            if (v == -1 && r < restantes.size()) {
                v = restantes[r++];
            }
        }
    }

    return {hijo1, hijo2};
}


pair<tSolution, tSolution> Snimp::crossoverOrden( tSolution &p1,  tSolution &p2) {
    set<int> conjunto(p1.begin(), p1.end());
    conjunto.insert(p2.begin(), p2.end());

    vector<int> ordenado(conjunto.begin(), conjunto.end());
    sort(ordenado.begin(), ordenado.end());

    tSolution h1, h2;
    for (size_t i = 0; i < ordenado.size(); ++i) {
        if (i % 2 == 0 && h1.size() < solSize)
            h1.push_back(ordenado[i]);
        else if (h2.size() < solSize)
            h2.push_back(ordenado[i]);
    }

    // Si faltan nodos, completar aleatoriamente
    vector<int> disponibles = nodos();
    Random::shuffle(disponibles.begin(), disponibles.end());

    set<int> usados1(h1.begin(), h1.end());
    for (int node : disponibles) {
        if (h1.size() < solSize && !usados1.count(node)) {
            h1.push_back(node);
            usados1.insert(node);
        }
    }

    set<int> usados2(h2.begin(), h2.end());
    for (int node : disponibles) {
        if (h2.size() < solSize && !usados2.count(node)) {
            h2.push_back(node);
            usados2.insert(node);
        }
    }

    return {h1, h2};
}


