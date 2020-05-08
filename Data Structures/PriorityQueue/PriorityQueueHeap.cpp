/** A generic priority queue implementation using a binary min heap
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>
#include <cstring>

// comparator for int, float, double
template <typename T>
bool lesser(T x, T y) {
  return x < y;
}

//comparator for char, char*
bool lesser(const char* x, const char* y) {
  return std::strcmp(x, y) < 0;
}

template <typename T>
class PriorityQueue {
private:
  T *heap;
  int length, capacity;
  void heapifyUp(int); // Bubble up
  void heapifyDown(int); // Bubble down
  void swap(int, int);
  void resize();

public:
  PriorityQueue(); // constructor
  ~PriorityQueue(); // destructor
  bool isEmpty(); // returns true if heap is empty
  int size(); // returns size of heap
  void clear(); // clears the heap
  T peek(); // returns the front element
  T poll(); // removes the top element and returns it's value
  bool contains(T); // returns true if heap contains the element
  void add(T);  // add element to the heap
  T remove(T);  // remove element from the heap
  T removeAt(int);  // remove element at the specified index
  void print(); // prints the elements of the queue
};

template <typename T>
PriorityQueue<T>::PriorityQueue() {
  length = 0;
  capacity = 7;
  heap = (T*)malloc(capacity * sizeof(T));
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {
  free(heap);
}

template <typename T>
bool PriorityQueue<T>::isEmpty() {
  return length == 0;
}

template <typename T>
int PriorityQueue<T>::size() {
  return length;
}

template <typename T>
void PriorityQueue<T>::clear() {
  length = 0;
  capacity = 7;
  free(heap);
  heap = (T*)malloc(capacity * sizeof(T));
}

template <typename T>
void PriorityQueue<T>::swap(int index1, int index2) {
  T temp = *(heap + index1);
  *(heap + index1) = *(heap + index2);
  *(heap + index2) = temp;
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
  int parent = (index - 1)/2;

  while(index > 0 && lesser(*(heap + index), *(heap + parent))) {
    swap(index, parent);
    index = parent;

    parent = (index - 1)/2;
  }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
  int heapsize = length - 1;
  while(true) {
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    int smallest = left;

    if (right < heapsize && lesser(*(heap + right), *(heap + left)))
      smallest = right;

    if (left > heapsize || lesser(*(heap + index), *(heap + smallest)))
      break;

    swap(smallest, index);
    index = smallest;
  }
}

template <typename T>
void PriorityQueue<T>::resize() {
  capacity *= 2;
  T *new_heap = (T*)malloc(capacity * sizeof(T));
  for (int i = 0; i < length; i++) {
    *(new_heap + i) = *(heap + i);
  }
  T *old = heap;
  free(old);
  heap = new_heap;
}

template <typename T>
T PriorityQueue<T>::peek() {
  if (length == 0) {
    std::cerr << "\n[peek() error] can't peek in empty queue!";
    exit(0);
  }

  return *(heap);
}

template <typename T>
T PriorityQueue<T>::poll() {
  return removeAt(0);
}

template <typename T>
bool PriorityQueue<T>::contains(T data) {
  if (length == 0) {
    std::cerr << "\n[contains() error] empty queue!";
    exit(0);
  }

  for (int i = 0; i < length; i++) {
    if (*(heap + i) == data) {
      return true;
    }
  }
  return false;
}

template <typename T>
void PriorityQueue<T>::add(T data) {
  if (length == capacity) {
    resize();
  }

  *(heap + length++) = data;
  heapifyUp(length - 1);
}

template <typename T>
T PriorityQueue<T>::remove(T data) {
  if (!contains(data)) {
    std::cerr << "\n[remove() error] queue doesn't contain element!";
    exit(0);
  }

  for (int i = 0; i < length; i++) {
    if (*(heap + i) == data) {
      return removeAt(i);
    }
  }
}

template <typename T>
T PriorityQueue<T>::removeAt(int index) {
  if (isEmpty()) {
    std::cout << "\n[removeAt() error] can't remove from empty queue!";
    exit(0);
  }

  if (index < 0 || index >= length) {
    std::cout << "\n[removeAt() error] index out of bounds!";
    exit(0);
  }

  T removedData = *(heap + index);
  int lastElemIndex = length - 1;
  swap(index, lastElemIndex);
  --length;

  if (index == lastElemIndex)
    return removedData;

  T elem = *(heap + index);
  heapifyDown(index);

  if (*(heap + index) == elem)
    heapifyUp(index);

  return removedData;
}

template <typename T>
void PriorityQueue<T>::print() {
  if (isEmpty()) {
    std::cout << "\n[]" << std::endl;
    return;
  }

  std::cout << "\n[";
  for (int i = 0; i < length; i++) {
    if ((i + 1) == length) {
      std::cout << *(heap + i) << "]" << std::endl;
    } else {
      std::cout << *(heap + i) << ", ";
    }
  }
}
