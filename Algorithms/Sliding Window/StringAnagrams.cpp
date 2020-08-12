/** Problem Statement
  * Given a string and a pattern, find all anagrams of the pattern in the given string.
  *
  * Anagram is actually a Permutation of a string. For example, “abc” has the following six anagrams:
  * abc, acb, bac, bca, cab, cba
  * Write a function to return a list of starting indices of the anagrams of the pattern in the given string.
  *
  * Example 1:
  * Input: String="ppqp", Pattern="pq"
  * Output: [1, 2]
  * Explanation: The two anagrams of the pattern in the given string are "pq" and "qp".
  *
  * Example 2:
  * Input: String="abbcabc", Pattern="abc"
  * Output: [2, 3, 4]
  * Explanation: The three anagrams of the pattern in the given string are "bca", "cab", and "abc".
  */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> findStringAnagrams(const string& str, const string& pattern) {
  int n = str.size(), windowStart = 0, matched = 0;
  unordered_map<char, int> charFreqMap;
  for (int i = 0; i < pattern.size(); i++)
    charFreqMap[pattern[i]]++;

  vector<int> result;
  for (int windowEnd = 0; windowEnd < n; windowEnd++) {
    if (charFreqMap.find(str[windowEnd]) != charFreqMap.end()) {
      charFreqMap[str[windowEnd]]--;

      if (charFreqMap[str[windowEnd]] == 0)
        matched++;
    }

    if (matched == charFreqMap.size())
      result.push_back(windowStart);

    if (windowEnd >= pattern.size() - 1) {
      if (charFreqMap.find(str[windowStart]) != charFreqMap.end()) {
        if (charFreqMap[str[windowStart]] == 0)
          matched--;

        charFreqMap[str[windowStart]]++;
      }
      windowStart++;
    }
  }

  return result;
}

int main() {
  vector<int> result1 = findStringAnagrams("ppqp", "pq");
  vector<int> result2 = findStringAnagrams("abbcabc", "abc");

  for (int i = 0; i < result1.size(); i++)
    cout << result1[i] << " ";
  cout << endl;

  for (int i = 0; i < result2.size(); i++)
    cout << result2[i] << " ";
  cout << endl;
  return 0;
}
