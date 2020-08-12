/** Problem Statement
  * Given a string and a pattern, find the smallest substring in the given string
  * which has all the characters of the given pattern.
  *
  * Example 1:
  * Input: String="aabdec", Pattern="abc"
  * Output: "abdec"
  * Explanation: The smallest substring having all characters of the pattern is "abdec"
  *
  * Example 2:
  * Input: String="abdabca", Pattern="abc"
  * Output: "abc"
  * Explanation: The smallest substring having all characters of the pattern is "abc".
  *
  * Example 3:
  * Input: String="adcad", Pattern="abc"
  * Output: ""
  * Explanation: No substring in the given string has all characters of the pattern.
  */

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

string findSubstring(const string& str, const string& pattern) {
  int n = str.size(), patternSize = pattern.size();
  unordered_map<char, int> charFreqMap;
  for (int i = 0; i < patternSize; i++)
    charFreqMap[pattern[i]]++;

  int matched = 0, windowStart = 0, minLength = n + 1, subStrStart = 0;
  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    if (charFreqMap.find(str[windowEnd]) != charFreqMap.end()) {
      charFreqMap[str[windowEnd]]--;

      if (charFreqMap[str[windowEnd]] >= 0) matched++;
    }

    while (matched == patternSize) {
        if (minLength > windowEnd - windowStart + 1) {
          minLength = windowEnd - windowStart + 1;
          subStrStart = windowStart;
        }

        if (charFreqMap.find(str[windowStart]) != charFreqMap.end()) {
          if (charFreqMap[str[windowStart]] == 0)
            matched--;

          charFreqMap[str[windowStart]]++;
        }
        windowStart++;
    }
  }
  return minLength > n ? "" : str.substr(subStrStart, minLength);
}

int main() {
  cout << findSubstring("aabdec", "abc") << endl;
  cout << findSubstring("abdabca", "abc") << endl;
  cout << findSubstring("adcad", "abc") << endl;
  return 0;
}
