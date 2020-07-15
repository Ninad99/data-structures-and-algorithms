#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int start, vector<vector<int> >& g, vector<int>& visited) {
  visited[start] = true;
  cout << "\nStarting node: " << start << endl;
  queue<int> q;
  q.push(start);
  while (!q.empty()) {
    int currentNode = q.front();
    vector<int> neighbours = g[currentNode];
    for (int i = 0; i < neighbours.size(); i++) {
      if (!visited[neighbours[i]]) {
        q.push(neighbours[i]);
        visited[neighbours[i]] = true;
        cout << "\nVisiting node " << neighbours[i] << endl;
      }
    }
    q.pop();
  }
}

int main() {
  int n = 13;
  vector<int> visited(n, false);
  vector<vector<int> > graph(n, vector<int>(0));
  graph[0].push_back(7);
  graph[0].push_back(9);
  graph[0].push_back(11);
  graph[3].push_back(2);
  graph[3].push_back(4);
  graph[6].push_back(5);
  graph[7].push_back(3);
  graph[7].push_back(6);
  graph[7].push_back(11);
  graph[8].push_back(1);
  graph[8].push_back(12);
  graph[9].push_back(8);
  graph[9].push_back(10);
  graph[10].push_back(1);
  graph[12].push_back(2);
  bfs(0, graph, visited);
  return 0;
}
