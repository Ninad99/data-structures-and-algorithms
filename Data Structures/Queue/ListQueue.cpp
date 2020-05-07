/** A generic queue implementation using a singly linked list
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
class Queue {
private:
  int length;
  Node<T> *head, *tail;

public:
  Queue(); // constructor
  ~Queue(); // destructor
  int size(); // return size of Queue
  bool isEmpty(); // returns true if queue is empty
  void enqueue(T); // adds element to back of queue
  T dequeue(); // removes element from the front of queue and returns it
  T front(); // returns the front element
  T back(); // returns the last element
  bool contains(T); // returns true if queue contains value
  void print(); // prints the queue
};

template <typename T>
Queue<T>::Queue() {
  length = 0;
  head = tail = NULL;
}

template <typename T>
Queue<T>::~Queue() {
  Node<T> *next = NULL, *current = head;

  while(current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

template <typename T>
int Queue<T>::size() {
  return length;
}

template <typename T>
bool Queue<T>::isEmpty() {
  return length == 0;
}

template <typename T>
void Queue<T>::enqueue(T data) {
  if (head == NULL) {
    head = tail = Node<T>::getNewNode(data);
    ++length;
    return;
  }

  Node<T> *new_node = Node<T>::getNewNode(data);
  tail->next = new_node;
  tail = new_node;
  ++length;
}

template <typename T>
T Queue<T>::dequeue() {
  if (head == NULL) {
    std::cerr << "\n[dequeue() error] can't dequeue from empty queue!";
    exit(0);
  }

  if (head == tail) {
    Node<T> *removedNode = head;
    T removedValue = removedNode->data;
    head = tail = NULL;
    free(removedNode);
    --length;
    return removedValue;
  }

  Node<T> *removedNode = head;
  T removedValue = removedNode->data;
  head = head->next;
  free(removedNode);
  --length;
  return removedValue;
}

template <typename T>
T Queue<T>::front() {
  if (head == NULL) {
    std::cerr << "\n[front() error] can't get front of empty queue!";
    exit(0);
  }

  return head->data;
}

template <typename T>
T Queue<T>::back() {
  if (head == NULL) {
    std::cerr << "\n[back() error] can't get back of empty queue!";
    exit(0);
  }

  return tail->data;
}

template <typename T>
bool Queue<T>::contains(T data) {
  Node<T> *current = head;

  while (current != NULL) {
    if (current->data == data) {
      return true;
    }
    current = current->next;
  }

  return false;
}

template <typename T>
void Queue<T>::print() {
  if (length == 0) {
    std::cout << "\n{}" << std::endl;
    return;
  }

  Node<T> *current = head;
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
