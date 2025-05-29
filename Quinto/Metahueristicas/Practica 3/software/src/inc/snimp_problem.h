#pragma once
#include <algorithm>
#include <unordered_map>
#include <problem.h>
#include <string>

using namespace std;

class Snimp : public Problem {
private:
    unordered_map<int, vector<int>> graph;  // Lista de adyacencia del grafo
    size_t numNodes;  // Cantidad de nodos en el grafo
    size_t solSize;  // Tamaño de la solución

public:
    Snimp(const unordered_map<int, vector<int>> &inputGraph) : Problem() {graph = inputGraph;
    numNodes = graph.size(); solSize = 10; } // cambair a 30 en esta practica
    tFitness fitness(tSolution &solution);
    tSolution createSolution() override;
    size_t getSize();
    size_t getSolutionSize() { return solSize; }
    vector<int> nodos();
    float heuristic(int pos_nodo);
    bool esValida(tSolution &solution);
    tSolution mutate(tSolution &sol);
    tSolution mutate(tSolution &sol, double porcentaje);
    pair<tSolution, tSolution> crossover2Puntos(tSolution &sol1, tSolution &sol2);
    pair<tSolution, tSolution> crossoverOrden( tSolution &p1,  tSolution &p2);
    void repararHijo(tSolution &hijo, const vector<int> &todosNodos);
};