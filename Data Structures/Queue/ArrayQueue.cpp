/** A generic queue implementation using an array
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

template <typename T>
class Queue {
private:
  int head, tail, length, capacity;
  T *arr;
  void resize(); // resize the queue

public:
  Queue(); // constructor
  ~Queue(); // destructor
  int size(); // return size of Queue
  bool isEmpty(); // returns true if queue is empty
  bool isFull(); // returns true if queue is full
  void enqueue(T); // adds element to back of queue
  T dequeue(); // removes element from the front of queue and returns it
  T front(); // returns the front element
  T back(); // returns the last element
  bool contains(T); // returns true if queue contains value
  void print(); // prints the queue
};

template <typename T>
Queue<T>::Queue() {
  head = tail = -1;
  length = 0;
  capacity = 16;
  arr = (T*)malloc(16 * sizeof(T)); // initialize array size to 16
}

template <typename T>
Queue<T>::~Queue() {
  free(arr);
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
bool Queue<T>::isFull() {
  return length == capacity;
}

template <typename T>
void Queue<T>::resize() {
  T *new_arr = (T*)malloc(capacity * sizeof(T));
  for (int i = 0; i < length; i++) {
    *(new_arr + i) = *(arr + i);
  }
  T *old_arr = arr;
  arr = new_arr;
  free(old_arr);
}

template <typename T>
void Queue<T>::enqueue(T data) {
  if (head == -1 && tail == -1) {
    *(arr) = data;
    head = tail = 0;
    ++length;
    return;
  }

  if (length > capacity) {
    capacity *= 2;
    resize();
  }

  *(arr + (++tail)) = data;
  ++length;
}

template <typename T>
T Queue<T>::dequeue() {
  if (head == -1 && tail == -1) {
    std::cerr << "\n[dequeue() error] can't dequeue from empty queue!";
    exit(0);
  }

  T removedValue = *(arr);
  for (int i = 0; i < (length - 1); i++) {
    *(arr + i) = *(arr + i + 1);
  }
  --tail;
  --length;
  if (length == 0)
    head = -1;
  return removedValue;
}

template <typename T>
T Queue<T>::front() {
  if (head == -1 && tail == -1) {
    std::cerr << "\n[front() error] can't get front of empty queue!";
    exit(0);
  }

  return *(arr);
}

template <typename T>
T Queue<T>::back() {
  if (head == -1 && tail == -1) {
    std::cerr << "\n[back() error] can't get back of empty queue!";
    exit(0);
  }

  return *(arr + tail);
}

template <typename T>
bool Queue<T>::contains(T data) {
  for (int i = 0; i < length; i++) {
    if (*(arr + i) == data) {
      return true;
    }
  }
  return false;
}

template <typename T>
void Queue<T>::print() {
  if (length == 0) {
    std::cout << "[]" << std::endl;
    return;
  }

  std::cout << "\n[";
  for (int i = 0; i < length; i++) {
    if (i == (length - 1)) {
      std::cout << *(arr + i) << "]" << std::endl;
    } else {
      std::cout << *(arr + i) << ", ";
    }
  }
}
