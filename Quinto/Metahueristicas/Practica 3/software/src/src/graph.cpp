#include <iostream>
#include <fstream>
#include <sstream>
#include <graph.h>


using namespace std;

void Graph::addEdge(int from, int to){
    adjList[from].push_back(to);
}

void Graph::printGraph() {
    for (const auto &node : adjList) {
        cout << "Nodo " << node.first << " -> ";
        for (int neighbor : node.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}


Graph readGraphFromFile(const string &filename) {
    ifstream file(filename);
    Graph graph;
    string line;

    if (!file) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }

    while (getline(file, line)) {
        if (line[0] == '#') continue;  // Saltar comentarios

        istringstream iss(line);
        int from, to;
        if (iss >> from >> to) {
            graph.addEdge(from, to);
        }
    }

    file.close();
    return graph;
}