/** Problem statement
  * Any number will be called a happy number if, after repeatedly replacing it with a number equal to the
  * sum of the square of all of its digits, leads us to number ‘1’. All other (not-happy) numbers will never
  * reach ‘1’. Instead, they will be stuck in a cycle of numbers which does not include ‘1’.
  *
  * Example 1:
  * Input: 23
  * Output: true (23 is a happy number)
  * Explanations: Here are the steps to find out that 23 is a happy number:
  * 2^2 + 3^2 = 4 + 9 = 13
  * 1^2 + 3^2 = 1 + 9 = 10
​​  * 1^2 + 0^2 = 1 + 0 = 1
  *
  * Example 2:
  * Input: 12
  * Output: false (12 is not a happy number)
  */

#include <iostream>

using namespace std;

int getSquare(int num) {
  int sum = 0, rem;
  while (num > 0) {
    rem = num % 10;
    sum += rem * rem;
    num /= 10;
  }

  return sum;
}

bool isHappyNumber(int num) {
  int slow = num, fast = num;
  do {
    slow = getSquare(slow);
    fast = getSquare(getSquare(fast));
  } while (slow != fast);

  return slow == 1;
}

int main() {
  cout << isHappyNumber(23) << endl;
  cout << isHappyNumber(12) << endl;
}
