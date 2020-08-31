/** Problem statement
  * Given a binary tree and a number ‘S’, find all paths in the tree such that
  * the sum of all the node values of each path equals ‘S’. Please note that the
  * paths can start or end at any node but all paths must follow direction from
  * parent to child (top to bottom).
  */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

int solve(TreeNode *root, int S, vector<int>& currentPath) {
  if (!root)
    return 0;

  int paths = 0;

  currentPath.push_back(root->val);
  int sum = 0;
  for (auto itr = currentPath.rbegin(); itr != currentPath.rend(); itr++) {
    sum += *itr;

    if (sum == S)
      paths++;
  }

  paths += solve(root->left, S, currentPath);
  paths += solve(root->right, S, currentPath);

  currentPath.pop_back();

  return paths;
}

int countPaths(TreeNode *root, int S) {
  vector<int> currentPath;
  return solve(root, S, currentPath);
}

int main() {
  // TreeNode *root = new TreeNode(1);
  // root->left = new TreeNode(7);
  // root->right = new TreeNode(9);
  // root->left->left = new TreeNode(6);
  // root->left->right = new TreeNode(5);
  // root->right->left = new TreeNode(2);
  // root->right->right = new TreeNode(3);
  // cout << countPaths(root, 12) << endl;

  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  cout << countPaths(root, 11) << endl;
  return 0;
}
