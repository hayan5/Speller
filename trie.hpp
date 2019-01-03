#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

struct Node
{
  bool LeafNode;
  std::unordered_map<char, Node*> map;
};

//Constuctor function for node struct
struct Node *getNewNode()
{
  Node *newNode = new Node;
  newNode->LeafNode = false;
  return newNode;
}

class Trie
{
public:
  Trie();
  ~Trie();
  void insert(std::string word);
  bool search(std::string word);
  void createDictionary(std::string dictionaryFile);
  std::vector<std::string> prefixSearch(std::string prefix);
  int levenshteinDistance(std::string X, int m, std::string Y, int n);
  std::vector<std::string> getWords();
private:
  Node *root;
  void traversePrefix(std::string prefix, Node *node, std::vector<std::string> &v);
  void traverse (std::string word, Node *node, std::vector<std::string> &v);
};
#endif
