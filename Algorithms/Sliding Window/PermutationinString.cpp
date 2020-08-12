/** Problem Statement
  * Given a string and a pattern, find out if the string contains any permutation of the pattern.
  *
  * Permutation is defined as the re-arranging of the characters of the string. For example, “abc” has the following six permutations:
  * abc, acb , bac, bca, cab , cba
  * If a string has ‘n’ distinct characters it will have n!n! permutations.
  *
  * Example 1:
  * Input: String="oidbcaf", Pattern="abc"
  * Output: true
  * Explanation: The string contains "bca" which is a permutation of the given pattern.
  *
  * Example 2:
  * Input: String="odicf", Pattern="dc"
  * Output: false
  * Explanation: No permutation of the pattern is present in the given string as a substring.
  *
  * Example 3:
  * Input: String="bcdxabcdy", Pattern="bcdyabcdx"
  * Output: true
  * Explanation: Both the string and the pattern are a permutation of each other.
  *
  * Example 4:
  * Input: String="aaacb", Pattern="abc"
  * Output: true
  * Explanation: The string contains "acb" which is a permutation of the given pattern.
  */

  #include <iostream>
  #include <string>
  #include <unordered_map>

  using namespace std;

  bool findPermutation(const string& str, const string& pattern) {
    int n = str.size(), reqStrSize = pattern.size();
    unordered_map<char, int> charFreqMap;
    for (int i = 0; i < reqStrSize; i++) // count frequency of characters in required pattern
      charFreqMap[pattern[i]]++;

    int windowStart = 0, matched = 0;
    for (int windowEnd = 0; windowEnd < n; windowEnd++) {
      if (charFreqMap.find(str[windowEnd]) != charFreqMap.end()) {
        charFreqMap[str[windowEnd]]--;
        if (charFreqMap[str[windowEnd]] == 0)
          matched++;
      }

      if (matched == charFreqMap.size())
        return true;

      if (windowEnd >= reqStrSize - 1) {
        if (charFreqMap.find(str[windowStart]) != charFreqMap.end()) {
          if (charFreqMap[str[windowStart]] == 0)
            matched--;

          charFreqMap[str[windowStart]]++;
        }
        windowStart++;
      }
    }

    return false;
  }

  int main() {
    cout << findPermutation("oidbcaf", "abc") << endl;
    cout << findPermutation("odicf", "dc") << endl;
    cout << findPermutation("bcdxabcdy", "bcdyabcdx") << endl;
    cout << findPermutation("aaacb", "abc") << endl;
    return 0;
  }
