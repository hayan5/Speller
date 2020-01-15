#ifndef TRIE_HPP
#define TRIE_HPP

#include <trie_node.hpp>

#include <iostream>
#include <string>


class Trie
{
  public:
    Trie();
    ~Trie();

    void setRoot(TrieNode* root);
    TrieNode* getRoot(void);
    
    long int getNumberOfNodes(TrieNode* root);
    bool has_children(TrieNode* node);
    
    void insert(TrieNode* root, std::string const& key);
    bool remove(TrieNode* root, std::string const& key);
    bool contains(TrieNode* root, std::string const& key);
  
  private:
    TrieNode* root;

};

#endif
