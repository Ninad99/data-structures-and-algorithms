/** Problem Statement
  * Given an array containing 0s and 1s, if you are allowed to replace no more than ‘k’ 0s with 1s,
  * find the length of the longest contiguous subarray having all 1s.
  *
  * Example 1:
  * Input: Array=[0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1], k=2
  * Output: 6
  * Explanation: Replace the '0' at index 5 and 8 to have the longest contiguous subarray of 1s having length 6.
  *
  * Example 2:
  * Input: Array=[0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], k=3
  * Output: 9
  * Explanation: Replace the '0' at index 6, 9, and 10 to have the longest contiguous subarray of 1s having length 9.
  */

#include <iostream>
#include <vector>

using namespace std;

int findLength(const vector<int>& arr, int k) {
  int n = arr.size(), result = 0;
  int windowStart = 0, maxOnesCount = 0;

  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    if (arr[windowEnd] == 1) maxOnesCount++;

    if (windowEnd - windowStart + 1 - maxOnesCount > k) {
      if (arr[windowStart] == 1) maxOnesCount--;
      windowStart++;
    }

    result = max(result, windowEnd - windowStart + 1);
  }

  return result;
}

int main() {
  cout << findLength(vector<int>{0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1}, 2) << endl;
  cout << findLength(vector<int>{0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1}, 3) << endl;
  return 0;
}
