/** Problem statement
  * Given a binary tree, find the length of its diameter. The diameter of a tree is the number of nodes on the
  * longest path between any two leaf nodes. The diameter of a tree may or may not pass through the root.
  */

#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

int solve(TreeNode *root, int& result) {
  if (!root)
    return 0;

  int leftHeight = solve(root->left, result);
  int rightHeight = solve(root->right, result);

  result = max(result, 1 + leftHeight + rightHeight);

  return max(leftHeight, rightHeight) + 1;
}

int getDiameter(TreeNode *root) {
  int result = 0;
  solve(root, result);
  return result;
}

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(7);
  root->right = new TreeNode(9);
  root->left->left = new TreeNode(6);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(2);
  root->right->right = new TreeNode(3);
  cout << getDiameter(root) << endl;
  return 0;
}
