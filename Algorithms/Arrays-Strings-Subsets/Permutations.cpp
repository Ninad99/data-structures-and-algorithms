/** Problem Statement
  * Given a set of distinct numbers, find all of its permutations.
  *
  * Permutation is defined as the re-arranging of the elements of the set. For example, {1, 2, 3} has the
  * following six permutations:
  * {1, 2, 3}
  * {1, 3, 2}
  * {2, 1, 3}
  * {2, 3, 1}
  * {3, 1, 2}
  * {3, 2, 1}
  * If a set has ‘n’ distinct elements it will have n! permutations.
  *
  * Example 1:
  * Input: [1,3,5]
  * Output: [1,3,5], [1,5,3], [3,1,5], [3,5,1], [5,1,3], [5,3,1]
  */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> getPermutations(vector<int>& arr) {
  vector<vector<int>> permutations;

  queue<vector<int>> q;
  q.push(vector<int>());

  for (int num : arr) {
    int n = q.size();

    for (int i = 0; i < n; i++) {
      vector<int> p = q.front();
      q.pop();
      int size = p.size();
      for (int j = 0; j <= size; j++) {
        vector<int> temp(p);
        temp.insert(temp.begin() + j, num);
        if (temp.size() == arr.size())
          permutations.push_back(temp);
        else
          q.push(temp);
      }
    }
  }

  return permutations;
}

void solve(vector<int>& nums, int idx, vector<int>& currPermutation, vector<vector<int>>& res) {
  if (currPermutation.size() == nums.size()) {
    res.push_back(currPermutation);
  } else {
    for (int i = 0; i <= currPermutation.size(); i++) {
      vector<int> temp(currPermutation);
      temp.insert(temp.begin() + i, nums[idx]);
      solve(nums, idx + 1, temp, res);
    }
  }
}

vector<vector<int>> getPermutationsRecursive(vector<int>& arr) {
  vector<vector<int>> result;
  vector<int> currentPermutation;
  solve(arr, 0, currentPermutation, result);
  return result;
}

void printResult(vector<vector<int>>& arr) {
  for (auto v : arr) {
    for (auto num : v)
      cout << num << " ";
    cout << "\n";
  }
}

int main() {
  vector<int> arr = {1, 3, 5};
  vector<vector<int>> res = getPermutationsRecursive(arr);
  printResult(res);
  return 0;
}
