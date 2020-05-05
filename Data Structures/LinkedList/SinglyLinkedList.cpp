/** A generic singly linked list implementation
 *  Works with primitive types
 *
 *  @author Ninad Subba <ninuch7@gmail.com>
 */

#include <iostream>
#include <cstdlib>

template <typename T>
class Node {
public:
  T data;
  Node<T> *next;

  static Node<T>* getNewNode(T inputData) {
    Node *newNode = (Node*)malloc(sizeof(Node<T>));
    newNode->data = inputData;
    newNode->next = NULL;
    return newNode;
  }
};

template <typename T>
class LinkedList {
private:
  int length;
  Node<T> *head;
  Node<T> *tail;

public:
  LinkedList(); // constructor
  ~LinkedList(); // destructor
  int size(); // returns number of data elements in list
  bool isEmpty(); // bool returns true if empty
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
LinkedList<T>::LinkedList() {
  std::cout << "\nIn constructor" << std::endl;
  length = 0;
  head = NULL;
  tail = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  std::cout << "\nIn destructor" << std::endl;
  Node<T> *next = NULL, *current = head;
  while (current) {
    next = current->next;
    free(current);
    current = next;
  }
}

template <typename T>
int LinkedList<T>::size() {
  return length;
}

template <typename T>
bool LinkedList<T>::isEmpty() {
  return length == 0;
}

template <typename T>
T LinkedList<T>::value_at(int index) {
  Node<T> *current = head;
  int count = 0;

  try {
    while(count != index) {
      if (current == NULL) {
        throw index;
      }
      current = current->next;
      count++;
    }
    return current->data;
  }
  catch (int errIndex) {
    std::cerr << "\n[value_at() exception] specified index " << errIndex << " out of bounds!" << std::endl;
    exit(0);
  }
}

template <typename T>
void LinkedList<T>::push_front(T data) {
  if (head == NULL) {
    head = Node<T>::getNewNode(data);
    tail = head;
    length++;
    return;
  }

  Node<T> *newNode = Node<T>::getNewNode(data);
  newNode->next = head;
  head = newNode;
  length++;
}

template <typename T>
T LinkedList<T>::pop_front() {
  try {
    if (head == NULL) {
      throw "\n[pop_front() exception] Can't remove from empty list!";
    }

    Node<T> *current = head;
    head = head->next;
    T removedValue = current->data;
    free(current);
    length--;
    return removedValue;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void LinkedList<T>::push_back(T data) {
  if (tail == NULL) {
    tail = Node<T>::getNewNode(data);
    head = tail;
    length++;
    return;
  }

  Node<T> *newNode = Node<T>::getNewNode(data);
  tail->next = newNode;
  tail = newNode;
  length++;
}

template <typename T>
T LinkedList<T>::pop_back() {
  try {
    if (tail == NULL) {
      throw "\n[pop_back() exception] Can't remove from empty list!";
    }

    Node<T> *current = head;
    while(current->next != tail) {
      current = current->next;
    }
    tail = current;
    current = current->next;
    T removedValue = current->data;
    free(current);
    tail->next = NULL;
    length--;
    return removedValue;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T LinkedList<T>::front() {
  try {
    if (head == NULL) {
      throw "\n[front() exception] can't access front of empty queue!";
    }
    return head->data;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T LinkedList<T>::back() {
  try {
    if (tail == NULL) {
      throw "\n[back() exception] can't access front of empty queue!";
    }
    return tail->data;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void LinkedList<T>::insert_at(int index, T data) {
  if (index == 0) {
    push_front(data);
    return;
  }

  Node<T> *current = head;
  int count = 0;
  while (count < (index - 1)) {
    if (current->next == NULL) {
      Node<T> *newNode = Node<T>::getNewNode(data);
      current->next = newNode;
      tail = newNode;
      length++;
      return;
    }
    current = current->next;
    count++;
  }

  Node<T> *next = current->next;
  Node<T> *newNode = Node<T>::getNewNode(data);
  current->next = newNode;
  newNode->next = next;
  length++;
}

template <typename T>
T LinkedList<T>::remove_at(int index) {
  if (index == 0) {
    return pop_front();
  }

  if (index == (length - 1)) {
    return pop_back();
  }

  Node<T> *current = head;
  int count = 0;
  try {
    while (count < (index - 1)) {
      current = current->next;
      if (current->next == NULL) {
        throw "\n[remove_at(index) exception] index out of bounds!";
      }
      count++;
    }

    Node<T> *next = current->next->next;
    Node<T> *removedNode = current->next;
    current->next = next;
    T removedValue = removedNode->data;
    free(removedNode);
    length--;
    return removedValue;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T LinkedList<T>::value_n_from_end(int n) {
  try {
    int position = length - n - 1;
    if (position < 0) {
      throw "\n[value_n_from_end(n) exception] index out of bounds!";
    }
    Node<T> *current = head;
    for (int i = 0; i < position; i++) {
      current = current->next;
    }
    return current->data;
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
T LinkedList<T>::remove_value(T value) {
  try {
    Node<T> *current = head;
    int index = 0;
    while(current->next != NULL) {
      if (current->data == value) {
        return remove_at(index);
      }
      index++;
      current = current->next;
    }

    throw "\n[remove_value()] Value not found!";
  }
  catch (const char* errMsg) {
    std::cerr << errMsg << std::endl;
    exit(0);
  }
}

template <typename T>
void LinkedList<T>::reverse() {
  if (head == NULL) { return; }

  tail = head;
  Node<T> *prev = NULL;
  Node<T> *current = head;
  Node<T> *next;

  while(current != NULL) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
  }

  head = prev;
}

template <typename T>
void LinkedList<T>::printList() {
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
