/** Problem statement:
  * You want to reach heaven that is at the top of the staircase. The staircase
  * has 'n' steps, and at each step you can climb either 1 step or 2 steps further.
  * In how many ways can you reach heaven?
  */

#include <iostream>
#include <vector>

using namespace std;

int stairwayToHeavenRecursive(int n) {
  if (n == 0 || n == 1)
    return 1;

  return stairwayToHeavenRecursive(n - 1) + stairwayToHeavenRecursive(n - 2);
}

int stairwayToHeavenMemoized(int n) {
  vector<int> dp(n + 1, 0);
  dp[0] = dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

int main() {
  int n = 6;
  cout << stairwayToHeavenMemoized(n) << endl;
  return 0;
}
