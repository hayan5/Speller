#include "trie.hpp"
#include <fstream>

Trie::Trie()
{
  root = getNewNode();
}

Trie::~Trie(){}

//Inserts word into trie
void Trie::insert(std::string word)
{
  Node *temp = this->root;

  for (int i = 0; i < word.length(); i++)
  {
    char x = word[i];

    if (temp->map[x] == NULL)
      temp->map[x] = getNewNode();

    temp = temp->map[x];
  }
  temp->LeafNode = true;


}

//Returns True if input word exsits in trie
bool Trie::search(std::string word)
{
  Node *temp = this->root;
  for (int i = 0; i < word.length(); i++)
  {
    temp = temp->map[word[i]];

    if(!temp)
      return false;
  }
  return temp->LeafNode;
}

//Creates trie using words from input file
void Trie::createDictionary(std::string dictionaryFile)
{
  std::string line;
  std::ifstream data(dictionaryFile);

  if(data.is_open()){

    while(getline (data,line)){
      insert(line);
    }

    data.close();
    std::cout<<"Dictionary Created"<<std::endl;
  }

  else
    std::cout<<"Unable to open dictionary file"<<std::endl;
}

//Travereses tree to prefix then calls to traverse function
//to get all possible endings then returns vectors with endings
std::vector<std::string> Trie::prefixSearch(std::string prefix)
{
  Node *temp = this->root;
  std::vector<std::string> completions;

  for (int i = 0; i < prefix.length(); i++)
  {
    if(temp->map[prefix[i]])
      temp = temp->map[prefix[i]];
  }

  traverse(prefix, temp, completions);

  return completions;
}

//****
int Trie::levenshteinDistance(std::string X, int m, std::string Y, int n)
{
  if (m == 0)
    return n;

  if (n == 0)
    return m;

  int cost;

  if (X[m - 1] == Y[n - 1])
    cost = 0;
  else
    cost = 1;

  return std::min(std::min(levenshteinDistance(X, m - 1, Y, n) + 1,
            levenshteinDistance(X, m, Y, n - 1) + 1),
            levenshteinDistance(X, m - 1, Y, n - 1) + cost);
}

//*****
void Trie::traverse(std::string word, Node *node, std::vector<std::string> &v)
{
  if(node == NULL)
    return;

  if(node->LeafNode && search(word) == true)
    v.push_back(word);

  for(auto x : node->map)
    traverse(word + x.first, x.second, v);
}

std::vector<std::string> Trie::getWords()
{
  Node *temp = this->root;
  std::vector<std::string> possible;

  traverse("", temp, possible);
  return possible;
}
