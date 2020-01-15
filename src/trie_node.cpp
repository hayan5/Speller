#include <trie_node.hpp>

TrieNode::TrieNode() {
  is_leaf_node = false;
  path = "";
}

TrieNode::~TrieNode() {
  for (auto it = children.begin(); it != children.end(); it++) {
    delete it->second;
  }
}



void TrieNode::make_leaf() {
  is_leaf_node = true;
}

void TrieNode::make_parent() {
  is_leaf_node = false;
}

bool TrieNode::is_leaf() {
  if (is_leaf_node == true)
    return true;
  
  return false;
}

std::string TrieNode::get_path() {
  return path;
}

void TrieNode::set_path(std::string path) {
  this->path = path;
}