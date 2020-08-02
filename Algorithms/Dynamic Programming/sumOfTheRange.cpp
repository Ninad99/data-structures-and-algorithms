/** Problem statement:
  * You are being given an integer array named my_array. You need to find the sum
  * of elements between indices i and j (i <= j) inclusive.
  * There are multiple queries that need to be answered.
  */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
  vector<int> sum_until;

public:
  Solution(vector<int> arr) {
    int n = arr.size();
    sum_until = vector<int>(n, 0);
    sum_until[0] = arr[0];
    for (int i = 1; i < n; i++) {
      sum_until[i] = sum_until[i - 1] + arr[i];
    }
  }

  int sumRange(int i, int j) {
    if (i == 0)
      return sum_until[j];
    else
      return sum_until[j] - sum_until[i - 1];
  }
};

int main() {
  vector<int> my_array = { 1, -2, 3, 10, -8, 0 };
  Solution s(my_array);
  cout << s.sumRange(0, 2) << endl;
  cout << s.sumRange(1, 4) << endl;
  cout << s.sumRange(3, 3) << endl;
  return 0;
}
