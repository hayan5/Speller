#ifndef SPELLER_HPP
#define SPELLER_HPP

#include <dictionary.hpp>
#include <trie.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class Speller {
  public:
    Speller();

    int menu();
    int file_menu();
    void look_up();
    void get_suggestions(std::string &word);
    void file_add_to_dictionary(std::string &word);
    void spell_check_file();
    void add_to_dictionary();
    void quit();
  
    Dictionary* dictionary;
};



#endif