#include <iostream>
#include <vector>

using namespace std;

void printGraph(vector<vector<int> >& g) {
  for (int i = 0; i < g.size(); i++) {
    cout << "\n" << i << " -> ";
    for (int j = 0; j < g[i].size(); j++) {
      cout << g[i][j] << " ";
    }
    cout << "\n";
  }
}

void dfs(int at, int N, vector<vector<int> >& g, vector<int>& visited) {
  if (visited[at]) {
    return;
  }

  cout << "\nVisiting node " << at << endl;
  visited[at] = true;
  vector<int> neighbours = g[at];
  for (int i = 0; i < neighbours.size(); i++) {
    dfs(neighbours[i], N, g, visited);
  }
}

int main() {
  int n = 12;
  vector<vector<int> > graph(n, vector<int>(0));
  graph[0].push_back(1);
  graph[0].push_back(9);
  graph[1].push_back(0);
  graph[1].push_back(8);
  graph[2].push_back(3);
  graph[3].push_back(2);
  graph[3].push_back(4);
  graph[3].push_back(5);
  graph[3].push_back(7);
  graph[4].push_back(3);
  graph[5].push_back(3);
  graph[5].push_back(6);
  graph[6].push_back(5);
  graph[6].push_back(7);
  graph[7].push_back(3);
  graph[7].push_back(6);
  graph[7].push_back(10);
  graph[7].push_back(11);
  graph[8].push_back(1);
  graph[8].push_back(7);
  graph[8].push_back(9);
  graph[9].push_back(0);
  graph[9].push_back(8);
  graph[10].push_back(7);
  graph[10].push_back(11);
  graph[11].push_back(7);
  graph[11].push_back(10);
  printGraph(graph);
  vector<int> visited(n, false);
  dfs(0, graph.size(), graph, visited);
  return 0;
}
