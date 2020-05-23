/** A Fenwick tree (Binary Indexed Tree) implementation
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>

class FenwickTree {
private:
  int n; // size of fenwick tree
  long *tree;
  int lsbValue(int); // returns the value of the least significant bit
  long prefixSum(int); // computes prefix sum from [1,i] O(log(n))

public:
  FenwickTree(int);
  FenwickTree(const int*, int);
  FenwickTree(const long*, int);
  ~FenwickTree();
  long getSum(int,int); // returns the interval sum from [i,j] O(log(n))
  long getValueAt(int); // returns the value at index
  void pointUpdate(int,long); // add value 'v' at index 'i'
  void set(int,long); // set index 'i' to value 'v'
  void print();
};

FenwickTree::FenwickTree(int size) {
  n = size + 1;
  tree = new long[n];
}

FenwickTree::FenwickTree(const int *arr, int size) {
  n = size + 1;
  tree = new long[n];

  tree[0] = 0; // first element is not used

  // clone the array since we're doing
  // in-place operations
  for (int i = 1; i < n; i++) {
    tree[i] = (long)arr[i - 1];
  }

  for (int i = 1; i < n; i++) {
    int parent = i + lsbValue(i);
    if (parent < n)
      tree[parent] += tree[i];
  }
}

FenwickTree::FenwickTree(const long *arr, int size) {
  n = size + 1;
  tree = new long[n];

  tree[0] = 0; // first element is not used

  // clone the array since we're doing
  // in-place operations
  for (int i = 1; i < n; i++) {
    tree[i] = arr[i - 1];
  }

  for (int i = 1; i < n; i++) {
    int parent = i + lsbValue(i);
    if (parent < n)
      tree[parent] += tree[i];
  }
}

FenwickTree::~FenwickTree() {
  delete[] tree;
}

// returns the value of the least significant bit (LSB)
// lsb(13) = (13)2 & (-13)2 = 0b1101 & 1b0011 = 1
// lsb(12) = (12)2 & (-12)2 = 0b1100 & 1b0100 = 4
// lsb(8) = (8)2 & (-8)2
// 0b1000
// 1b1000 &
// 001000 = 8
int FenwickTree::lsbValue(int i) {
  return i & -i;
}

// returns sum of range [1,i]
long FenwickTree::prefixSum(int i) {
  long sum = 0;

  while(i != 0) {
    sum += tree[i];
    i &= ~lsbValue(i);
  }

  return sum;
}

long FenwickTree::getSum(int i, int j) {
  if (j < i) {
    std::cerr << "[getSum()] error! second argument should be greater than first";
    exit(0);
  }

  return prefixSum(j) - prefixSum(i-1);
}

long FenwickTree::getValueAt(int i) {
  return getSum(i, i);
}

void FenwickTree::pointUpdate(int i, long value) {
  while(i < n) {
    tree[i] += value;
    i += lsbValue(i);
  }
}

void FenwickTree::set(int i, long value) {
  pointUpdate(i, value - getValueAt(i));
}

void FenwickTree::print() {
  for (int i = 1; i < n; i++) {
    std::cout << tree[i] << " ";
  }
  std::cout << "]\n";
}
