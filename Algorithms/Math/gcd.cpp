#include <iostream>

using namespace std;

// Euclidean algorithm
// returns gcd of a and b
int gcd(int a, int b) {
  if (a == 0)
    return b;

  return gcd(b % a, a);
}

// computes x and y along with gcd
// ax + by = gcd(a, b)
int extendedEuclid(int a, int b, int *x, int *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }

  int x1, y1;
  int gcd = extendedEuclid(b % a, a, &x1, &y1);

  *x = y1 - (b/a) * x1;
  *y = x1;

  return gcd;
}

int main() {
  int a = 36, b = 60, x, y;
  cout << gcd(a, b) << endl;
}
