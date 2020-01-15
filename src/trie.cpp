#include <trie.hpp>



Trie::Trie() {
  root = new TrieNode();
}

Trie::~Trie() {
  delete root;
}

void Trie::setRoot(TrieNode* root) {
  this->root = root;
}

TrieNode* Trie::getRoot(void) {
  return this->root;
}


// long int Trie::getNumberOfNodes(struct Node* root) {
//   return 0;
// }

// Returns True if node has children
bool Trie::has_children(TrieNode* node) {
  for (auto it: node->children) {
    if (it.second != nullptr)
      return true;
  }
  return false;
}

void Trie::insert(TrieNode* root, std::string const& key) {

  TrieNode* temp = root;

  for (int i = 0; i < key.size(); i++) {

    if (temp->children[key[i]] == nullptr) {
      TrieNode* newNode = new TrieNode();
      newNode->set_path(temp->path + key[i]);
      temp->children[key[i]] = newNode;
    }
    
    temp = temp->children[key[i]];
    
    if (i == key.size() - 1)
      temp->make_leaf();
  }
}

bool Trie::remove(TrieNode* root, std::string const& key) {
  
  
  
 
 

  return true;
}



// Returns false if key does not exist in trie
bool Trie::contains(TrieNode* root, std::string const& key) {

  TrieNode* temp = root;

  for (int i = 0; i < key.size(); i++) {
    if (temp->children[key[i]] == nullptr)
      return false;
    temp = temp->children[key[i]];
  }

  return temp->is_leaf();
}