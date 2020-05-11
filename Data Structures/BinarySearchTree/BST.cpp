/** An implementation of a Binary Search Tree data structure
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>

template <typename T>
class Node {
public:
  T data;
  Node<T> *left, *right;

  static Node<T>* getNewNode(T data) {
    Node<T> *new_node = (Node<T>*)malloc(sizeof(Node<T>));
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
  }
};

template <typename T>
int compare(T x, T y) {
  if (x < y)
    return -1;
  else if (x > y)
    return 1;
  else
    return 0;
}

int compare(const char* x, const char* y) {
  return std::strcmp(x, y);
}

template <typename T>
class BinarySearchTree {
private:
  int nodeCount;
  Node<T> *root;
  bool containsUtil(Node<T>*, T); // helper function to check if a value is in the BST
  Node<T>* removeUtil(Node<T>*, T); // helper function to remove a node
  Node<T>* insertUtil(Node<T>*, T); // helper function to insert a node
  void removeTreeData(Node<T>*); // helper function to free allocated memory
  Node<T>* leftmost(Node<T>*); // finds and returns the leftmost node
  Node<T>* rightmost(Node<T>*); // finds and returns the rightmost node
  int heightUtil(Node<T>*); // helper function to find the height of BST
  void PreorderUtil(Node<T>*); // helper function for preorder traversal
  void InorderUtil(Node<T>*); // helper function for inorder traversal
  void PostorderUtil(Node<T>*); // helper function for postorder traversal

public:
  BinarySearchTree();
  ~BinarySearchTree();
  bool isEmpty(); // returns if BST is is empty
  int size(); // returns the number of nodes in the BST
  bool contains(T); // returns true if element exists in BST
  bool insert(T); // returns true if element is inserted successfully
  bool remove(T); // remove the value from the BST
  int height(); // returns the height of the BST
  void Preorder(); // preorder traversal
  void Inorder(); // inorder traversal
  void Postorder(); // postorder traversal
  void Levelorder(); // levelorder traversal
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
  std::cout << "\nIn constructor\n";
  nodeCount = 0;
  root = NULL;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  std::cout << "\nIn destructor\n";
  removeTreeData(root);
}

template <typename T>
void BinarySearchTree<T>::removeTreeData(Node<T> *root) {
  if (root == NULL)
    return;

  removeTreeData(root->left);
  removeTreeData(root->right);
  free(root);
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() {
  return nodeCount == 0;
}

template <typename T>
int BinarySearchTree<T>::size() {
  return nodeCount;
}

template <typename T>
Node<T>* BinarySearchTree<T>::leftmost(Node<T> *root) {
  Node<T> *temp = root;
  while(temp->left != NULL)
    temp = temp->left;
  return temp;
}

template <typename T>
Node<T>* BinarySearchTree<T>::rightmost(Node<T> *root) {
  Node<T> *temp = root;
  while(temp->right != NULL)
    temp = temp->right;
  return temp;
}

template <typename T>
bool BinarySearchTree<T>::contains(T data) {
  if (root == NULL)
    return false;
  else
    return containsUtil(root, data);
}

template <typename T>
bool BinarySearchTree<T>::containsUtil(Node<T>* root, T data) {
  if (root == NULL)
    return false;

  if (compare(root->data, data) < 0)
    return containsUtil(root->left, data);
  else if (compare(root->data, data) > 0)
    return containsUtil(root->right, data);
  else
    return true;
}

template <typename T>
bool BinarySearchTree<T>::insert(T data) {
  if (!contains(data)) {
    root = insertUtil(root, data);
    ++nodeCount;
    return true;
  } else {
    return false;
  }
}

template <typename T>
Node<T>* BinarySearchTree<T>::insertUtil(Node<T> *node, T data) {
  if (node == NULL) {
    node = Node<T>::getNewNode(data);
  }

  // if current node's data is greater than input data, go left
  if (compare(node->data, data) > 0) {
    node->left = insertUtil(node->left, data);
  }
  // if current node's data is lesser than input data, go right
  else if (compare(node->data, data) < 0) {
    node->right = insertUtil(node->right, data);
  }

  return node;
}

template <typename T>
bool BinarySearchTree<T>::remove(T data) {
  if (contains(data)) {
    root = removeUtil(root, data);
    --nodeCount;
    return true;
  } else {
    return false;
  }
}

template <typename T>
Node<T>* BinarySearchTree<T>::removeUtil(Node<T> *node, T data) {
  if (node == NULL)
    return node;
  // if current node's data is less than the data to be removed, go to right subtree
  if (compare(node->data, data) < 0)
    node->right = removeUtil(node->right, data);
  // if current node's data is greater than the data to be removed, go to left subtree
  else if (compare(node->data, data) > 0)
    node->left = removeUtil(node->left, data);
  // else found the node to be removed
  else {
    // is leaf node
    if (!node->left && !node->right) {
      free(node);
    }
    // has only right subtree
    else if (!node->left) {
      Node<T>* right_child = node->right;
      free(node);
      return right_child;
    }
    // has only left subtree
    else if (!node->right) {
      Node<T>* left_child = node->left;
      free(node);
      return left_child;
    }
    // has both left and right subtree
    else {
      Node<T>* smallest = leftmost(node->right); // find leftmost of right subtree
      node->data = smallest->data; // copy it's value to the current node
      node->right = removeUtil(node->right, smallest->data);
    }
  }

  return node;
}

template <typename T>
int BinarySearchTree<T>::height() {
  return heightUtil(root);
}

template <typename T>
int BinarySearchTree<T>::heightUtil(Node<T> *root) {
  if (root == NULL)
    return 0;
  else
    return std::max(heightUtil(root->left), heightUtil(root->right)) + 1;
}

template <typename T>
void BinarySearchTree<T>::PreorderUtil(Node<T>* root) {
  if (root == NULL)
    return;

  std::cout << root->data << " ";
  PreorderUtil(root->left);
  PreorderUtil(root->right);
}

template <typename T>
void BinarySearchTree<T>::InorderUtil(Node<T>* root) {
  if (root == NULL)
    return;

  InorderUtil(root->left);
  std::cout << root->data << " ";
  InorderUtil(root->right);
}

template <typename T>
void BinarySearchTree<T>::PostorderUtil(Node<T>* root) {
  if (root == NULL)
    return;

  PostorderUtil(root->left);
  PostorderUtil(root->right);
  std::cout << root->data << " ";
}

template <typename T>
void BinarySearchTree<T>::Preorder() {
  std::cout << "\nPreorder traversal: ";
  PreorderUtil(root);
  std::cout << "\n";
}

template <typename T>
void BinarySearchTree<T>::Inorder() {
  std::cout << "\nInorder traversal: ";
  InorderUtil(root);
  std::cout << "\n";
}

template <typename T>
void BinarySearchTree<T>::Postorder() {
  std::cout << "\nPostorder traversal: ";
  PostorderUtil(root);
  std::cout << "\n";
}

template <typename T>
void BinarySearchTree<T>::Levelorder() {
  if (root == NULL)
    return;

  std::queue<Node<T>* > q;
  q.push(root);
  std::cout << "\nLevel order traversal: ";
  while(!q.empty()) {
    Node<T> *current = q.front();

    std::cout << current->data << " ";

    if (current->left)
      q.push(current->left);

    if (current->right)
      q.push(current->right);

    q.pop();
  }
  std::cout << "\n";
}
