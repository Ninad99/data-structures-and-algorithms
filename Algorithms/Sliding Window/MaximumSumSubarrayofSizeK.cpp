/** Problem Statement
  * Given an array of positive numbers and a positive number ‘k’, find the maximum sum of any contiguous subarray of size ‘k’.
  *
  * Example 1:
  * Input: [2, 1, 5, 1, 3, 2], k=3
  * Output: 9
  * Explanation: Subarray with maximum sum is [5, 1, 3].
  *
  * Example 2:
  * Input: [2, 3, 4, 1, 5], k=2
  * Output: 7
  * Explanation: Subarray with maximum sum is [3, 4].
  */

#include <iostream>
#include <vector>

using namespace std;

int findMaxSumSubArray(int k, vector<int> arr) {
  int n = arr.size(), result = 0, sum = 0, windowStart = 0;
  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    sum += arr[windowEnd]; // add the next element
    // slide the window; we don't need to slide if we haven't hit the required window size of 'k'
    if (windowEnd >= k - 1) {
      result = max(result, sum);
      sum -= arr[windowStart++];
    }
  }

  return result;
}

int main() {
  cout << findMaxSumSubArray(3, {2, 1, 5, 1, 3, 2}) << endl;
  cout << findMaxSumSubArray(2, {2, 3, 4, 1, 5}) << endl;
  return 0;
}
