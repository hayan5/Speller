#include "trie.hpp"
#include <fstream>

Trie::Trie()
{
  root = getNode();
}

//Destuctor helper function

Trie::~Trie()
{

}

//Returns True if input word exsits in trie
bool Trie::search(std::string word)
{
  TrieNode *temp = this->root;

  for (int i = 0; i < word.length(); i++)
  {
    int index = word[i] - 'a';
    if(!temp->children[index])
      return false;

    temp = temp->children[index];
  }

  return (temp != NULL && temp->isEndOfWord);
}

//Returns true if there are no other children(not a prefix)
bool Trie::isLastNode(TrieNode *root)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
    if(root->children[i])
      return false;
  return true;
}


//Inserts word into trie
void Trie::insert(std::string word)
{
  TrieNode *temp = this->root;
  for (int i = 0; i < word.length(); i++)
  {
    int index = word[i] - 'a';
    if (!temp->children[index])
      temp->children[index] = getNode();

    temp = temp->children[index];
  }

  temp->isEndOfWord = true;
}



//Creates trie using words from input file
void Trie::loadDictionary(std::string dictionaryFile)
{
  std::string line;
  std::ifstream data(dictionaryFile);
  int n = 1;
  if(data.is_open()){
    while(getline (data,line)){
      for(int i = 0, len = line.length(); i < len; i++)
      {
        if(ispunct(line[i])){
          line.erase(i--, 1);
          len = line.size();
        }
      }
      for(int i = 0; i < line.length(); i ++)
        line[i] = tolower(line[i]);

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
  TrieNode *temp = this->root;
  int index;
  std::vector<std::string> possible;
  for(int i = 0; i < prefix.length(); i++)
  {
    index = prefix[i] - 'a';
    if(temp->children[index] != NULL)
      temp = temp->children[index];
  }

  traversePrefix(prefix, temp, possible);

  return possible;

}
//Prefix search recursive helper function
void Trie::traversePrefix(std::string prefix, TrieNode *node, std::vector<std::string> &v)
{
  if(node == NULL)
    return;
  if(node->isEndOfWord && search(prefix) == true)
    v.push_back(prefix);

  for(int i = 0; i < ALPHABET_SIZE; i++)
  {
    if(node->children[i])
      traversePrefix(prefix + (char)(i + 'a'), node->children[i], v);
  }
}

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

void Trie::traverse(std::string word, TrieNode *node, std::vector<std::string> &v)
{
  if(node->isEndOfWord && search(word) == true)
    v.push_back(word);

  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if(node->children[i])
    {
      traverse(word + (char)(i + 'a'), node->children[i], v);
    }
  }
}

std::vector<std::string> Trie::getWords()
{
  TrieNode *temp = this->root;
  std::vector<std::string> possible;

  traverse("", temp, possible);

  return possible;
}
