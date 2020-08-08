#include <iostream>

using namespace std;

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partition(int arr[], int pivot, int left, int right) {
  int pivotValue = arr[pivot];
  int partitionIndex = left;

  for (int i = left; i < right; i++) {
    if (arr[i] < pivotValue) {
      swap(&arr[i], &arr[partitionIndex]);
      partitionIndex++;
    }
  }
  swap(&arr[right], &arr[partitionIndex]);

  return partitionIndex;
}

void quickSort(int arr[], int left, int right) {
  int pivot, partitionIndex;

  if (left < right) {
    pivot = right;
    partitionIndex = partition(arr, pivot, left, right);

    // sort left and right
    quickSort(arr, left, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, right);
  }
}

int main() {
  int n = 8;
  int arr[] = {5, 1, 2, 5, 45, 0, 12, 7};
  quickSort(arr, 0, n - 1);

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}
