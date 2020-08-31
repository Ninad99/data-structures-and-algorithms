/** Problem statement
  * Find the path with the maximum sum in a given binary tree. Write a function that returns the maximum
  * sum. A path can be defined as a sequence of nodes between any two nodes and doesn’t necessarily
  * pass through the root.
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

  int leftSubtreeMaxPathSum = solve(root->left, result);
  int rightSubtreeMaxPathSum = solve(root->right, result);

  // if negative sum ignore it
  leftSubtreeMaxPathSum = max(leftSubtreeMaxPathSum, 0);
  rightSubtreeMaxPathSum = max(rightSubtreeMaxPathSum, 0);

  int localMax = leftSubtreeMaxPathSum + rightSubtreeMaxPathSum + root->val;

  result = max(result, localMax);

  return max(leftSubtreeMaxPathSum, rightSubtreeMaxPathSum) + root->val;
}

int getMaxPathSum(TreeNode *root) {
  int result = 0;
  solve(root, result);
  return result;
}

int main() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(1);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(6);
  root->right->left->left = new TreeNode(7);
  root->right->left->right = new TreeNode(8);
  root->right->right->left = new TreeNode(9);
  cout << getMaxPathSum(root) << endl;
  return 0;
}
