/** Problem statement
  * Given an array of unsorted numbers and a target number, find a triplet in the array whose sum is as
  * close to the target number as possible, return the sum of the triplet. If there are more than one such
  * triplet, return the sum of the triplet with the smallest sum.
  *
  * Example 1:
  * Input: [-2, 0, 1, 2], target=2
  * Output: 1
  * Explanation: The triplet [-2, 1, 2] has the closest sum to the target.
  *
  * Example 2:
  * Input: [-3, -1, 1, 2], target=1
  * Output: 0
  * Explanation: The triplet [-3, 1, 2] has the closest sum to the target.
  *
  * Example 3:
  * Input: [1, 0, 1, 1], target=100
  * Output: 3
  * Explanation: The triplet [1, 1, 1] has the closest sum to the target.
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int searchTripletClosestSum(vector<int>& arr, int targetSum) {
  sort(arr.begin(), arr.end());
  int n = arr.size(), left, right, smallestDiff = INT32_MAX, targetDiff;

  for (int i = 0; i < n - 2; i++) {
    left = i + 1; right = n - 1;
    while (left < right) {
      targetDiff = targetSum - (arr[i] + arr[left] + arr[right]);

      if (targetDiff == 0)
        return targetSum;

      if (abs(targetDiff) < abs(smallestDiff))
        smallestDiff = targetDiff;

      if (targetDiff > 0)
        left++;
      else
        right--;
    }
  }

  return targetSum - smallestDiff;
}

int main() {
  vector<int> arr = {-2, 0, 1, 2};
  cout << searchTripletClosestSum(arr, 2) << endl;
  arr = {-3, -1, 1, 2};
  cout << searchTripletClosestSum(arr, 1) << endl;
  arr = {1, 0, 1, 1};
  cout << searchTripletClosestSum(arr, 100) << endl;
  return 0;
}
