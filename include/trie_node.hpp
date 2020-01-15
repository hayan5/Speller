#ifndef TRIE_NODE_HPP
#define TRIE_NODE_HPP

#include <unordered_map>
#include <string>

class TrieNode 
{
  


  public:
    std::unordered_map<char, TrieNode*> children;
    bool is_leaf_node;
    std::string path;
    TrieNode();
    ~TrieNode();

    void make_leaf();
    void make_parent();
    bool is_leaf();
    std::string get_path();
    void set_path(std::string path);

};

#endif