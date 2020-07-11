#include <iostream>
#include <vector>

using namespace std;

int fibRecursive(int n) {
  if (n <= 1)
    return n;

  return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int fibRecursiveMemoized(int n, vector<int>& memo) {
  if (memo[n] == -1) {
    if (n <= 1)
      memo[n] = n;
    else
      memo[n] = fibRecursiveMemoized(n - 1, memo) + fibRecursiveMemoized(n - 2, memo);
  }

  return memo[n];
}

int fibBottomUp(int n) {
  int f[n + 2];
  f[0] = 0;
  f[1] = 1;

  for (int i = 2; i <= n; i++) {
    f[i] = f[i - 1] + f[i - 2];
  }

  return f[n];
}

int fibBottomUpOptimized(int n) {
  if (n == 0)
    return 0;

  int a = 0, b = 1, c;

  for (int i = 2; i <= n; i++) {
    c = a + b;
    a = b;
    b = c;
  }

  return b;
}

int main() {
  int n = 6;
  vector<int> memo(n + 1, -1);
  cout << fibRecursive(n) << endl;
  cout << fibRecursiveMemoized(n, memo) << endl;
  cout << fibBottomUp(n) << endl;
  cout << fibBottomUpOptimized(n) << endl;
}
