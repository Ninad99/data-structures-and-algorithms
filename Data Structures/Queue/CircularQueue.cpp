/** A generic circular queue implementation using an array
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

template <typename T>
class CircularQueue {
private:
  int head, tail, length, capacity;
  T *arr;

public:
  CircularQueue(); // constructor
  CircularQueue(int); // parameterized constructor
  ~CircularQueue(); // destructor
  int size(); // return size of Queue
  bool isEmpty(); // returns true if queue is empty
  bool isFull(); // returns true if queue is full
  void enqueue(T); // adds element to back of queue
  T dequeue(); // removes element from the front of queue and returns it
  T front(); // returns the front element
  T back(); // returns the last element
  bool contains(T); // returns true if queue contains value
  int frontIndex(); // returns the index of front element
  int rearIndex(); // returns the index of rear element
  void print(); // prints the queue
};

template <typename T>
CircularQueue<T>::CircularQueue() {
  head = tail = -1;
  length = 0;
  capacity = 16;
  arr = (T*)malloc(capacity * sizeof(T));
}

template <typename T>
CircularQueue<T>::CircularQueue(int c) {
  head = tail = -1;
  length = 0;
  capacity = c;
  arr = (T*)malloc(c * sizeof(T));
}

template <typename T>
CircularQueue<T>::~CircularQueue() {
  free(arr);
}

template <typename T>
int CircularQueue<T>::size() {
  return length;
}

template <typename T>
bool CircularQueue<T>::isEmpty() {
  return length == 0;
}

template <typename T>
bool CircularQueue<T>::isFull() {
  return length == capacity;
}

template <typename T>
void CircularQueue<T>::enqueue(T data) {
  if (head == -1) {
    *(arr) = data;
    head = tail = 0;
    ++length;
    return;
  }

  if (length == capacity) {
    std::cerr << "\n[enqueue() error] Queue is full!" << std::endl;
    return;
  }

  if (tail == (capacity - 1) && head != 0) {
    tail = 0;
    *(arr) = data;
    ++length;
    return;
  }

  *(arr + (++tail)) = data;
  ++length;
}

template <typename T>
T CircularQueue<T>::dequeue() {
  if (length == 0) {
    std::cerr << "\n[dequeue() error] Queue is empty!" << std::endl;
    exit(0);
  }

  T removedValue = *(arr + head);

  if (head == tail) {
    head = tail = -1;
  } else if (head == (capacity - 1)) {
    head = 0;
  } else {
    ++head;
  }

  --length;
  return removedValue;
}

template <typename T>
T CircularQueue<T>::front() {
  if (length == 0) {
    std::cerr << "\n[front() error] Queue is empty!" << std::endl;
    exit(0);
  }

  return *(arr + head);
}

template <typename T>
T CircularQueue<T>::back() {
  if (length == 0) {
    std::cerr << "\n[back() error] Queue is empty!" << std::endl;
    exit(0);
  }

  return *(arr + tail);
}

template <typename T>
bool CircularQueue<T>::contains(T data) {
  if (length == 0) {
    std::cerr << "\n[contains() error] Queue is empty!" << std::endl;
    exit(0);
  }

  int i;
  if (tail >= head) {
    for (i = head; i <= tail; i++) {
      if (*(arr + i) == data) {
        return true;
      }
    }
    return false;
  } else {
    for (i = head; i < capacity; i++) {
      if (*(arr + i) == data) {
        return true;
      }
    }
    for (i = 0; i <= tail; i++) {
      if (*(arr + i) == data) {
        return true;
      }
    }
    return false;
  }
}

template <typename T>
int CircularQueue<T>::frontIndex() {
  return head;
}

template <typename T>
int CircularQueue<T>::rearIndex() {
  return tail;
}

template <typename T>
void CircularQueue<T>::print() {
  if (length == 0) {
    std::cout << "\n[]" << std::endl;
    return;
  }

  int i;
  std::cout << "\n[";
  if (tail >= head) {
    for (i = head; i <= tail; i++) {
      if (i == tail) {
        std::cout << *(arr + i) << "]" << std::endl;
      } else {
        std::cout << *(arr + i) << ", ";
      }
    }
  } else {
    for (i = head; i < capacity; i++) {
      std::cout << *(arr + i) << ", ";
    }
    for (i = 0; i <= tail; i++) {
      if (i == tail) {
        std::cout << *(arr + i) << "]" << std::endl;
      } else {
        std::cout << *(arr + i) << ", ";
      }
    }
  }
}
