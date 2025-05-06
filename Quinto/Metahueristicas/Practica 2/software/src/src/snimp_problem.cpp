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

    //cout << "\nCruce entre " << punto1 << " y " << punto2;

    tSolution hijo1(n, -1), hijo2(n, -1);
    set<int> usados1, usados2;

    // Copiar segmentos cruzados
    for (int i = 0; i < p1.size(); ++i) {
        if(i >= punto1 && i <= punto2) {
            hijo1[i] = p2[i];
            hijo2[i] = p1[i];
        } else {
            hijo1[i] = p1[i];
            hijo2[i] = p2[i];
        }
        usados1.insert(hijo1[i]);
        usados2.insert(hijo2[i]);
    }

    // Completar los hijos con nodos no usados
    vector<int> todosNodos = nodos();
    repararHijo(hijo1, todosNodos);
    repararHijo(hijo2, todosNodos);

    // imprimir padres e hijos
    // cout << "\nPadre 1: " << p1.size() << " nodos: ";
    // for (int i : p1) cout << i << " ";
    // cout << "\nPadre 2: " << p2.size() << " nodos: ";
    // for (int i : p2) cout << i << " ";
    // cout << "\nHijo 1: " << hijo1.size() << " nodos: ";
    // for (int i : hijo1) cout << i << " ";
    // cout << "\nHijo 2: " << hijo2.size() << " nodos: ";
    // for (int i : hijo2) cout << i << " " ;
    // cout << endl;  

    return {hijo1, hijo2};
}

void Snimp::repararHijo(tSolution &hijo, const vector<int> &todosNodos) {
    set<int> vistos;
    vector<int> duplicados;

    // Identificar duplicados
    for (int v : hijo) {
        if (vistos.count(v))
            duplicados.push_back(v);
        else
            vistos.insert(v);
    }

    // Obtener nodos no usados
    vector<int> disponibles;
    for (int nodo : todosNodos) {
        if (!vistos.count(nodo)) {
            disponibles.push_back(nodo);
        }
    }

    // Sustituir los duplicados por nodos disponibles
    int r = 0;
    set<int> yaCambiados;
    for (int &v : hijo) {
        if (count(hijo.begin(), hijo.end(), v) > 1 && !yaCambiados.count(v)) {
            if (r < disponibles.size()) {
                v = disponibles[r++];
            }
            yaCambiados.insert(v); // Para no sustituir dos veces el mismo valor
        }
    }
}


pair<tSolution, tSolution> Snimp::crossoverOrden( tSolution &p1,  tSolution &p2) {
    vector<int> conjunto(p1.begin(), p1.end());
    for (int i : p2) {
        conjunto.push_back(i);
    }


    vector<int> ordenado(conjunto.begin(), conjunto.end());
    sort(ordenado.begin(), ordenado.end());

    tSolution h1, h2;
    for (size_t i = 0; i < ordenado.size(); ++i) {
        if (i % 2 == 0 && h1.size() < solSize)
            h1.push_back(ordenado[i]);
        else if (h2.size() < solSize)
            h2.push_back(ordenado[i]);
    }

    return {h1, h2};
}


