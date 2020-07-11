/** An implementation of a graph data structure using an adjacency matrix
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
  int V; // number of vertices/nodes in the graph
  int E; // number of edges in the graph
  vector<vector<int> > adj; // 2d matrix representing the graph

public:
  Graph(int); // creates a new graph
  ~Graph();
  int getVerticesCount(); // returns the count of vertices
  int getEdgesCount(); // returns the count of edges
  void addEdge(int, int); // adds an edge between the two vertices
  void printGraph(); // prints the graph
};

Graph::Graph(int n) {
  E = 0;
  V = n;
  adj = vector<vector<int> >(n, vector<int>(n, 0));
}

Graph::~Graph() {}

Graph::getVerticesCount() {
  return V;
}

Graph::getEdgesCount() {
  return E;
}

void Graph::addEdge(int src, int dest) {
  if (src < 0 || dest < 0 || src > V || dest > V)
    return;
  E = E + 1;
  adj[src][dest] = 1;
}

void Graph::printGraph() {
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      cout << adj[i][j] << " ";
    }
    cout << "\n";
  }
}
