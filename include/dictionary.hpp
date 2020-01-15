#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <trie.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Dictionary {
  public:
    Dictionary();
    ~Dictionary();

    void insert(const std::string& word);
    void create(const std::string& filename);
    std::vector<std::string> prefix_search(std::string& prefix);
    std::vector<std::string> get_words();
    std::vector<std::string> get_suggestions(std::string& word, int max_cost);
    bool search(const std::string& word);
  
  private:
    TrieNode* root;
    Trie* trie;

    void traverse(std::string &word, TrieNode* node, std::vector<std::string> &v);
    void distance(TrieNode* node, char ch, std::string& word, int *row, std::vector<std::string> &suggestions,int max_cost);
};


#endif