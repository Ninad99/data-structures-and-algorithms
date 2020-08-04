#include <iostream>

using namespace std;

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bubbleSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
}

int main() {
  int n = 8;
  int arr[] = {5, 1, 2, 5, 45, 0, 12, 7};
  bubbleSort(arr, 8);

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}
