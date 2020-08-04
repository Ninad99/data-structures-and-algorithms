#include <iostream>

using namespace std;

void merge(int *arr, int start, int mid, int end) {
  int leftLength = (mid - start) + 1;
  int rightLength = end - mid;
  int left[leftLength], right[rightLength];
  int i, j, count;

  for (i = 0; i < leftLength; i++)
    left[i] = arr[start + i];

  for (i = 0; i < rightLength; i++)
    right[i] = arr[mid + i + 1];

  i = 0, j = 0, count = start;
  while (i < leftLength && j < rightLength) {
    if (left[i] <= right[j]) {
      arr[count] = left[i];
      i++;
    } else {
      arr[count] = right[j];
      j++;
    }
    count++;
  }

  while (i < leftLength)
    arr[count++] = left[i++];

  while (j < rightLength)
    arr[count++] = right[j++];
}

void mergeSort(int arr[], int startIndex, int endIndex) {
  if (startIndex < endIndex) {
    int mid = startIndex + (endIndex - startIndex) / 2;

    mergeSort(arr, startIndex, mid);
    mergeSort(arr, mid + 1, endIndex);

    merge(arr, startIndex, mid, endIndex);
  }
}

int main() {
  int n = 8;
  int arr[] = {5, 1, 2, 5, 45, 0, 12, 7};
  mergeSort(arr, 0, n - 1);

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}
