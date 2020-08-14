/** Problem Statement
  * Given an array of unsorted numbers and a target number, find all unique quadruplets in it, whose sum
  * is equal to the target number.
  *
  * Example 1:
  * Input: [4, 1, 2, -1, 1, -3], target=1
  * Output: [-3, -1, 1, 4], [-3, 1, 1, 2]
  * Explanation: Both the quadruplets add up to the target.
  *
  * Example 2:
  * Input: [2, 0, -1, 1, -2, 2], target=2
  * Output: [-2, 0, 2, 2], [-1, 0, 1, 2]
  * Explanation: Both the quadruplets add up to the target.
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void searchPair(vector<int>& nums, int targetSum, int first, int second, vector<vector<int>>& result) {
  int left = second + 1;
  int right = nums.size() - 1;
  while (left < right) {
    int sum = nums[first] + nums[second] + nums[left] + nums[right];
    if (sum == targetSum) {
      result.push_back({ nums[first], nums[second], nums[left], nums[right] });
      left++;
      right--;
      while (left < right && nums[left] == nums[left - 1]) left++;
      while (left < right && nums[right] == nums[right + 1]) right--;
    } else if (sum < targetSum) {
      left++;
    } else {
      right--;
    }
  }
}

vector<vector<int>> searchQuadruplets(vector<int>& nums, int target) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> quadruplets;
  int n = nums.size(), left, right;
  for (int i = 0; i < n - 3; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue;

    for (int j = i + 1; j < n - 2; j++) {
      if (j > i + 1 && nums[j] == nums[j - 1]) continue;

      searchPair(nums, target, i, j, quadruplets);
    }
  }

  return quadruplets;
}

void print(vector<vector<int>>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<int> arr = {4, 1, 2, -1, 1, -3};
  vector<vector<int>> result = searchQuadruplets(arr, 1);
  print(result);

  arr = {2, 0, -1, 1, -2, 2};
  result = searchQuadruplets(arr, 2);
  print(result);

  return 0;
}
