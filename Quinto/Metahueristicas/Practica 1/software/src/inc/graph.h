#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph {
public:
    unordered_map<int, vector<int>> adjList;

    void addEdge(int from, int to) ;
    void printGraph();
};

Graph readGraphFromFile(const string &filename);