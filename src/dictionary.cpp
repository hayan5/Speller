#include <trie.hpp>
#include <dictionary.hpp>



Dictionary::Dictionary() {
  trie = new Trie();
  this->root = trie->getRoot();
}

Dictionary::~Dictionary() {
  delete this->root;
}

// Returns 0 if word already exists, 1 if word insert success
// -1 word insert error
void Dictionary::insert(const std::string& word) {
  
  this->trie->insert(this->root, word);
}

// Takes dictionary file as input and adds words to dictionary
void Dictionary::create(const std::string& filename) {
  
  std::string line;
  std::ifstream data(filename);

  if (data.is_open()) {
    while(std::getline (data,line)){
      insert(line);
    }
    
    data.close();
    std::cout<<"Dictionary created using: "<<filename<<"\n";
  }
  else
    std::cout<<"Unable to open dictionary file: "<<filename<<'\n';
}
std::vector<std::string> Dictionary::get_words() {
  TrieNode *temp = this->root;
  std::vector<std::string> words;

  std::string empty = "";
  this->traverse(empty, temp, words);

  return words;
}
std::vector<std::string> Dictionary::prefix_search(std::string& prefix) {
  TrieNode* temp = this->root;
  // std::cout<<this->root<<'\n';
  std::vector<std::string> completions;

  for (int i = 0; i < prefix.length(); i++) {
    if (temp->children[prefix[i]])
      temp = temp->children[prefix[i]];
  }

  this->traverse(prefix, temp, completions);


  return completions;
}

std::vector<std::string> Dictionary::get_suggestions(std::string& word, int max_cost) {
  // std::cout<<this->root<<'\n';
  int size = word.length() + 1;
  int row[size];

  for (int i = 0; i < size; i++) {
    row[i] = i;
  }
  
  std::vector<std::string> suggestions;
  TrieNode* node = this->root;

  for (int i = 0; i < size-1; i++) {
    if (node->children.find(word[i]) != node->children.end()) {
      
      distance(node->children[word[i]], word[i], word, row, suggestions, max_cost);
    }
  }

  return suggestions;
}
  
bool Dictionary::search(const std::string& word) {
  TrieNode* temp = this->root;
  bool flag = this->trie->contains(temp, word);
  // std::cout<<this->root<<'\n';
  return flag;
}

void Dictionary::distance(TrieNode* node, char ch, std::string& word, int *row, std::vector<std::string> &suggestions,int max_cost) {
  // std::cout<<ch<<'\t'<<word<<'\t';

  int size = word.length() + 1;
  int new_row[size];
  // std::cout<<size<<'\t';
  new_row[0] = row[0] + 1;

  int insert_cost, delete_cost, sub_cost;

  for (int i = 1; i < size; i++){
    insert_cost = new_row[i - 1] + 1;
    delete_cost = row[i] + 1;

    if (word[i - 1] == ch)
      sub_cost = row[i - 1];

    else
      sub_cost = row[i - 1] + 1;
    // std::cout<<i;
    new_row[i] = std::min(insert_cost,delete_cost);
    new_row[i] = std::min(sub_cost,new_row[i]);
  }
  // std::cout<<'\t';
  

  if (new_row[size-1] <= max_cost && node->is_leaf_node == true) {
    // std::cout<<node->path<<'\t';
    suggestions.push_back(node->path);
  }

  int _min = 99999;
  for (int i = 0; i < size; i ++) {
    
    if(new_row[i] < _min)
      _min = new_row[i];
  }
  
  if (_min <= max_cost) {
    for (auto it = node->children.begin(); it != node->children.end(); it++) {
      // std::cout<<it->second<<'\t'<<it->first<<'\n';
      if(it->second != nullptr) {
        distance(it->second, it->first, word, new_row, suggestions,max_cost);
      }
    }
  }
}

void Dictionary::traverse(std::string &word, TrieNode* node, std::vector<std::string> &v) {
  if(node == nullptr)
    return;

  if(node->is_leaf_node && this->trie->contains(this->root,word))
    v.push_back(word);

  for(auto x : node->children) {
    std::string temp = word + x.first;
    traverse(temp, x.second, v);
  }
} 

