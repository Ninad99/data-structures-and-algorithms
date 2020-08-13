/** Problem statement
  * Given an array arr of unsorted numbers and a target sum, count all triplets in it such
  * that arr[i] + arr[j] + arr[k] < target where i, j, and k are three different indices.
  * Write a function to return the count of such triplets.
  *
  * Example 1:
  * Input: [-1, 0, 2, 3], target=3
  * Output: 2
  * Explanation: There are two triplets whose sum is less than the target: [-1, 0, 3], [-1, 0, 2]
  *
  * Example 2:
  * Input: [-1, 4, 2, 1, 3], target=5
  * Output: 4
  * Explanation: There are four triplets whose sum is less than the target:
  * [-1, 1, 4], [-1, 1, 3], [-1, 1, 2], [-1, 2, 3]
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int searchTriplets(vector<int>& arr, int target) {
  sort(arr.begin(), arr.end());
  int count = 0, n = arr.size(), left, right, currSum;
  for (int i = 0; i < n - 2; i++) {
    left = i + 1;
    right = n - 1;

    while (left < right) {
      currSum = arr[i] + arr[left] + arr[right];

      if (currSum < target) {
        count += right - left;
        left++;
      } else {
        right--;
      }
    }
  }

  return count;
}

int main() {
  vector<int> arr = {-1, 0, 2, 3};
  cout << searchTriplets(arr, 3) << endl;

  arr = {-1, 4, 2, 1, 3};
  cout << searchTriplets(arr, 5) << endl;

  return 0;
}
