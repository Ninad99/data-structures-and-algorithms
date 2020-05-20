/** A hash table implementation with open addressing
  * collision handling using quadratic probing
  *
  * @author Ninad Subba <ninuch7@gmail.com>
  */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>

#define DEFAULT_CAPACITY 8
#define DEFAULT_LOAD_FACTOR 0.65

template <typename K, typename V>
class Entry {
private:
  K key;
  V value;
  bool tombstone;

public:
  K getKey() { return key; }
  V getValue() { return value; }
  V setValue(V new_value) {
    this->value = new_value;
    return new_value;
  }
  bool isTombstone() { return tombstone; }

  static Entry<K, V>* createNewEntry(K key, V value) {
    Entry<K, V> *new_entry = new Entry<K, V>();
    new_entry->key = key;
    new_entry->value = value;
    new_entry->tombstone = false;
    return new_entry;
  }

  static Entry<K, V>* createTombstone(K old_key, V old_value) {
    Entry<K, V>* new_tombstone = new Entry<K, V>();
    new_tombstone->key = old_key;
    new_tombstone->value = old_value;
    new_tombstone->tombstone = true;
    return new_tombstone;
  }
};

// comparison functions
template <typename T>
int compare(T x, T y) {
  if (x < y)
    return -1;
  else if (x > y)
    return 1;
  else
    return 0;
}

int compare(const char* x, const char* y) {
  return std::strcmp(x, y);
}

template <typename K, typename V>
class HashTableQuadraticProbing {
private:
  // load factor = (items in table)/(size of table)
  // needs to be kept under a fixed value
  float loadFactor;
  // the value of capacity should be relatively prime
  // with the linear constant of the probing function
  // threshold = capacity * load factor
  int capacity, threshold;
  // array of entry pointers to store the data
  Entry<K, V> **table;
  // keep the count of the used buckets in the hash table
  // includes removed entries as well
  int usedBuckets;
  // keep the count of valid keys in the hash table
  int keysCount;

  int gcd(int, int); // computes the gcd of the given numbers
  int probeFunc(int); // probing function
  void adjustCapacity(); // adjusts the capacity value for the hash table
  void resizeTable(); // resizes the hash table with double capacity
  V updateEntry(K, V); // updates the value with the speicifed key in the hash table
  int hashFunc(int);
  int hashFunc(char);
  int hashFunc(const char*);

public:
  HashTableQuadraticProbing();
  ~HashTableQuadraticProbing();
  int size(); // returns the number of elements in the hash table
  bool isEmpty(); // returns true if hash table is empty
  bool containsKey(K); // returns true if hash table contains the given key
  V insert(K, V); // inserts the given value in the hash table
  V get(K); // gets the value mapped to the specified key in the hash table
  V remove(K); // removes the value with the corresponding key from the hash table
  std::vector<K> getKeys(); // returns a vector of keys from the hash table
  std::vector<V> getValues(); // returns a vector of values from the hash table
  void printTable(); // prints the hash table
};

// hash functions
// returns the hash for a given key
template <typename K, typename V>
int HashTableQuadraticProbing<K, V>::hashFunc(int key) {
  return abs(key) % capacity;
}

template <typename K, typename V>
int HashTableQuadraticProbing<K, V>::hashFunc(char key) {
  int ascii = (int)key;
  return abs(ascii) % capacity;
}

template <typename K, typename V>
int HashTableQuadraticProbing<K, V>::hashFunc(const char* key) {
  int keyValue = atoi(key);
  return abs(keyValue) % capacity;
}

template <typename K, typename V>
HashTableQuadraticProbing<K, V>::HashTableQuadraticProbing() {
  loadFactor = DEFAULT_LOAD_FACTOR;
  capacity = DEFAULT_CAPACITY;
  threshold = (int)capacity * loadFactor;
  usedBuckets = keysCount = 0;
  table = new Entry<K, V>*[capacity];
  for (int i = 0; i < capacity; i++) {
    table[i] = NULL;
  }
}

template <typename K, typename V>
HashTableQuadraticProbing<K, V>::~HashTableQuadraticProbing() {
  for (int i = 0; i < capacity; i++) {
    delete table[i];
  }
  delete[] table;
}

template<typename K, typename V>
int HashTableQuadraticProbing<K, V>::gcd(int a, int b) {
  if (a == 0)
    return b;

  return gcd(b % a, a);
}

// Quadratic probing function of type P(x) = (x^2 + x)/2
template<typename K, typename V>
int HashTableQuadraticProbing<K, V>::probeFunc(int x) {
  return (pow(x, 2) + x)/2;
}

template <typename K, typename V>
void HashTableQuadraticProbing<K, V>::adjustCapacity() {
  // P(x): probing function = (x^2 + x) / 2; N = capacity
  // for P(x) to produce a full cycle MOD N
  // N should be a power of 2
  int new_capacity = 2;
  while (new_capacity <= capacity) {
    new_capacity = new_capacity << 1;
  }
  capacity = new_capacity;
}

template <typename K, typename V>
void HashTableQuadraticProbing<K, V>::resizeTable() {
  // keep the old capacity value
  int oldCapacity = capacity;

  adjustCapacity(); // table capacity should be kept as a power of 2
  // reset the counts
  usedBuckets = keysCount = 0;
  threshold = (int)capacity * loadFactor;

  // keep the reference of the old hash table
  Entry<K, V> **old_table = table;

  // create a new table with updated capacity
  table = new Entry<K, V>*[capacity];
  for (int i = 0; i < capacity; i++) {
    table[i] = NULL;
  }

  for (int i = 0; i < oldCapacity; i++) {
    if (old_table[i] && !old_table[i]->isTombstone()) {
      insert(old_table[i]->getKey(), old_table[i]->getValue());
    }
    delete old_table[i];
  }

  delete[] old_table;
}

template <typename K, typename V>
int HashTableQuadraticProbing<K, V>::size() {
  return keysCount;
}

template <typename K, typename V>
bool HashTableQuadraticProbing<K, V>::isEmpty() {
  return keysCount == 0;
}

template <typename K, typename V>
bool HashTableQuadraticProbing<K, V>::containsKey(K key) {
  if (isEmpty()) { return false; }

  int keyHash = hashFunc(key);
  int x = 1;
  int bucket = keyHash;

  // if key at bucket matches given key return
  if (table[bucket] != NULL)
    if (compare(table[bucket]->getKey(), key) == 0)
      return true;

  // else probe
  while(table[bucket] != NULL) {
    bucket = (keyHash + probeFunc(x++)) % capacity;

    if (table[bucket] != NULL) {
        // continue probing if tombstone
        if (table[bucket]->isTombstone())
          continue;

        if (compare(table[bucket]->getKey(), key) == 0)
          return true;
    }
  }

  // not found
  return false;
}

template <typename K, typename V>
V HashTableQuadraticProbing<K, V>::updateEntry(K key, V value) {
  int keyHash = hashFunc(key);
  int x = 1;
  int bucket = keyHash;

  if (compare(table[bucket]->getKey(), key) == 0)
    return table[bucket]->setValue(value);

  while(table[bucket] != NULL) {
    bucket = (keyHash + probeFunc(x++)) % capacity;

    if (table[bucket] != NULL) {
        // continue probing if tombstone
        if (table[bucket]->isTombstone())
          continue;

        if (compare(table[bucket]->getKey(), key) == 0)
          break;
    }
  }

  return table[bucket]->setValue(value);
}

template <typename K, typename V>
V HashTableQuadraticProbing<K, V>::insert(K key, V value) {
  if (containsKey(key)) {
    return updateEntry(key, value);
  } else {
    if (usedBuckets >= threshold)
      resizeTable();

    int keyHash = hashFunc(key);
    int x = 1;
    int bucket = keyHash;

    while(table[bucket] != NULL) {
      bucket = (keyHash + probeFunc(x++)) % capacity;

      if (table[bucket] != NULL) {
          // break probing if tombstone
          if (table[bucket]->isTombstone())
            break;
      }
    }

    // if existing tombstone, delete it
    if (table[bucket] != NULL && table[bucket]->isTombstone()) {
      delete table[bucket];
    }

    table[bucket] = Entry<K, V>::createNewEntry(key, value);
    usedBuckets++;
    keysCount++;
  }

  return value;
}

template <typename K, typename V>
V HashTableQuadraticProbing<K, V>::get(K key) {
  if(!containsKey(key)) {
    std::cerr << "\n[get()] Error! Key not found in hash table!";
    exit(0);
  }

  int keyHash = hashFunc(key);
  int x = 1;
  int bucket = keyHash;

  if (compare(table[bucket]->getKey(), key) == 0)
    return table[bucket]->getValue();

  while(table[bucket] != NULL) {
    bucket = (keyHash + probeFunc(x++)) % capacity;

    if (table[bucket] != NULL) {
        // continue probing if tombstone
        if (table[bucket]->isTombstone())
          continue;

        if (compare(table[bucket]->getKey(), key) == 0)
          break;
    }
  }

  return table[bucket]->getValue();
}

template <typename K, typename V>
V HashTableQuadraticProbing<K, V>::remove(K key) {
  if(!containsKey(key)) {
    std::cerr << "\n[get()] Error! Key not found in hash table!";
    exit(0);
  }

  int keyHash = hashFunc(key);
  int x = 1;
  int bucket = keyHash;

  if (compare(table[bucket]->getKey(), key) == 0) {
    K removedKey = table[bucket]->getKey();
    V removedValue = table[bucket]->getValue();
    delete table[bucket];

    table[bucket] = Entry<K, V>::createTombstone(removedKey, removedValue);
    keysCount--;
    return removedValue;
  }

  while(table[bucket] != NULL) {
    bucket = (keyHash + probeFunc(x++)) % capacity;

    if (table[bucket] != NULL) {
        // continue probing if tombstone
        if (table[bucket]->isTombstone())
          continue;

        if (compare(table[bucket]->getKey(), key) == 0)
          break;
    }
  }

  K removedKey = table[bucket]->getKey();
  V removedValue = table[bucket]->getValue();
  delete table[bucket];

  table[bucket] = Entry<K, V>::createTombstone(removedKey, removedValue);
  keysCount--;
  return removedValue;
}

template <typename K, typename V>
std::vector<K> HashTableQuadraticProbing<K, V>::getKeys() {
  std::vector<K> keys;

  for (int bucket = 0; bucket < capacity; bucket++) {
    if (table[bucket] != NULL && !table[bucket]->isTombstone()) {
      keys.push_back(table[bucket]->getKey());
    }
  }

  return keys;
}

template <typename K, typename V>
std::vector<V> HashTableQuadraticProbing<K, V>::getValues() {
  std::vector<V> values;

  for (int bucket = 0; bucket < capacity; bucket++) {
    if (table[bucket] != NULL && !table[bucket]->isTombstone()) {
      values.push_back(table[bucket]->getValue());
    }
  }

  return values;
}

template <typename K, typename V>
void HashTableQuadraticProbing<K, V>::printTable() {
  std::cout << "\n";
  for (int bucket = 0; bucket < capacity; bucket++) {
    if (table[bucket] != NULL && !table[bucket]->isTombstone())
      std::cout << "\n" << bucket << " -> (" << table[bucket]->getKey() << ", " << table[bucket]->getValue() << ")";
    else
      std::cout << "\n" << bucket << " -> ( )";
  }
  std::cout << "\n";
}
