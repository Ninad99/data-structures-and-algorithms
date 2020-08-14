/** Problem statement
  * Given an array, find the length of the smallest subarray in it which when sorted will sort the whole array.
  *
  * Example 1:
  * Input: [1, 2, 5, 3, 7, 10, 9, 12]
  * Output: 5
  * Explanation: We need to sort only the subarray [5, 3, 7, 10, 9] to make the whole array sorted
  *
  * Example 2:
  * Input: [1, 3, 2, 0, -1, 7, 10]
  * Output: 5
  * Explanation: We need to sort only the subarray [1, 3, 2, 0, -1] to make the whole array sorted
  *
  * Example 3:
  * Input: [1, 2, 3]
  * Output: 0
  * Explanation: The array is already sorted
  *
  * Example 4:
  * Input: [3, 2, 1]
  * Output: 3
  * Explanation: The whole array needs to be sorted.
  */

#include <iostream>
#include <vector>

using namespace std;

int minimumWindowSort(vector<int> arr) {
  int n = arr.size(), left = 0, right = arr.size() - 1;

  while (left < n - 1 && arr[left] <= arr[left + 1]) left++;

  if (left == n - 1) return 0;

  while (right > 0 && arr[right] >= arr[right - 1]) right--;

  int maxInSubarray = INT32_MIN, minInSubarray = INT32_MAX;
  for (int k = left; k <= right; k++) {
    maxInSubarray = max(maxInSubarray, arr[k]);
    minInSubarray = min(minInSubarray, arr[k]);
  }

  while (left > 0 && arr[left - 1] > minInSubarray) left--;

  while (right < n - 1 && arr[right + 1] < maxInSubarray) right++;

  return right - left + 1;
}

int main() {
  cout << minimumWindowSort(vector<int>{1, 2, 5, 3, 7, 10, 9, 12}) << endl;
  cout << minimumWindowSort(vector<int>{1, 3, 2, 0, -1, 7, 10}) << endl;
  cout << minimumWindowSort(vector<int>{1, 2, 3}) << endl;
  cout << minimumWindowSort(vector<int>{3, 2, 1}) << endl;
  return 0;
}
