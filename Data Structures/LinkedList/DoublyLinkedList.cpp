/** A generic doubly linked list implementation
  * works with primitive types
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

template <typename T>
class Node {
public:
  T data;
  Node<T> *next, *prev;

  static Node<T>* getNewNode(T inputData) {
    Node<T> *newNode = (Node<T>*)malloc(sizeof(Node<T>));
    newNode->data = inputData;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
  }
};

template <typename T>
class DoublyLinkedList {
private:
  int length;
  Node<T> *head, *tail;

public:
  DoublyLinkedList(); // constructor
  ~DoublyLinkedList(); // destructor
  int size(); // returns number of data elements in list
  bool isEmpty(); // bool returns true if empty
  void clear(); // clears the list
  T value_at(int); // returns the value of the nth item (starting at 0 for first)
  void push_front(T); // adds an item to the front of the list
  T pop_front(); // remove front item and return its value
  void push_back(T); // adds an item at the end
  T pop_back(); // removes end item and returns its value
  T front(); // get value of front item
  T back(); // get value of end item
  void insert_at(int, T); // insert value at index, so current item at that index is pointed to by new item at index
  T remove_at(int); // removes node at given index
  T value_n_from_end(int); // returns the value of the node at nth position from the end of the list
  void reverse(); // reverses the list
  T remove_value(T); // removes the first item in the list with this value
  void printList(); // prints the list
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  length = 0;
  head = tail = NULL;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node<T> *current = head, *next;
  while(current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

template <typename T>
int DoublyLinkedList<T>::size() {
  return length;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() {
  return length == 0;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
  Node<T> *current = head, *next;
  while(current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  head = tail = NULL;
  length = 0;
}

template <typename T>
T DoublyLinkedList<T>::value_at(int index) {
  if (index == 0) {
    return front();
  }
  Node<T> *current;
  int count, position;
  try {
    if (index >= length) {
      throw "\n[value_at() exception] Index out of bounds!";
    }
    if (index > (length/2)) {
      current = tail;
      count = 0;
      position = length - index - 1;
      while(count < position) {
        current = current->prev;
        ++count;
      }
      return current->data;
    } else {
      current = head;
      count = 0;
      position = index;
      while(count < position) {
        current = current->next;
        ++count;
      }
      return current->data;
    }
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void DoublyLinkedList<T>::push_front(T inputData) {
  if (head == NULL) {
    head = Node<T>::getNewNode(inputData);
    tail = head;
    ++length;
    return;
  }

  head->prev = Node<T>::getNewNode(inputData);
  head->prev->next = head;
  head = head->prev;
  ++length;
}

template <typename T>
T DoublyLinkedList<T>::pop_front() {
  if (length == 1) {
    Node<T> *current = head;
    T removedValue = current->data;
    tail = NULL;
    head = NULL;
    free(current);
    --length;
    return removedValue;
  }

  try {
    if (head == NULL) {
      throw "\n[pop_front() exception] can't pop front of an empty list!";
    }

    Node<T> *current = head;
    T removedValue = current->data;
    head = head->next;
    head->prev = NULL;
    free(current);
    --length;
    return removedValue;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void DoublyLinkedList<T>::push_back(T inputData) {
  if (head == NULL) {
    head = tail = Node<T>::getNewNode(inputData);
    ++length;
    return;
  }

  tail->next = Node<T>::getNewNode(inputData);
  tail->next->prev = tail;
  tail = tail->next;
  ++length;
}

template <typename T>
T DoublyLinkedList<T>::pop_back() {
  if (length == 1) {
    Node<T> *current = tail;
    T removedValue = current->data;
    tail = NULL;
    head = NULL;
    free(current);
    --length;
    return removedValue;
  }

  try {
    if (tail == NULL) {
      throw "\n[pop_back() exception] can't pop back of an empty list!";
    }

    Node<T> *current = tail;
    T removedValue = current->data;
    tail = tail->prev;
    tail->next = NULL;
    free(current);
    --length;
    return removedValue;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T DoublyLinkedList<T>::front() {
  try {
    if (head == NULL) {
      throw "\n[front() exception] can't get front element of empty list!";
    }
    return head->data;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T DoublyLinkedList<T>::back() {
  try {
    if (tail == NULL) {
      throw "\n[back() exception] can't get back element of empty list!";
    }
    return tail->data;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void DoublyLinkedList<T>::insert_at(int index, T inputData) {
  if (index < 0) {
    std::cerr << "\n[insert_at()] index out of bounds!" << std::endl;
    exit(0);
  }
  if (index == 0) {
    push_front(inputData);
    return;
  }
  if (index >= length) {
    push_back(inputData);
    return;
  }

  Node<T> *current;
  int count, position;
  if (index > (length / 2)) {
    current = tail;
    position = length - index - 1;
    while(count < position) {
      current = current->prev;
      ++count;
    }

    Node<T> *temp = current->prev;
    current->prev = Node<T>::getNewNode(inputData);
    current->prev->next = current;
    current->prev->prev = temp;
    temp->next = current->prev;
    ++length;
  } else {
    current = head;
    position = index;
    while(count < position - 1) {
      current = current->next;
      ++count;
    }

    Node<T> *temp = current->next;
    current->next = Node<T>::getNewNode(inputData);
    current->next->prev = current;
    current->next->next = temp;
    temp->prev = current->next;
    ++length;
  }
}

template <typename T>
T DoublyLinkedList<T>::remove_at(int index) {
  if (index < 0 || index >= length) {
    std::cerr << "\n[remove_at() error] Index out of bounds!";
    exit(0);
  }
  if (index == 0) {
    return pop_front();
  }
  if (index == (length - 1)) {
    return pop_back();
  }

  Node<T> *current;
  int count = 0, position;
  if (index > (length / 2)) {
    current = tail;
    position = length - index - 1;
    while (count < position) {
      current = current->prev;
      ++count;
    }

    Node<T> *removedNode = current->prev;
    T removedValue = removedNode->data;
    current->prev = removedNode->prev;
    removedNode->prev->next = removedNode->next;
    free(removedNode);
    --length;
    return removedValue;
  } else {
    current = head;
    position = index - 1;
    while (count < position) {
      current = current->next;
      ++count;
    }

    Node<T> *removedNode = current->next;
    T removedValue = removedNode->data;
    current->next = removedNode->next;
    removedNode->next->prev = removedNode->prev;
    free(removedNode);
    --length;
    return removedValue;
  }
}

template <typename T>
T DoublyLinkedList<T>::value_n_from_end(int n) {
  if (n < 0 || n >= length) {
    std::cerr << "\n[value_n_from_end() error] index out of bounds!";
    exit(0);
  }
  if (n == 0) {
    return back();
  }
  if (n == (length - 1)) {
    return front();
  }

  Node<T> *current = tail;
  int count = 0;
  while (count < n - 1) {
    current = current->prev;
    ++count;
  }
  return current->data;
}

template <typename T>
T DoublyLinkedList<T>::remove_value(T value) {
  if (head == NULL) {
    std::cerr << "\n[remove_value() error] Can't remove from empty list!" << '\n';
    exit(0);
  }
  Node<T> *current = head;
  int count = 0;
  while(current != NULL) {
    if (current->data == value) {
      return remove_at(count);
    }
    current = current->next;
    ++count;
  }
  std::cerr << "\n[remove_value() error] Couldn't find value in list!" << '\n';
  exit(0);
}

template <typename T>
void DoublyLinkedList<T>::reverse() {
  if (head == NULL) {
    std::cerr << "\n[reverse() error] Can't remove empty list!" << '\n';
    exit(0);
  }

  tail = head;
  Node<T> *prev = NULL, *current = head, *next;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    current->prev = next;
    prev = current;
    current = next;
  }

  head = prev;
}

template <typename T>
void DoublyLinkedList<T>::printList() {
  if (head == NULL) {
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
