/** Problem Statement
  * Given an expression containing digits and operations (+, -, *), find all possible ways in which the
  * expression can be evaluated by grouping the numbers and operators using parentheses.
  *
  * Example 1:
  * Input: "1+2*3"
  * Output: 7, 9
  * Explanation: 1+(2*3) => 7 and (1+2)*3 => 9
  *
  * Example 2:
  * Input: "2*3-4-5"
  * Output: 8, -12, 7, -7, -3
  * Explanation: 2*(3-(4-5)) => 8, 2*(3-4-5) => -12, 2*3-(4-5) => 7, 2*(3-4)-5 => -7, (2*3)-4-5 => -3
  */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<int>> m;

vector<int> evaluateExpression(string expr) {
  vector<int> result;

  if (m.find(expr) != m.end())
    return m[expr];

  if (expr.find("+") == string::npos && expr.find("-") == string::npos && expr.find("*") == string::npos) {
    result.push_back(stoi(expr));
  } else {
    for (int i = 0; i < expr.size(); i++) {
      if (!isdigit(expr[i])) {
        vector<int> leftHalf = evaluateExpression(expr.substr(0, i));
        vector<int> rightHalf = evaluateExpression(expr.substr(i + 1));

        for (auto part1 : leftHalf) {
          for (auto part2 : rightHalf) {
            if (expr[i] == '+') {
              result.push_back(part1 + part2);
            } else if (expr[i] == '-') {
              result.push_back(part1 - part2);
            } else if (expr[i] == '*') {
              result.push_back(part1 * part2);
            }
          }
        }
      }
    }
  }

  m[expr] = result;
  return result;
}

void printResult(vector<int>& arr) {
  for (auto s : arr) {
    cout << s << " ";
  }
  cout << "\n";
}

int main() {
  vector<int> res = evaluateExpression("1+2*3");
  printResult(res);

  res = evaluateExpression("2*3-4-5");
  printResult(res);
  return 0;
}
