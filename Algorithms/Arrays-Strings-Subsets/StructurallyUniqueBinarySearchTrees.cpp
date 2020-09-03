/** Problem Statement
  * Given a number ‘n’, write a function to return all structurally unique Binary Search Trees (BST) that can
  * store values 1 to ‘n’?
  *
  * Example 1:
  * Input: 2
  * Output: 2
  *
  * Example 2:
  * Input: 3
  * Output: 5
  */

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<TreeNode*> findUniqueTreesRecursive(int start, int end) {
  vector<TreeNode*> result;

  if (start > end) {
    result.push_back(NULL);
    return result;
  }

  for (int i = start; i <= end; i++) {
    vector<TreeNode*> leftSubtree = findUniqueTreesRecursive(start + 1, i);
    vector<TreeNode*> rightSubtree = findUniqueTreesRecursive(i + 1, end);

    for (auto left : leftSubtree) {
      for (auto right : rightSubtree) {
        TreeNode *root = new TreeNode(i);
        root->left = left;
        root->right = right;
        result.push_back(root);
      }
    }
  }

  return result;
}

vector<TreeNode*> findUniqueTrees(int n) {
  if (n <= 0)
    return vector<TreeNode*>();

  return findUniqueTreesRecursive(1, n);
}

int main() {
  vector<TreeNode*> res = findUniqueTrees(2);
  cout << res.size() << endl;

  res = findUniqueTrees(3);
  cout << res.size() << endl;
  return 0;
}
