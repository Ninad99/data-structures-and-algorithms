#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

bool isBalanced(string str) {
  int count = 0;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == '(') count++;
    if (str[i] == ')') count--;
    if (count < 0) return false;
  }

  if (count == 0) return true;
  else return false;
}

int main() {
  string s = "(())(a))";
  cout << s.substr(2);
  map<string, bool> visited;
  queue<string> q;
  vector<string> result;

  q.push(s);

  while (!q.empty()) {
    string current = q.front(); q.pop();
    if (visited[current]) {
        cout << "\nAlready visited " << current;
        continue;
    }

    visited[current] = true;

    if (isBalanced(current)) {
      result.push_back(current);
    }

    for (int i = 0; i < current.size(); i++) {
      if (current[i] == '(' || current[i] == ')') {
        string child = current.substr(0, i) + current.substr(i + 1);
        cout << "\nNode: " << child;
        q.push(child);
      }
    }
  }

  cout << "\nResult: [";
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  cout << "]" << endl;
  return 0;
}
