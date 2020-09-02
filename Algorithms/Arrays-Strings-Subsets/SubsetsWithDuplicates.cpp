/** Problem Statement
  * Given a set of numbers that might contain duplicates, find all of its distinct subsets.
  *
  * Example 1:
  * Input: [1, 3, 3]
  * Output: [], [1], [3], [1,3], [3,3], [1,3,3]
  *
  * Example 2:
  * Input: [1, 5, 3, 3]
  * Output: [], [1], [5], [3], [1,5], [1,3], [5,3], [1,5,3], [3,3], [1,3,3], [3,3,5], [1,5,3,3]
  */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> findSubsets(vector<int>& arr) {
  sort(arr.begin(), arr.end());
  vector<vector<int>> subsets;
  subsets.push_back(vector<int>());

  int startIdx = 0, endIdx = 0;
  for (int i = 0; i < arr.size(); i++) {
    startIdx = 0;
    // if current element is the same as the previous then
    // generate subsets only from the subsets added in the
    // previous step
    if (i > 0 && arr[i] == arr[i - 1])
      startIdx = endIdx + 1;

    endIdx = subsets.size() - 1;

    for (int j = startIdx; j <= endIdx; j++) {
      vector<int> s(subsets[j]);
      s.push_back(arr[i]);
      subsets.push_back(s);
    }
  }

  return subsets;
}

void printResult(vector<vector<int>>& arr) {
  for (auto v : arr) {
    for (auto num : v)
      cout << num << " ";
    cout << "\n";
  }
}

int main() {
  vector<int> arr = {1, 3, 3};
  vector<vector<int>> res = findSubsets(arr);
  printResult(res);

  arr = {1, 5, 3, 3};
  res = findSubsets(arr);
  printResult(res);
  return 0;
}
