/** Problem Statement
  * Given a string and a list of words, find all the starting indices of substrings in the given string that are a
  * concatenation of all the given words exactly once without any overlapping of words. It is given that
  * all words are of the same length.
  *
  * Example 1:
  * Input: String="catfoxcat", Words=["cat", "fox"]
  * Output: [0, 3]
  * Explanation: The two substring containing both the words are "catfox" & "foxcat".
  *
  * Example 2:
  * Input: String="catcatfoxfox", Words=["cat", "fox"]
  * Output: [3]
  * Explanation: The only substring containing both the words is "catfox".
  */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> findConcatenation(const string& str, const vector<string>& words) {
  int n = str.size(), wordsCount = words.size(), wordLength = words[0].size();
  unordered_map<string, int> wordsFreqMap;
  for (int i = 0; i < wordsCount; i++)
    wordsFreqMap[words[i]]++;

  vector<int> result;
  for (int i = 0; i <= n - (wordsCount * wordLength); i++) {
    unordered_map<string, int> seenWords;
    for (int j = 0; j < wordsCount; j++) {
      int nextWordIndex = i + (j * wordLength);
      string word = str.substr(nextWordIndex, wordLength);

      if (wordsFreqMap.find(word) == wordsFreqMap.end()) break;

      seenWords[word]++;

      if (seenWords[word] > wordsFreqMap[word]) break;

      if (j + 1 == wordsCount)
        result.push_back(i);
    }
  }
  return result;
}

int main() {
  vector<int> result = findConcatenation("catfoxcat", vector<string>{"cat", "fox"});
  for (int i = 0; i < result.size(); i++)
    cout << result[i] << " ";
  cout << endl;

  result = findConcatenation("catcatfoxfox", vector<string>{"cat", "fox"});
  for (int i = 0; i < result.size(); i++)
    cout << result[i] << " ";
  cout << endl;
  return 0;
}
