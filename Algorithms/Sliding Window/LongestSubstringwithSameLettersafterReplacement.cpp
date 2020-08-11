/** Problem Statement
  * Given a string with lowercase letters only, if you are allowed to replace no more than ‘k’ letters with
  * any letter, find the length of the longest substring having the same letters after replacement.
  *
  * Example 1:
  * Input: String="aabccbb", k=2
  * Output: 5
  * Explanation: Replace the two 'c' with 'b' to have a longest repeating substring "bbbbb".
  *
  * Example 2:
  * Input: String="abbcb", k=1
  * Output: 4
  * Explanation: Replace the 'c' with 'b' to have a longest repeating substring "bbbb".
  *
  * Example 3:
  * Input: String="abccde", k=1
  * Output: 3
  * Explanation: Replace the 'b' or 'd' with 'c' to have the longest repeating substring "ccc".
  */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int findLength(const string& str, int k) {
  int n = str.size(), result = 0;
  int windowStart = 0, maxCharCount = 0;
  unordered_map<char, int> charMap;
  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    char currChar = str[windowEnd];
    charMap[currChar]++;
    maxCharCount = max(maxCharCount, charMap[currChar]);

    if (windowEnd - windowStart + 1 - maxCharCount > k) {
      charMap[str[windowStart]]--;
      windowStart++;
    }

    result = max(result, windowEnd - windowStart + 1);
  }

  return result;
}

int main() {
  string s1 = "aabccbb", s2 = "abbcb", s3 = "abccde";
  cout << findLength(s1, 2) << endl;
  cout << findLength(s2, 1) << endl;
  cout << findLength(s3, 1) << endl;
  return 0;
}
