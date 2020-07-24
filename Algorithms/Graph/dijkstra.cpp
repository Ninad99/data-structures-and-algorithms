#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

struct Edge {
  int from, to, weight;
};

struct comparator {
  constexpr bool operator()(
    pair<int, int> const& a,
    pair<int, int> const& b
  ) const noexcept {
    return a.second > b.second;
  }
};

typedef pair<int, int> Tuple;

vector<vector<int>> dijkstra(vector<vector<Edge> > g, int n, int s) {
  vector<bool> visited(n, false);
  vector<int> prev(n, -1);
  vector<int> dist(n, INT32_MAX);
  dist[s] = 0;
  priority_queue<Tuple, vector<Tuple>, comparator> pq;
  pq.push({ s, 0 });
  while (!pq.empty()) {
    Tuple current = pq.top(); pq.pop();
    visited[current.first] = true;
    // if distance to current node from start node is less than
    // the accumulated distance up till the current node, continue
    if (dist[current.first] < current.second) continue;
    vector<Edge> edges = g[current.first];
    for (int i = 0; i < edges.size(); i++) {
      if (visited[edges[i].to]) continue;
      int newDist = dist[current.first] + edges[i].weight;
      if (newDist < dist[edges[i].to]) {
        prev[edges[i].to] = current.first;
        dist[edges[i].to] = newDist;
        pq.push({ edges[i].to, newDist });
      }
    }
  }

  vector<vector<int> > result;
  result.push_back(dist);
  result.push_back(prev);
  return result;
}

vector<int> findShortestPath(vector<vector<Edge> > g, int n, int start, int end) {
  vector<vector<int> > result = dijkstra(g, n, start);
  vector<int> dist = result[0];
  vector<int> prev = result[1];
  vector<int> path;
  if (dist[end] == INT32_MAX)
    return path;

  for (int at = end; prev[at] != -1; at = prev[at]) {
    path.push_back(at);
  }
  reverse(path.begin(), path.end());

  return path;
}

int main() {
  int n = 5;
  vector<vector<Edge> > graph(n, vector<Edge>(0));
  graph[0].push_back({ 0, 1, 4 });
  graph[0].push_back({ 0, 2, 1 });
  graph[1].push_back({ 1, 3, 1 });
  graph[2].push_back({ 2, 1, 2 });
  graph[2].push_back({ 2, 3, 5 });
  graph[3].push_back({ 3, 4, 3 });

  for (int i = 0; i < graph.size(); i++) {
    cout << "\n" << i << " -> ";
    for (int j = 0; j < graph[i].size(); j++) {
      cout << "{" << graph[i][j].from << "," << graph[i][j].to << "," << graph[i][j].weight << "}";
    }
    cout << "\n";
  }

  vector<int> path = findShortestPath(graph, n, 0, 4);

  cout << "\nShortest Path from 0 to 4 = 0 -> ";
  for (int i = 0; i < path.size(); i++) {
    if (i == path.size() - 1)
      cout << path[i];
    else
      cout << path[i] << " -> ";
  }
  cout << endl;

  return 0;
}
