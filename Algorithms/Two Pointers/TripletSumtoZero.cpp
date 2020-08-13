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
#include <algorithm>

using namespace std;

vector<vector<int>> searchTriplets(vector<int>& arr) {
  vector<vector<int>> triplets;
  sort(arr.begin(), arr.end());
  int n = arr.size(), left, right, sum;
  for (int i = 0; i < n - 2; i++) {
    if (arr[i] == arr[i + 1]) continue;
    left = i + 1;
    right = n - 1;
    while (left < right) {
      sum = arr[left] + arr[right];

      if (sum == (-arr[i])) {
        triplets.push_back({ arr[i], arr[left], arr[right] });
        left++;
        right--;
        while (left < right && arr[left] == arr[left - 1])
          left++;
        while (right > left && arr[right] == arr[right + 1])
          right--;
      }
      else if (sum < (-arr[i]))
        left += 1;
      else if (sum > (-arr[i]))
        right -= 1;
    }
  }

  return triplets;
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
