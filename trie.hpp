//Implementaion of Trie
#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <iostream>


const int ALPHABET_SIZE = 26;


struct TrieNode
{
  TrieNode *children[ALPHABET_SIZE];
  bool isEndOfWord;
};

//Returns new trie node initialized to NULL
//for when creating new node
struct TrieNode *getNode()
{
  TrieNode *newNode = new TrieNode;
  newNode->isEndOfWord = false;

  for(int  i = 0; i < ALPHABET_SIZE; i++)
    newNode->children[i] = NULL;

  return newNode;
}


class Trie
{
public:
  Trie();
  ~Trie();
  TrieNode *getRoot(){ return root; }
  bool search(std::string word);
  bool isLastNode(TrieNode *root);
  void insert(std::string word);
  void loadDictionary(std::string dictionaryFile);
  std::vector<std::string> prefixSearch(std::string prefix);
  void traversePrefix(std::string prefix, TrieNode *node, std::vector<std::string> &v);
  int levenshteinDistance(std::string X, int m, std::string Y, int n);
  void traverse (std::string word, TrieNode *node, std::vector<std::string> &v);
  std::vector<std::string> getWords();
private:
  TrieNode *root;
};


#endif
