/** Problem statement
  * Given an array of sorted numbers, remove all duplicates from it. You should not use any extra space;
  * after removing the duplicates in-place return the new length of the array.
  *
  * Example 1:
  * Input: [2, 3, 3, 3, 6, 9, 9]
  * Output: 4
  * Explanation: The first four elements after removing the duplicates will be [2, 3, 6, 9].
  *
  * Example 2:
  * Input: [2, 2, 2, 11]
  * Output: 2
  * Explanation: The first two elements after removing the duplicates will be [2, 11].
  */

#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& arr) {
  int nextNonDuplicate = 1, n = arr.size();
  for (int i = 1; i < n; i++) {
    if (arr[nextNonDuplicate - 1] != arr[i]) {
      arr[nextNonDuplicate] = arr[i];
      nextNonDuplicate++;
    }
  }

  return nextNonDuplicate;
}

int main() {
  vector<int> arr = {2, 3, 3, 3, 6, 9, 9};
  cout << removeDuplicates(arr) << endl;

  arr = {2, 2, 2, 11};
  cout << removeDuplicates(arr) << endl;

  return 0;
}
