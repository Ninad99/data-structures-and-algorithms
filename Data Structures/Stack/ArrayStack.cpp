/** A generic stack implementation using an array
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

template <typename T>
class Stack {
private:
  int top, length, capacity;
  T *arr;
  void resize(); // resize array

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
  arr = (T*)malloc(16 * sizeof(T)); // initialize array size to 16
  capacity = 16;
  top = -1;
  length = 0;
}

template <typename T>
Stack<T>::~Stack() {
  free(arr);
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
void Stack<T>::resize() {
  T *new_arr = (T*)malloc(capacity * sizeof(T));
  for (int i = 0; i < length; i++) {
    *(new_arr + i) = *(arr + i);
  }
  T *old_arr = arr;
  arr = new_arr;
  free(old_arr);
}

template <typename T>
void Stack<T>::push(T data) {
  if ((length + 1) > capacity) {
    capacity *= 2;
    resize();
  }

  *(arr + (++top)) = data;
  ++length;
}

template <typename T>
T Stack<T>::pop() {
  if (top == -1) {
    std::cerr << "\n[pop() error] can't pop from empty stack!";
    exit(0);
  }

  T data = *(arr + top);
  --top;
  --length;
  return data;
}

template <typename T>
T Stack<T>::peek() {
  if (top == -1) {
    std::cerr << "\n[peek() error] can't peek empty stack!";
    exit(0);
  }

  return *(arr + top);
}

template <typename T>
bool Stack<T>::contains(T data) {
  for (int i = top; i >= 0; i--) {
    if (*(arr + i) == data) {
      return true;
    }
  }
  return false;
}

template <typename T>
void Stack<T>::print() {
  if (top == -1) {
    std::cout << "[]" << std::endl;
    return;
  }

  std::cout << "\n[";
  for (int i = top; i >= 0; i--) {
    if (i == 0) {
      std::cout << *(arr + i) << "]" << std::endl;
    } else {
      std::cout << *(arr + i) << ", ";
    }
  }
}
