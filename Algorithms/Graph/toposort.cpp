#include <iostream>
#include <vector>

using namespace std;

void dfs(int at, vector<bool>& visited, vector<int>& visitedNodes, vector<vector<int> >& graph) {
  if (visited[at])
    return;

  visited[at] = true;
  vector<int> edges = graph[at];
  for (int i = 0; i < edges.size(); i++) {
    if (!visited[edges[i]])
      dfs(edges[i], visited, visitedNodes, graph);
  }

  visitedNodes.push_back(at);
}

vector<int> toposort(vector<vector<int> >& graph, int N) {
  vector<bool> visited(N, false);
  vector<int> ordering(N, 0);
  int i = N-1;
  for (int at = 0; at < N; at++) {
    if (!visited[at]) {
      vector<int> visitedNodes;
      dfs(at, visited, visitedNodes, graph);
      for (int j = 0; j < visitedNodes.size(); j++) {
        ordering[i] = visitedNodes[j];
        i--;
      }
    }
  }

  return ordering;
}

int main() {
 vector<vector<int> > graph = {
     { 1, 2, 3 },
     { 9 },
     {},
     { 4, 6 },
     { 7, 10 },
     {},
     { 5, 8 },
     {},
     {},
     {},
     {}
   };

  vector<int> ordering = toposort(graph, 10);
  for (int i = 0; i < ordering.size(); i++) {
    cout << ordering[i] << " ";
  }

  return 0;
}
