/** Problem statement
  * Given an array of unsorted numbers, find all unique triplets in it that add up to zero.
  *
  * Example 1:
  * Input: [-3, 0, 1, 2, -1, 1, -2]
  * Output: [-3, 1, 2], [-2, 0, 2], [-2, 1, 1], [-1, 0, 1]
  * Explanation: There are four unique triplets whose sum is equal to zero.
  *
  * Example 2:
  * Input: [-5, 2, -1, -2, 3]
  * Output: [[-5, 2, 3], [-2, -1, 3]]
  * Explanation: There are two unique triplets whose sum is equal to zero.
  */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void searchPair(vector<int>& nums, int targetSum, int left, vector<vector<int>>& result) {
    int right = nums.size() - 1, sum;
    while (left < right) {
      sum = nums[left] + nums[right];
      if (sum == targetSum) {
        result.push_back({ -targetSum, nums[left], nums[right] });
        left++; right--;
        while (left < right && nums[left] == nums[left - 1]) left++;
          while (left < right && nums[right] == nums[right + 1]) right--;
      } else if (sum < targetSum){
        left++;
      } else {
        right--;
      }
    }
  }

vector<vector<int>> searchTriplets(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> result;
  unordered_map<int, bool> numbers;
  int n = nums.size(), left, right, sum;
  for (int i = 0; i < n - 2; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;

      searchPair(nums, -nums[i], i + 1, result);
  }

  return result;
}

void print(vector<vector<int>>& arr) {
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < arr[i].size(); j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  vector<int> arr = {-3, 0, 1, 2, -1, 1, -2};
  vector<vector<int>> result = searchTriplets(arr);
  print(result);

  arr = {-5, 2, -1, -2, 3};
  result = searchTriplets(arr);
  print(result);

  return 0;
}
