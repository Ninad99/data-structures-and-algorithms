#include <iostream>

using namespace std;

void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i], j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

int main() {
  int n = 8;
  int arr[] = {5, 1, 2, 5, 45, 0, 12, 7};
  insertionSort(arr, 8);

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}
