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