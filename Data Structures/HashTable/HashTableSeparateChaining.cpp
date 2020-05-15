/** A hash table implementation using separate chaining with a linked list
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <list>
#include <iterator>

#define DEFAULT_CAPACITY 10

using namespace std;

template <typename K, typename V>
class Node {
private:
  K key;
  V value;
  int hash;

public:
  K getKey() { return key; }
  V getValue() { return value; }
  void setHash(int hash) { this->hash = hash; }

  static Node<K, V>* getNewNode(K key, V value) {
    Node<K, V>* new_node = new Node();
    new_node->key = key;
    new_node->value = value;
    new_node->hash = -1;
    return new_node;
  }

  static bool equals(Node<K, V>* x, Node<K, V>* y) {
    if (x.hash != y.hash)
      return false;

    return x.key == y.key;
  }
};

int createHash(int key) {
  return abs(key) % DEFAULT_CAPACITY;
}

int createHash(char key) {
  int ascii = (int)key;
  return abs(ascii) % DEFAULT_CAPACITY;
}

int createHash(const char* key) {
  int keyValue = atoi(key);
  return abs(keyValue) % DEFAULT_CAPACITY;
}

template <typename K, typename V>
class HashTableSeparateChain {
private:
  int sz, capacity;
  list<Node<K, V>*> *table;

public:
  HashTableSeparateChain();
  ~HashTableSeparateChain();
  int size();
  bool isEmpty();
  bool containsKey(K);
  void insert(K, V);
  void remove(K);
  V get(K);
  void print();
  list<K> getKeys();
  list<V> getValues();
};

template <typename K, typename V>
HashTableSeparateChain<K, V>::HashTableSeparateChain() {
  cout << "\nIn constructor\n";
  sz = 0;
  capacity = DEFAULT_CAPACITY;
  table = new list<Node<K, V>*>[DEFAULT_CAPACITY];
}

template <typename K, typename V>
HashTableSeparateChain<K, V>::~HashTableSeparateChain() {
  cout << "\nIn destructor\n";
  for (int i = 0; i < capacity; i++) {
    while (!table[i].empty()) {
      delete table[i].front();
      table[i].pop_front();
    }
  }
  delete[] table;
}

template <typename K, typename V>
int HashTableSeparateChain<K, V>::size() {
  return sz;
}

template <typename K, typename V>
bool HashTableSeparateChain<K, V>::isEmpty() {
  return sz == 0;
}

template <typename K, typename V>
bool HashTableSeparateChain<K, V>::containsKey(K key) {
  int hash = createHash(key);

  if (!table[hash].empty()) {
    typename list<Node<K, V>*>::iterator itr;

    for (itr = table[hash].begin(); itr != table[hash].end(); ++itr) {
      if ((*itr)->getKey() == key)
        return true;
    }
    return false;
  }

  return false;
}

template <typename K, typename V>
void HashTableSeparateChain<K, V>::insert(K key, V value) {
  // hash the key
  int bucket = createHash(key);

  if (!containsKey(key)) {
    // create new node and assign hash value
    Node<K, V>* new_node = Node<K, V>::getNewNode(key, value);
    new_node->setHash(bucket);

    // insert node into appropriate bucket
    table[bucket].push_back(new_node);
  }
}

template <typename K, typename V>
void HashTableSeparateChain<K, V>::remove(K key) {
  // find the bucket
  int bucket = createHash(key);

  typename list<Node<K, V>*>::iterator itr;
  // iterate over the list and check if key matches
  for (itr = table[bucket].begin(); itr != table[bucket].end(); ++itr) {
    if ((*itr)->getKey() == key) {
      break;
    }
  }

  // remove if found
  if (itr != table[bucket].end())
    table[bucket].erase(itr);
}

template <typename K, typename V>
V HashTableSeparateChain<K, V>::get(K key) {
  int bucket = createHash(key);

  if (table[bucket].empty()) {
      std::cerr << "\n[get() error] table doesn't contain given key!\n";
      exit(0);
  }

  typename list<Node<K, V>*>::iterator itr;

  for (itr = table[bucket].begin(); itr != table[bucket].end(); ++itr) {
    if ((*itr)->getKey() == key) {
      return (*itr)->getValue();
    }
  }
}

template <typename K, typename V>
list<K> HashTableSeparateChain<K, V>::getKeys() {
  list<K> keysList;
  for (int i = 0; i < capacity; i++) {
    typename list<Node<K, V>*>::iterator itr;
    for (itr = table[i].begin(); itr != table[i].end(); ++itr) {
      keysList.push_back((*itr)->getKey());
    }
  }

  return keysList;
}

template <typename K, typename V>
list<V> HashTableSeparateChain<K, V>::getValues() {
  list<V> valuesList;
  for (int i = 0; i < capacity; i++) {
    typename list<Node<K, V>*>::iterator itr;
    for (itr = table[i].begin(); itr != table[i].end(); ++itr) {
      valuesList.push_back((*itr)->getValue());
    }
  }

  return valuesList;
}

template <typename K, typename V>
void HashTableSeparateChain<K, V>::print() {
  for (int i = 0; i < capacity; i++) {
    cout << i << " -> ";
    typename list<Node<K, V>*>::iterator itr;
    cout << "{";
    for (itr = table[i].begin(); itr != table[i].end(); ++itr) {
      cout << (*itr)->getValue() << " ";
    }
    cout << "}\n";
  }
}
