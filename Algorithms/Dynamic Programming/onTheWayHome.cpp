#include <iostream>
#include <vector>

using namespace std;

int util(int r, int c, int m, int n) {
  if (r == m - 1 || c == n - 1)
    return 1;

  return util(r + 1, c, m, n) + util(r, c + 1, m, n);
}

int numWaysRecursive(int m, int n) {
    int startRow = 0, startCol = 0;
    return util(startRow, startCol, m, n);
}

int numWaysMemoized(int m, int n) {
  vector<vector<int> > dp(m, vector<int>(n));

  for (int i = 0; i < m; i++)
    dp[i][n - 1] = 1;
  for (int i = 0; i < n; i++)
    dp[m - 1][i] = 1;

  for (int i = m - 2; i >= 0; i--) {
    for (int j = n - 2; j >= 0; j--) {
      dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
    }
  }

  return dp[0][0];
}

int main() {
  int m = 4, n = 3;
  cout << numWaysMemoized(m, n) << endl;
  return 0;
}
