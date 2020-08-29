/** Problem statement
  * Given a binary tree, connect each node with its level order successor.
  * The last node of each level should point to a null node.
  */

#include <iostream>
#include <queue>

using namespace std;


struct TreeNode {
  int val;
  TreeNode *left, *right, *next;
  TreeNode(int x): val(x), left(NULL), right(NULL), next(NULL) {}
};

void printLevelOrder(TreeNode *root) {
  if (!root)
    return;

  TreeNode *nextLevelRoot = root, *current;
  while (nextLevelRoot) {
    current = nextLevelRoot;
    nextLevelRoot = NULL;
    while (current) {
      cout << current->val << " ";
      if (!nextLevelRoot) {
        if (current->left)
          nextLevelRoot = current->left;
        else if (current->right)
          nextLevelRoot = current->right;
      }
      current = current->next;
    }
    cout << "\n";
  }
}

void connect(TreeNode *root) {
  if (root == NULL)
    return;

  queue<TreeNode*> q;
  q.push(root);
  TreeNode *curr, *prev;
  while (!q.empty()) {
    int levelSize = q.size();
    prev = NULL;
    for (int i = 0; i < levelSize; i++) {
      curr = q.front(); q.pop();

      if (prev)
        prev->next = curr;
      prev = curr;

      if (curr->left)
        q.push(curr->left);

      if (curr->right)
        q.push(curr->right);
    }
  }
}

int main() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  connect(root);
  printLevelOrder(root);
  return 0;
}
