/** An implementation of the Trie data structure
  *
  * @author Ninad Subba
  */

#include <iostream>
#include <stack>

using namespace std;

class TrieNode {
public:
  char data;
  int startsHere;
  int endsHere;
  TrieNode* children[26];

  // returns a new trie node
  static TrieNode* getNewNode(char ch) {
    TrieNode* node = new TrieNode();
    node->data = ch;
    node->startsHere = 0;
    node->endsHere = 0;
    for (int i = 0; i < 26; i++)
      node->children[i] = NULL;

    return node;
  }
};

class Trie {
private:
  TrieNode* root;

public:
  Trie(); // Default constructor
  Trie(string); // Parameterised constructor
  ~Trie(); // Destructor
  void insert(string); // inserts a string into trie
  bool search(string); // checks whether given string is present in trie or not
  void remove(string); // removes a string from the trie
  int startsWith(string); // returns the number of words starting with given prefix
};

Trie::Trie() {
  root = TrieNode::getNewNode('*');
}

Trie::Trie(string str) {
  root = TrieNode::getNewNode('*');
  insert(str);
}

Trie::~Trie() {
  delete root;
}

void Trie::insert(string str) {
  TrieNode* crawler = root;
  int strLength = str.size();
  for (int i = 0; i < strLength; i++) {
    char ch = str[i];

    if (!crawler->children[ch - 'a']) {
      crawler->children[ch - 'a'] = TrieNode::getNewNode(ch);
      crawler->children[ch - 'a']->startsHere = 1;
    } else {
      crawler->children[ch - 'a']->startsHere += 1;
    }

    crawler = crawler->children[ch - 'a'];
  }

  crawler->endsHere += 1;
}

bool Trie::search(string str) {
  TrieNode* crawler = root;
  int strLength = str.size();
  for (int i = 0; i < strLength; i++) {
    char ch = str[i];

    if (!crawler->children[ch - 'a']) {
      return false;
    }

    crawler = crawler->children[ch - 'a'];
  }

  return (crawler != NULL && crawler->endsHere > 0);
}

void Trie::remove(string str) {
  TrieNode* crawler = root;
  int strLength = str.size();
  stack<TrieNode*> s;
  for (int i = 0; i < strLength; i++) {
    char ch = str[i];

    if (!crawler->children[ch - 'a'])
      return;

    crawler = crawler->children[ch - 'a'];
    s.push(crawler);
  }

  if (crawler->endsHere > 0) {
    crawler->endsHere--;
    while (!s.empty()) {
      s.top()->startsHere--;
      s.pop();
    }
  }
}

int Trie::startsWith(string str) {
  TrieNode* crawler = root;
  int strLength = str.size();
  for (int i = 0; i < strLength; i++) {
    char ch = str[i];

    if (!crawler->children[ch - 'a'])
      return 0;

    crawler = crawler->children[ch - 'a'];
  }

  return crawler->startsHere;
}

int main() {
  Trie t("apple");
  cout << "Insert 'apple'\nInsert 'add'\nInsert 'beer'" << endl;
  t.insert("add");
  t.insert("beer");
  cout << "Search 'add': " << t.search("add") << endl;
  cout << "Search 'app': " << t.search("app") << endl;
  cout << "Starts with 'a': " << t.startsWith("a") << endl;
  cout << "Starts with 'ad': " << t.startsWith("ad") << endl;
  cout << "Starts with 'addd': " << t.startsWith("addd") << endl;
  t.remove("add");
  cout << "Removed 'add'" << endl;
  cout << "Starts with 'a': " << t.startsWith("a") << endl;
  cout << "Search 'add': " << t.search("add") << endl;
  cout << "Search 'beer': " << t.search("beer") << endl;
  return 0;
}
