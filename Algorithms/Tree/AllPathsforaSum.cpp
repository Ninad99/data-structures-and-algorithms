/** Problem statement
  * Given a binary tree and a number ‘S’, find all paths from root-to-leaf such that
  * the sum of all the node values of each path equals ‘S’.
  */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

void findAllPathsToSum(
  TreeNode *root,
  int sum,
  vector<vector<int>>& res,
  vector<int>& currPath) {
  if (!root)
    return;

  currPath.push_back(root->val);

  if (root->val == sum && !root->left && !root->right) {
    res.push_back((vector<int>)currPath);
  } else {
    findAllPathsToSum(root->left, sum - root->val, res, currPath);
    findAllPathsToSum(root->right, sum - root->val, res, currPath);
  }

  currPath.pop_back();
}

vector<vector<int>> findPaths(TreeNode *root, int sum) {
  vector<vector<int>> res;
  vector<int> currPath;
  findAllPathsToSum(root, sum, res, currPath);
  return res;
}

int main() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->left->right = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  vector<vector<int>> result = findPaths(root, 23);
  for (auto vec : result) {
    for (auto node : vec)
      cout << node << " ";
    cout << "\n";
  }
  return 0;
}
