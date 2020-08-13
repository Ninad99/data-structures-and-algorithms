/** Problem statement
  * Given a sorted array, create a new array containing squares of all the number of the input array in the
  * sorted order.
  *
  * Example 1:
  * Input: [-2, -1, 0, 2, 3]
  * Output: [0, 1, 4, 4, 9]
  *
  * Example 2:
  * Input: [-3, -1, 0, 1, 2]
  * Output: [0 1 1 4 9]
  */

#include <iostream>
#include <vector>

using namespace std;

vector<int> makeSquares(const vector<int>& arr) {
  int n = arr.size();
  vector<int> squares(n);
  int left = 0, right = n - 1, highestSquareIndex = n - 1;
  while (left <= right) {
    int square1 = arr[left] * arr[left];
    int square2 = arr[right] * arr[right];

    if (square1 > square2) {
      squares[highestSquareIndex--] = square1;
      left += 1;
    } else {
      squares[highestSquareIndex--] = square2;
      right -= 1;
    }
  }

  return squares;
}

void print(vector<int>& arr) {
  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {-2, -1, 0, 2, 3};
  vector<int> result = makeSquares(arr);
  print(result);

  arr = {-3, -1, 0, 1, 2};
  result = makeSquares(arr);
  print(result);

  return 0;
}
