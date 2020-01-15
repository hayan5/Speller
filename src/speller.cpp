#include <speller.hpp>
#include <dictionary.hpp>


Speller::Speller() {
  dictionary = new Dictionary();
}

int Speller::menu() {
  char choice;

  std::cout<<"--------Menu--------\n";
  std::cout<<"Would You Like to:\n";
  std::cout<<"  (1)| Quick Look Up\n";
  std::cout<<"  (2)| Spell Check File\n";
  std::cout<<"  (3)| Add to Dictionary\n";
  std::cout<<"  (4)| Quit\n";
  
  std::cin>>choice;
  if (isdigit(choice)) {
    choice = choice - '0';
    return choice;
  }

  return 0;
}

int Speller::file_menu() {
  char choice;

  std::cout<<"Would you like to:\n";
  std::cout<<"\t(1)Get suggestions\n";
  std::cout<<"\t(2)Add to dictionary\n";
  std::cout<<"\t(3)Ignore\n";
  
  std::cin>>choice;
  std::cout<<'\n';

  if (isdigit(choice)) {
    choice = choice - '0';
    return choice;
  }

  return 0;
}

void Speller::look_up() {

  std::string input;
  std::vector<std::string> suggestions;
  
  std::cout<<"Enter the word you would like to look up:\n";
  std::cout<<"***If you dont know the spelling of the word enter the prefix\n";
  std::cout<<"and you will be given suggestions based off of your entry***\n\n";
  
  std::cin>>input;
  std::cout<<'\n';

  //Makes sure input only contains letters
  for(int i = 0; i < input.length(); i++)
  {
    if(isalpha(input[i]) == false){
      std::cout<<"Please enter a vaild word\n";
      return;
    }
  }

  //Makes input only lower case
  for(int i = 0; i < input.length(); i++)
    input[i] = tolower(input[i]);

  suggestions = this->dictionary->prefix_search(input);

  if(suggestions.size() > 5){
    for(int i = 0; i < 5; i++){
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }

  else if(suggestions.size() <= 5 && suggestions.size() != 0){
    for(int i = 0; i < suggestions.size(); i++){
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }

  else
    std::cout<<"There were no suggestions from your input"<<std::endl;
}


void Speller::get_suggestions(std::string &word) {
  std::cout<<"---suggestions---"<<std::endl;
  // std::vector<std::string> allWords = this->dictionary->getWords();
  std::vector<std::string> suggestions;
  int max_cost = 1;

  suggestions = this->dictionary->get_suggestions(word, max_cost);

  if(suggestions.size() <= 5 && suggestions.size() > 0){
    for(int i = 0; i < suggestions.size(); i++)
    {
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }

  else if(suggestions.size() > 5){
    for(int i = 0; i < 5; i++)
    {
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }

  else{
    std::cout<<"**No suggestions**"<<std::endl;
  }
  std::cout<<std::endl;
}

void Speller::file_add_to_dictionary(std::string &word) {
  
  for(int i = 0; i < word.length(); i++)
  {
    if(isalpha(word[i]) == false){
      std::cout<<"Cannot add numbers to dictionary"<<std::endl;
      return;
    }
  }

  for(int i = 0; i < word.length(); i++)
    word[i] = tolower(word[i]);

  if(this->dictionary->search(word)){
    std::cout<<"Word already exists in dictionary"<<std::endl;
    return;
  }

  this->dictionary->insert(word);
  if(this->dictionary->search(word))
    std::cout<<word<<" successfully added to dictionary"<<std::endl;
  else
    std::cout<<"Error adding "<<word<<" to dictionary"<<std::endl;

  std::cout<<std::endl;
}

void Speller::spell_check_file() {
  std::string filename;
  std::string line;
  int lineNumber = 1;

  std::cout<<"Enter The Name of the File You Would Like to Check:"<<std::endl<<std::endl;
  std::cin>>filename;
  std::cout<<std::endl;
  std::ifstream data (filename);

  if(data.is_open()){
    while(getline (data,line)){
      //Parse document from punctuation
      for(int i = 0, len = line.size(); i < len; i++)
      {
        if(ispunct(line[i])){
          line.erase(i--, 1);
          len = line.size();
        }
      }

      std::cout<<"Line #"<<lineNumber<<":"<<std::endl;
      std::cout<<line<<std::endl<<std::endl;
      std::cout<<"Misspelled words:"<<std::endl;

      //Parse document from spaces
      std::istringstream iss(line);
      while(iss){
        std::string word;
        std::string printWord;
        iss >> word;
        if(word.length()!= 0)
        {
          //Checks if word string is a number
          bool isNumber = false;
          int digitCount = 0;
          for(int i = 0; i < word.length(); i++)
          {
            if(isdigit(word[i]) == true)
              digitCount++;
          }
          if(digitCount == word.length()){
            isNumber = true;
          }

          printWord = word;
          if(isNumber == false)
          {
            for(int i = 0; i < word.length(); i++)
              word[i] = tolower(word[i]);

            //Misspelled words(not found in the trie)
            if(this->dictionary->search(word) == false)
            {
              std::cout<<"---"<<printWord<<"---"<<std::endl;
              int choice = 0;
              bool nextWord = false;

              while(nextWord == false)
              {
                choice = file_menu();

                if(choice == 1){
                  get_suggestions(word);
                  nextWord = true;
                }

                else if(choice == 2){
                  file_add_to_dictionary(word);
                  nextWord = true;
                }

                else if(choice == 3){ nextWord = true;}

                else
                  std::cout<<"Please Enter a Valid Choice"<<std::endl;
              }
            }
          }
        }
      }
      lineNumber++;
    }
    data.close();
  }
  else{
    std::cout<<"Unable to Open File"<<std::endl;
  }
}

void Speller::add_to_dictionary() {
  std::string newWord;
  std::cout<<"Enter the word you would like to add:"<<std::endl;
  std::cin>>newWord;

  //Makes sure input only contains letters
  for(int i = 0; i < newWord.length(); i++)
  {
    if(isalpha(newWord[i]) == false){
      std::cout<<"Please enter a vaild word"<<std::endl;
      return;
    }
  }
  //Makes input only lower case numbers
  for(int i = 0; i < newWord.length(); i++)
    newWord[i] = tolower(newWord[i]);

  if(this->dictionary->search(newWord)){
    std::cout<<"Word already exists in dictionary"<<std::endl;
    return;
  }

  this->dictionary->insert(newWord);
  if(this->dictionary->search(newWord)){
    std::cout<<newWord<<" successfully added to dictionary"<<std::endl;
  }
  else
    std::cout<<"Error adding "<<newWord<<" to dictionary"<<std::endl;
}

void Speller::quit(){
  std::cout<<"Goodbye"<<std::endl;
}