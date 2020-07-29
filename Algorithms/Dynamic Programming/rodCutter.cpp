
/** Problem statement:
  * You are given a rod of length 'n' inches and an array of prices. This array contains
  * prices of smaller pieces of that rod when sold. Find the maximum value that could
  * be earned by cutting up the rod and selling the pieces
  */
#include <iostream>
#include <vector>

using namespace std;

int rodCutter(int cost[], int n) {
  vector<int> rod(n + 1, 0);

  for (int i = 1; i <= n; i++) {
    int max_val = INT32_MIN;
    for (int j = 1; j <= i; j++)
      max_val = max(max_val, cost[j] + rod[i - j]);

    rod[i] = max_val;
  }

  return rod[n];
}

int main() {
  int n = 4;
  int cost[5] = { 0, 2, 4, 7, 8 };
  cout << rodCutter(cost, n) << endl;
  return 0;
}
