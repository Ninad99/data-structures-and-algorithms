#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from, to, weight;
};

vector<int> BellmanFord(vector<Edge>& graph, int N, int startNode) {
  int E = graph.size(); // no of edges
  vector<int> dist(N, INT32_MAX);
  dist[startNode] = 0;

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < graph.size(); j++) {
      // relax edge (update dist with shorter path)
      if (dist[graph[j].from] + graph[j].weight < dist[graph[j].to])
        dist[graph[j].to] = dist[graph[j].from] + graph[j].weight;
    }
  }

  // Repeat to find nodes caught in -ve cycle
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < graph.size(); j++) {
      if (dist[graph[j].from] + graph[j].weight < dist[graph[j].to])
        dist[graph[j].to] = INT32_MIN;
    }
  }

  return dist;
}

int main() {
  int N = 6;
  vector<Edge> graph; // edgelist
  graph.push_back({0, 1, 4});
  graph.push_back({0, 6, 2});
  graph.push_back({1, 1, -1});
  graph.push_back({1, 2, 3});
  graph.push_back({2, 3, 3});
  graph.push_back({2, 4, 1});
  graph.push_back({3, 5, -2});
  graph.push_back({4, 5, 2});
  graph.push_back({6, 4, 2});
  vector<int> paths = BellmanFord(graph, N, 0);
  cout << "\nPaths: ";
  for (int i = 0; i < paths.size(); i++) {
    cout << paths[i] << " ";
  }
  cout << endl;
  return 0;
}
