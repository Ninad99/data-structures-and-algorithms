#include <iostream>
#include <vector>

#define INFINITY 100000007

using namespace std;

void propagateNegativeCycles(vector<vector<int> >& dp, vector<vector<int> >& next, int N) {
  // execute FW APSP algorithm again but this time if the distance
  // can be improved, set the optimal distance to be -INFINITY
  // Every edge (i,j) marked with -INFINITY is either part
  // of or reaches into a negative cycle
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (dp[i][k] + dp[k][j] < dp[i][j]) {
          dp[i][j] = -INFINITY;
          next[i][j] = -1;
        }
      }
    }
  }
}

vector<vector<int> > FloydWarshall(vector<vector<int> >& matrix, int N) {
  vector<vector<int> > dp(N, vector<int>(N)); // memo table
  vector<vector<int> > next(N, vector<int>(N)); // matrix used to reconstruct shortest paths
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      dp[i][j] = matrix[i][j];
      if (matrix[i][j] != INFINITY) next[i][j] = j;
    }
  }

  // Floyd Warshall
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (dp[i][k] + dp[k][j] < dp[i][j]) {
          dp[i][j] = dp[i][k] + dp[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }

  propagateNegativeCycles(dp, next, N);

  return dp;
}

int main() {
  int N = 4;
  vector<vector<int> > graph = {
    { 0, 4, 1, INFINITY },
    { INFINITY, 0, 6, INFINITY },
    { 4, 1, 0, 2 },
    { INFINITY, INFINITY, INFINITY, 0 }
  };
  vector<vector<int> > result = FloydWarshall(graph, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << result[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
