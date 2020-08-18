/** Problem statement:
  * You are given an array "nums" and you need to find the longest forming
  * increasing subsequence from it.
  * Longest increasing subsequence is the longest subsequence such that
  * all elements of the subsequence are sorted in increasing order
  *
  * Example:
  * Input = [11, 23, 10, 37, 21, 50, 80];
  * Output = 5
  * Explanation - The LIS is [11, 23, 37, 50, 80] which is of length 5
  */

#include <iostream>
#include <vector>

using namespace std;

int longestIncSubseq(vector<int>& nums) {
  int n = nums.size(), maxLength = 0;
  vector<int> LIS(n, 1);
  for (int i = 1; i < n; i++)
    for (int j = 0; j < i; j++)
      if (nums[j] < nums[i] && LIS[i] < LIS[j] + 1)
        LIS[i] = LIS[j] + 1;

  for (int i = 0; i < n; i++)
    maxLength = max(maxLength, LIS[i]);

  return maxLength;
}

int main() {
  vector<int> nums = {11, 23, 10, 37, 21, 50, 80};
  cout << longestIncSubseq(nums) << endl;
  return 0;
}
