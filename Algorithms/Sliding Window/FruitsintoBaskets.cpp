/** Problem Statement
  * Given an array of characters where each character represents a fruit tree,
  * you are given two baskets and your goal is to put maximum number of fruits in each basket.
  * The only restriction is that each basket can have only one type of fruit.
  *
  * You can start with any tree, but once you have started you can’t skip a tree.
  * You will pick one fruit from each tree until you cannot, i.e., you will stop when you have to pick from a third fruit type.
  * Write a function to return the maximum number of fruits in both the baskets.
  *
  * Example 1:
  * Input: Fruit=['A', 'B', 'C', 'A', 'C']
  * Output: 3
  * Explanation: We can put 2 'C' in one basket and one 'A' in the other from the subarray ['C', 'A', 'C']
  *
  * Example 2:
  * Input: Fruit=['A', 'B', 'C', 'B', 'B', 'C']
  * Output: 5
  * Explanation: We can put 3 'B' in one basket and two 'C' in the other basket.
  * This can be done if we start with the second letter: ['B', 'C', 'B', 'B', 'C']
  */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int findLength(vector<char> arr) {
  int n = arr.size(), windowStart = 0, result = 0;
  unordered_map<char, int> charMap;

  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    charMap[arr[windowEnd]]++;

    while (charMap.size() > 2) {
      charMap[arr[windowStart]]--;
      if (charMap[arr[windowStart]] == 0)
        charMap.erase(arr[windowStart]);
      windowStart++;
    }

    result = max(result, windowEnd - windowStart + 1);
  }

  return result;
}

int main() {
  cout << findLength({'A', 'B', 'C', 'A', 'C'}) << endl;
  cout << findLength({'A', 'B', 'C', 'B', 'B', 'C'}) << endl;
  return 0;
}
