/** Problem Statement
  * Given an array containing 0s, 1s and 2s, sort the array in-place. You should treat numbers of the array as
  * objects, hence, we can’t count 0s, 1s, and 2s to recreate the array.
  * The flag of the Netherlands consists of three colors: red, white and blue; and since our input array also
  * consists of three different numbers that is why it is called Dutch National Flag problem.
  *
  * Example 1:
  * Input: [1, 0, 2, 1, 0]
  * Output: [0 0 1 1 2]
  *
  * Example 2:
  * Input: [2, 2, 0, 1, 2, 0]
  * Output: [0 0 1 2 2 2 ]
  */

#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int>& arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

void sortArray(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;

    for (int i = 0; i <= high;) {
      if (arr[i] == 0) {
        swap(arr, i, low);
        i++; low++;
      } else if (arr[i] == 1) {
        i++;
      } else if (arr[i] == 2) {
        swap(arr, i, high);
        high--;
      }
    }
}

void print(vector<int>& arr) {
  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {1, 0, 2, 1, 0};
  sortArray(arr);
  print(arr);

  arr = {2, 2, 0, 1, 2, 0};
  sortArray(arr);
  print(arr);

  return 0;
}
