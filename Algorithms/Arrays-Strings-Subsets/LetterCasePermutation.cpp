/** Problem Statement
  * Given a string, find all of its permutations preserving the character sequence but changing case.
  *
  * Example 1:
  * Input: "ad52"
  * Output: "ad52", "Ad52", "aD52", "AD52"
  *
  * Example 2:
  * Input: "ab7c"
  * Output: "ab7c", "Ab7c", "aB7c", "AB7c", "ab7C", "Ab7C", "aB7C", "AB7C"
  */

#include <iostream>
#include <vector>

using namespace std;

vector<string> letterCasePermutation(string s) {
  vector<string> result;
  if (s.size() == 0)
    return result;

  result.push_back(s);

  for (int i = 0; i < s.size(); i++) {
    if (isalpha(s[i])) {
      int n = result.size();

      for (int j = 0; j < n; j++) {
        vector<char> arr(result[j].begin(), result[j].end());

        if (islower(arr[i])) {
          arr[i] = toupper(arr[i]);
        } else if (isupper(arr[i])) {
          arr[i] = tolower(arr[i]);
        }

        result.push_back(string(arr.begin(), arr.end()));
      }
    }
  }

  return result;
}

void printResult(vector<string>& arr) {
  for (auto s : arr) {
    cout << s << " ";
  }
  cout << "\n";
}

int main() {
  string s = "ad52";
  vector<string> res = letterCasePermutation(s);
  printResult(res);

  s = "ab7c";
  res = letterCasePermutation(s);
  printResult(res);
  return 0;
}
