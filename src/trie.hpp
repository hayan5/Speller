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

  //Inserts string into trie
  void insert(std::string word);
  //Returns true if string already exists in trie
  bool search(std::string word);
  void createDictionary(std::string dictionaryFile);

  //Returns vector of all endings to entered prefix
  std::vector<std::string> prefixSearch(std::string prefix);
  //Returns vector of all words in trie
  std::vector<std::string> getWords();

  int levenshteinDistance(std::string X, int m, std::string Y, int n);

private:
  Node *root;
  //recursive helper
  void traverse (std::string word, Node *node, std::vector<std::string> &v);
};
#endif
