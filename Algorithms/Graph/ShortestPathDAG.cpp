#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int to, weight;
};

int dfs(int orderingIndex, int at, vector<bool>& visited, vector<int>& ordering, vector<vector<Edge> >& graph) {
  visited[at] = true;
  vector<Edge> edges = graph[at];
  for (int i = 0; i < edges.size(); i++) {
    if (!visited[edges[i].to])
      orderingIndex = dfs(orderingIndex, edges[i].to, visited, ordering, graph);
  }

  ordering[orderingIndex] = at;
  return orderingIndex - 1;
}

vector<int> toposort(vector<vector<Edge> >& graph) {
  int N = graph.size();
  vector<bool> visited(N, false);
  vector<int> ordering(N, 0);
  int orderingIndex = N - 1;

  for (int at = 0; at < N; at++) {
    if (!visited[at])
      orderingIndex = dfs(orderingIndex, at, visited, ordering, graph);
  }

  return ordering;
}

// returns the shortest path from starting node to all other nodes in the DAG
vector<int> DAGShortestPath(vector<vector<Edge> >& graph, int startIndex) {
  int N = graph.size();
  vector<int> topsort = toposort(graph);
  vector<int> dist(N, INT32_MIN);
  dist[startIndex] = 0;

  for (int i = 0; i < N; i++) {
    int nodeIndex = topsort[i];
    if (dist[nodeIndex] != INT32_MIN) {
      vector<Edge> adjacentEdges = graph[nodeIndex];
      if (adjacentEdges.size() > 0) {
        for (int j = 0; j < adjacentEdges.size(); j++) {
          int newDist = dist[nodeIndex] + adjacentEdges[j].weight;
          if (dist[adjacentEdges[j].to] == INT32_MIN)
            dist[adjacentEdges[j].to] = newDist;
          else
            dist[adjacentEdges[j].to] = min(dist[adjacentEdges[j].to], newDist);
        }
      }
    }
  }

  return dist;
}

int main() {
  vector<vector<Edge> > graph(8, vector<Edge>(0));
  graph[0].push_back({ 1, 3 });
  graph[0].push_back({ 2, 6 });
  graph[1].push_back({ 2, 4 });
  graph[1].push_back({ 3, 4 });
  graph[1].push_back({ 4, 11 });
  graph[2].push_back({ 3, 8 });
  graph[2].push_back({ 6, 11 });
  graph[3].push_back({ 4, -4 });
  graph[3].push_back({ 5, 5 });
  graph[3].push_back({ 6, 2 });
  graph[4].push_back({ 7, 9 });
  graph[5].push_back({ 7, 1 });
  graph[6].push_back({ 7, 2 });

  vector<int> path = DAGShortestPath(graph, 0);

  cout << "\n\nShortest path in DAG: ";
  for (int i = 0; i < path.size(); i++) {
    cout << path[i] << " ";
  }
  cout << endl;

  return 0;
}
