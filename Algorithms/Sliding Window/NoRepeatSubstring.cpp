/** Problem Statement
  * Given a string, find the length of the longest substring which has no repeating characters.
  *
  * Example 1:
  * Input: String="aabccbb"
  * Output: 3
  * Explanation: The longest substring without any repeating characters is "abc".
  *
  * Example 2:
  * Input: String="abbbb"
  * Output: 2
  * Explanation: The longest substring without any repeating characters is "ab".
  *
  * Example 3:
  * Input: String="abccde"
  * Output: 3
  * Explanation: Longest substrings without any repeating characters are "abc" & "cde".
  */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int findLength(const string& str) {
  int n = str.size(), windowStart = 0, result = 0;
  unordered_map<char, int> charMap;

  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    int currChar = str[windowEnd];

    if (charMap.find(currChar) != charMap.end())
      windowStart = max(windowStart, charMap[currChar] + 1);

    charMap[currChar] = windowEnd;
    result = max(result, windowEnd - windowStart + 1);
  }

  return result;
}

int main() {
  string s1 = "aabccbb", s2 = "abbbb", s3 = "abccde";
  cout << findLength(s1) << endl;
  cout << findLength(s2) << endl;
  cout << findLength(s3) << endl;
  return 0;
}
