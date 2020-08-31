/** Problem statement
  * Given a binary tree and a number sequence, find if the sequence is present
  * as a root-to-leaf path in the given tree.
  */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

bool solve(TreeNode *root, const vector<int>& seq, int idx) {
  if (!root || idx >= seq.size() || root->val != seq[idx])
    return false;

  if ((!root->left && !root->right) && (idx == seq.size() - 1))
    return true;

  return solve(root->left, seq, idx + 1) || solve(root->right, seq, idx + 1);
}

bool findPathSequence(TreeNode *root, const vector<int>& seq) {
  if (!root)
    return false;

  return solve(root, seq, 0);
}

int main() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->left->right = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  root->right->left->left = new TreeNode(11);
  vector<int> seq = {12, 1, 10, 11};
  if (findPathSequence(root, seq))
    cout << "Sequence exists" << endl;
  else
    cout << "Nope" << endl;
  return 0;
}
