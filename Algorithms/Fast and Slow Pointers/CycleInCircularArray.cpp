/** Problem statement
  * We are given an array containing positive and negative numbers. Suppose the array contains a number
  * ‘M’ at a particular index. Now, if ‘M’ is positive we will move forward ‘M’ indices and if ‘M’ is negative
  * move backwards ‘M’ indices. You should assume that the array is circular which means two things:
  *   1. If, while moving forward, we reach the end of the array, we will jump to the first element to
  *      continue the movement.
  *   2. If, while moving backward, we reach the beginning of the array, we will jump to the last element to
  *      continue the movement.
  * Write a method to determine if the array has a cycle. The cycle should have more than one element and
  * should follow one direction which means the cycle should not contain both forward and backward movements.
  *
  * Example 1:
  * Input: [1, 2, -1, 2, 2]
  * Output: true
  * Explanation: The array has a cycle among indices: 0 -> 1 -> 3 -> 0
  *
  * Example 2:
  * Input: [2, 2, -1, 2]
  * Output: true
  * Explanation: The array has a cycle among indices: 1 -> 3 -> 1
  *
  * Example 3:
  * Input: [2, 1, -1, -2]
  * Output: false
  * Explanation: The array does not have any cycle.
  */

#include <iostream>
#include <vector>

using namespace std;

int getNextIndex(vector<int>& arr, bool isForward, int currentIndex) {
  bool direction = arr[currentIndex] >= 0;
  if (direction != isForward)
    return -1;

  int nextIndex = (currentIndex + arr[currentIndex] + arr.size()) % arr.size();

  if (nextIndex == currentIndex)
    return -1;

  return nextIndex;
}

bool hasCycle(vector<int> arr) {
  int n = arr.size(), slow, fast;
  bool isForward;
  for (int i = 0; i < n; i++) {
    isForward = arr[i] >= 0;
    slow = i, fast = i;

    do {
      slow = getNextIndex(arr, isForward, slow);
      fast = getNextIndex(arr, isForward, fast);
      if (fast != -1) {
        fast = getNextIndex(arr, isForward, fast);
      }
    } while (slow != -1 && fast != -1 && slow != fast);

    if (slow != -1 && slow == fast)
      return true;
  }

  return false;
}

int main() {
  cout << hasCycle(vector<int>{1, 2, -1, 2, 2}) << endl;
  cout << hasCycle(vector<int>{2, 2, -1, 2}) << endl;
  cout << hasCycle(vector<int>{2, 1, -1, -2}) << endl;
  return 0;
}
