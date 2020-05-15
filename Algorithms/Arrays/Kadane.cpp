// Largest Sum of Contiguous Subarray

#include <iostream>
#include <cmath>

using namespace std;

int KadaneWithIndices(int *arr, int n) {
  int currentMax = arr[0], totalMax = arr[0];
  int startIndex = 0, endIndex = 0;

  for (int i = 1; i < n; i++) {
    if ((currentMax + arr[i]) < arr[i]) {
      currentMax = arr[i];
      startIndex = i;
    } else {
      currentMax += arr[i];
      if (currentMax > totalMax) {
        totalMax = currentMax;
        endIndex = i;
      }
    }
  }

  cout << "\nStart index: " << startIndex << ", end index: " << endIndex << endl;
  return totalMax;
}

int Kadane(int *arr, int n) {
  int currentMax = INT_MIN, totalMax = INT_MIN;

  for (int i = 0; i < n; i++) {
    currentMax = max(currentMax, 0) + arr[i];
    totalMax = max(totalMax, currentMax);
  }

  return totalMax;
}

int main() {
  int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
  int n = 8;
  cout << KadaneWithIndices(arr, n) << endl;
}
