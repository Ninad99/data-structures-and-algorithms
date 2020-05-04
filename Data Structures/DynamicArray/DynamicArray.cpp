/**
 * A generic dynamic array implementation
 * works with primitive types
 *
 * @author Ninad Subba <ninuch7@gmail.com>
*/

template <typename T>
class DynamicArray {
private:
  T *arr;
  int size;
  int capacity;

public:
  DynamicArray();
  DynamicArray(int);
  int length();
  bool isEmpty();
  T get(int);
  void push(T);
  int indexOf(T);
  T removeAt(int);
  bool remove(T);
  bool contains(T);
  void print();
};

template<typename T>
DynamicArray<T>::DynamicArray() {
  this->size = 0;
  this->arr = new T[16];
  this->capacity = 16;
}

template<typename T>
DynamicArray<T>::DynamicArray(int capacity) {
  try {
    if (capacity < 0) {
      throw this;
    }
    this->size = 0;
    this->arr = new T[capacity];
    this->capacity = capacity;
  }
  catch (DynamicArray *obj) {
    std::cerr << "\nError! Illegal capacity specified!" << std::endl;
    exit(0);
  }
}

template<typename T>
int DynamicArray<T>::length() {
  return this->size;
}

template<typename T>
bool DynamicArray<T>::isEmpty() {
  return this->size == 0;
}

template<typename T>
T DynamicArray<T>::get(int index) {
  try {
    if (index >= this->size || index < 0) {
      throw index;
    }
    return this->arr[index];
  }
  catch (int e) {
    std::cerr << "\n[get() exception] Array index out of bounds! Can't get item at index " << e << std::endl;
    exit(0);
  }
}

template<typename T>
void DynamicArray<T>::push(T item) {
  if (this->size + 1 >= this->capacity) {
    if (this->capacity == 0)
      this->capacity = 1;
    else
      this->capacity *= 2;

    T *new_arr = new T[this->capacity];
    for (int i = 0; i < this->size; i++)
      new_arr[i] = arr[i];

    this->arr = new_arr;
  }
  arr[this->size++] = item;
}

template<typename T>
int DynamicArray<T>::indexOf(T obj) {
  for (int i = 0; i < this->size; i++) {
    if (this->arr[i] == obj) {
      return i;
    }
  }
  return -1;
}

template<typename T>
T DynamicArray<T>::removeAt(int index) {
  try {
    if (index >= this->size || index < 0)
      throw index;
  }
  catch (int errIndex) {
    std::cerr << "\n[removeAt() exception] Array index out of bounds! Can't get item at index " << errIndex << std::endl;
    exit(0);
  }

  T data = this->arr[index];
  T *new_arr = new T[this->size - 1];

  for (int i = 0, j = 0; i < this->size; i++, j++) {
    if (i == index)
      j--;
    else
      new_arr[j] = arr[i];
  }

  arr = new_arr;
  capacity = --this->size;
  return data;
}

template<typename T>
bool DynamicArray<T>::remove(T obj) {
  int index = indexOf(obj);
  if (index == -1)
    return false;
  removeAt(index);
  return true;
}

template<typename T>
bool DynamicArray<T>::contains(T obj) {
  return indexOf(obj) != -1;
}

template<typename T>
void DynamicArray<T>::print() {
  if (this->size == 0) {
    std::cout << "[]" << std::endl;
    return;
  }

  std::cout << "\n[";
  for (int i = 0; i < this->size; i++) {
    if (i != this->size - 1) {
      std::cout << this->arr[i] << ", ";
    }
    else {
      std::cout << this->arr[i] << "]" << std::endl;
    }
  }
}
