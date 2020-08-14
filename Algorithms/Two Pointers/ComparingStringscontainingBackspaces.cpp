/** Problem statement
  * Given two strings containing backspaces (identified by the character ‘#’), check if the two strings are equal.
  *
  * Example 1:
  * Input: str1="xy#z", str2="xzz#"
  * Output: true
  * Explanation: After applying backspaces the strings become "xz" and "xz" respectively.
  *
  * Example 2:
  * Input: str1="xy#z", str2="xyz#"
  * Output: false
  * Explanation: After applying backspaces the strings become "xz" and "xy" respectively.
  *
  * Example 3:
  * Input: str1="xp#", str2="xyz##"
  * Output: true
  * Explanation: After applying backspaces the strings become "x" and "x" respectively.
  * In "xyz##", the first '#' removes the character 'z' and the second '#' removes the character 'y'.
  *
  * Example 4:
  * Input: str1="xywrrmp", str2="xywrrmu#p"
  * Output: true
  * Explanation: After applying backspaces the strings become "xywrrmp" and "xywrrmp" respectively.
  */

#include <iostream>
#include <string>

using namespace std;

int getNextValidIndex(const string& str, int i) {
  int backspaceCount = 0;
  while (i >= 0) {
    if (str[i] == '#') {
      backspaceCount++;
    } else if (backspaceCount > 0) {
      backspaceCount--;
    } else {
      break;
    }

    i--;
  }

  return i;
}

bool compare(const string& str1, const string& str2) {
  int idx1 = str1.size() - 1, idx2 = str2.size() - 1;
  while (idx1 >= 0 && idx2 >= 0) {
    int i1 = getNextValidIndex(str1, idx1);
    int i2 = getNextValidIndex(str2, idx2);

    if (i1 < 0 && i2 < 0) return true;

    if (i1 < 0 || i2 < 0) return false;

    if (str1[i1] != str2[i2]) return false;

    idx1 = i1 - 1;
    idx2 = i2 - 1;
  }

  return true;
}

int main() {
  cout << compare("xy#z", "xzz#") << endl;
  cout << compare("xy#z", "xyz#") << endl;
  cout << compare("xp#", "xyz##") << endl;
  cout << compare("xywrrmp", "xywrrmu#p") << endl;
  return 0;
}
