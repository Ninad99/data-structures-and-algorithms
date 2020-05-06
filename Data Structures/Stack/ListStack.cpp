/** A generic stack implementation using a singly linked list
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

template <typename T>
class Node {
public:
  T data;
  Node<T> *next;

  static Node<T>* getNewNode(T input) {
    Node<T> *new_node = (Node<T>*)malloc(sizeof(Node<T>));
    new_node->data = input;
    new_node->next = NULL;
  }
};

template <typename T>
class Stack {
private:
  int length;
  Node<T> *top;

public:
  Stack(); // constructor
  ~Stack(); // destructor
  int size(); // returns the size of the stack
  void push(T); // adds element to top of Stack
  T pop(); // pops an element from the top of the stack and returns it
  bool isEmpty(); // returns true if stack is empty
  T peek(); // returns the top element
  bool contains(T); // returns true if element is present in stack
  void print(); // prints elements in stack
};

template <typename T>
Stack<T>::Stack() {
  length = 0;
  top = NULL;
}

template <typename T>
Stack<T>::~Stack() {
  Node<T> *current = top, *next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

template <typename T>
int Stack<T>::size() {
  return length;
}

template <typename T>
bool Stack<T>::isEmpty() {
  return length == 0;
}

template <typename T>
void Stack<T>::push(T input) {
  Node<T> *new_node = Node<T>::getNewNode(input);
  new_node->next = top;
  top = new_node;
  ++length;
}

template <typename T>
T Stack<T>::pop() {
  if (top == NULL) {
    std::cerr << "\n[pop() error] can't pop from empty stack!";
    exit(0);
  }

  Node<T> *removedNode = top;
  T removedValue = removedNode->data;
  top = top->next;
  free(removedNode);
  --length;
  return removedValue;
}

template <typename T>
T Stack<T>::peek() {
  if (top == NULL) {
    std::cerr << "\n[peek() error] can't peek empty stack!";
    exit(0);
  }

  return top->data;
}

template <typename T>
bool Stack<T>::contains(T data) {
  Node<T> *current = top;
  while (current != NULL) {
    if (current->data == data) {
      return true;
    }
    current = current->next;
  }
  return false;
}

template <typename T>
void Stack<T>::print() {
  if (top == NULL) {
    std::cout << "{}" << std::endl;
    return;
  }

  Node<T> *current = top;
  std::cout << "\n{";
  while(current != NULL) {
    if (current->next == NULL) {
      std::cout << current->data << "}" << std::endl;
    } else {
      std::cout << current->data << ", ";
    }
    current = current->next;
  }
}
