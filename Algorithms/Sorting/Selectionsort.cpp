#include <iostream>

using namespace std;

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void selectionSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int smallest = i;
    for (int j = i + 1; j < n; j++)
      if (arr[j] < arr[smallest])
        smallest = j;

    if (smallest != i)
      swap(&arr[smallest], &arr[i]);
  }
}

int main() {
  int n = 8;
  int arr[] = {5, 1, 2, 5, 45, 0, 12, 7};
  selectionSort(arr, 8);

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}
