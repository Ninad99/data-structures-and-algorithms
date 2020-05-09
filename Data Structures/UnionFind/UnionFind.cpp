/** An implementation of the UnionFind/Disjoint Set data structure
  *
  * @author Ninad Subba
  */

#include <iostream>
#include <cstdlib>

class UnionFind {
private:
  int size, numComponents, *cSize, *id;

public:
  UnionFind(int);
  ~UnionFind();
  int find(int);  // Find which component/set (arg) belongs to
  int componentSize(int); // Return the size of the components/set (arg) belongs to
  bool connected(int, int); // Return whether or not the two elements are in the same components/set.
  int components(); // Returns the number of remaining components/sets
  int getSize(); // Return the number of elements in this UnionFind/Disjoint set
  void unify(int, int); // Unify the components/sets containing elements the two given elements
  void print();
};

UnionFind::UnionFind(int sz) {
  if (sz <= 0) {
    std::cerr << "\nSize <= 0 not allowed!\n";
    exit(0);
  }

  size = numComponents = sz;
  cSize = (int*)malloc(sz * sizeof(int));
  id = (int*)malloc(sz * sizeof(int));

  for (int i = 0; i < sz; i++) {
    id[i] = i;  // Link to itself
    cSize[i] = 1;  // Each component is originally of size one
  }
}

UnionFind::~UnionFind() {
  free(cSize);
  free(id);
}

int UnionFind::find(int p) {
  int root = p;
  while (root != id[root])
    root = id[root];

  // path compression
  while (p != root) {
    int next = id[p];
    id[p] = root;
    p = next;
  }

  return root;
}

// This is an alternative recursive formulation for the find method
// int find(int p) {
//   if (p == id[p]) return p;
//   return id[p] = find(id[p]);
// }

bool UnionFind::connected(int p, int q) {
  return find(p) == find(q);
}

int UnionFind::componentSize(int p) {
  return cSize[find(p)];
}

int UnionFind::getSize() {
  return size;
}

int UnionFind::components() {
  return numComponents;
}

void UnionFind::unify(int p, int q) {

  if (connected(p, q)) return;

  int root1 = find(p);
  int root2 = find(q);

  // Merge smaller component/set into the larger one.
  if (cSize[root1] < cSize[root2]) {
    cSize[root2] += cSize[root1];
    id[root1] = root2;
  } else {
    cSize[root1] += cSize[root2];
    id[root2] = root1;
  }

  numComponents--;
}

void UnionFind::print() {
  std::cout << "[";
  for (int i = 0; i < size; i++) {
    std::cout << id[i] << " ";
  }
  std::cout << "]";
}
