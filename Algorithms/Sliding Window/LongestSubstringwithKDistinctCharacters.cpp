/** Problem Statement
  * Given a string, find the length of the longest substring in it with no more than K distinct characters.
  *
  * Example 1:
  * Input: String="araaci", K=2
  * Output: 4
  * Explanation: The longest substring with no more than '2' distinct characters is "araa".
  *
  * Example 2:
  * Input: String="araaci", K=1
  * Output: 2
  * Explanation: The longest substring with no more than '1' distinct characters is "aa".
  *
  * Example 3:
  * Input: String="cbbebi", K=3
  * Output: 5
  * Explanation: The longest substrings with no more than '3' distinct characters are "cbbeb" & "bbebi".
  */

  #include <iostream>
  #include <string>
  #include <unordered_map>

  using namespace std;

  int findLength(const string& str, int k) {
    int len = str.size(), windowStart = 0, result = 0;
    unordered_map<char, int> charMap;

    for (int windowEnd = 0; windowEnd < len; windowEnd++) {
      int rightChar = str[windowEnd];
      charMap[rightChar]++;

      while (charMap.size() > k) {
        char leftChar = str[windowStart];
        charMap[leftChar]--;
        if (charMap[leftChar] == 0)
          charMap.erase(leftChar);
        windowStart++;
      }

      result = max(result, windowEnd - windowStart + 1);
    }

    return result;
  }

  int main() {
    string s1 = "araaci", s2 = "araaci", s3 = "cbbebi";
    cout << findLength(s1, 2) << endl;
    cout << findLength(s2, 1) << endl;
    cout << findLength(s3, 3) << endl;
    return 0;
  }
