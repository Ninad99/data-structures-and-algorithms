/** Problem Statement
  * For a given number ‘N’, write a function to generate all combination of ‘N’ pairs of balanced parentheses.
  *
  * Example 1:
  * Input: N=2
  * Output: (()), ()()
  *
  * Example 2:
  * Input: N=3
  * Output: ((())), (()()), (())(), ()(()), ()()()
  */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ParenthesisString {
  string str;
  int openCount, closedCount;
};

vector<string> generateParenthesis(int n) {
  vector<string> res;
  if (n == 0)
    return res;

  queue<ParenthesisString> q;
  q.push({"", 0, 0});
  while (!q.empty()) {
    int levelSize = q.size();

    for (int i = 0; i < levelSize; i++) {
      ParenthesisString ps = q.front(); q.pop();

      if (ps.openCount == n && ps.closedCount == n)
        res.push_back(ps.str);

      if (ps.openCount < n)
        q.push({ ps.str + "(", ps.openCount + 1, ps.closedCount });

      if (ps.closedCount < ps.openCount)
        q.push({ ps.str + ")", ps.openCount, ps.closedCount + 1 });
    }
  }

  return res;
}

void solve(int n, int openCount, int closedCount, string curr, vector<string>& res) {
  if (openCount == n && closedCount == n) {
    res.push_back(curr);
  } else {
    if (openCount < n)
      solve(n, openCount + 1, closedCount, curr + "(", res);

    if (closedCount < openCount)
      solve(n, openCount, closedCount + 1, curr + ")", res);
  }
}

vector<string> generateParenthesisRecursive(int n) {
  if (n == 0)
    return {""};

  vector<string> res;
  solve(n, 0, 0, "", res);
  return res;
}

void printResult(vector<string>& arr) {
  for (string s : arr) {
    cout << s << " ";
  }
  cout << "\n";
}

int main() {
  vector<string> res = generateParenthesis(2);
  printResult(res);

  res = generateParenthesisRecursive(3);
  printResult(res);
  return 0;
}
