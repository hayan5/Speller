#include "trie.cpp"
#include <fstream>
#include <string>
#include <sstream>


Trie dictionary;

//Menu for main function
int menu()
{
  char choice;
  std::cout<<"--------Menu--------"<<std::endl;
  std::cout<<"Would You Like to:"<<std::endl;
  std::cout<<"  (1)| Quick Look Up"<<std::endl;
  std::cout<<"  (2)| Spell Check File"<<std::endl;
  std::cout<<"  (3)| Add to Dictionary"<<std::endl;
  std::cout<<"  (4)| Quit"<<std::endl;
  std::cin>>choice;

  if(isdigit(choice)){
    choice = choice - '0';
    return choice;
  }
  else
    return 0;

}

//Menu for spellCheckFile function
int fileMenu()
{
  char choice;

  std::cout<<"Would you like to:"<<std::endl<<" (1)Get suggestions"<<
  std::endl<<" (2)Add to dictionary"<<std::endl<<" (3)Ignore"<<std::endl;
  std::cin>>choice;
  std::cout<<std::endl;

  if(isdigit(choice)){
    choice = choice - '0';
    return choice;
  }
  else
    return 0;
}

//Quick look up user option with auto complete
//Prints out top 5 suggestions from the prefix inputed
void quickLookUp()
{
  std::string wordInput;
  std::vector<std::string> suggestions;

  std::cout<<"Enter the word you would like to look up:"<<std::endl;
  std::cout<<"***If you dont know the spelling of the word enter the prefix"<<std::endl;
  std::cout<<"and you will be given suggestions based off of your entry***"<<std::endl;
  std::cout<<std::endl;

  std::cin>>wordInput;
  std::cout<<std::endl;
  //Makes sure input only contains letters
  for(int i = 0; i < wordInput.length(); i++)
  {
    if(isalpha(wordInput[i]) == false){
      std::cout<<"Please enter a vaild word"<<std::endl;
      return;
    }
  }
  //Makes input only lower case
  for(int i = 0; i < wordInput.length(); i++)
    wordInput[i] = tolower(wordInput[i]);


  suggestions = dictionary.prefixSearch(wordInput);
  //More than 5 suggestions
  if(suggestions.size() > 5){
    for(int i = 0; i < 5; i++){
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }
  //5 or less suggestions
  else if(suggestions.size() <= 5 && suggestions.size() != 0){
    for(int i = 0; i < suggestions.size(); i++){
      std::cout<<i+1<<":"<<suggestions[i]<<std::endl;
    }
  }
  //No suggestions
  else
    std::cout<<"There were no suggestions from your input"<<std::endl;

}


//Helper function for spellCheckFile function
void fileGetSuggestions(std::string X)
{
  std::cout<<"---suggestions---"<<std::endl;
  std::vector<std::string> allWords = dictionary.getWords();
  std::vector<std::string> suggestions;
  std::string Y;

  for(int i = 0; i < allWords.size(); i++)
  {
    Y = allWords[i];
    int tempDistance = 100;
    tempDistance = dictionary.levenshteinDistance(X, X.length(), Y, Y.length());
    if(tempDistance < 2)
      suggestions.push_back(Y);
  }
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
  else
    std::cout<<"**No suggestions**"<<std::endl;
  std::cout<<std::endl;
}

//Helper function for spellCheckFile function
void fileAddToDictionary(std::string word)
{

  for(int i = 0; i < word.length(); i++)
  {
    if(isalpha(word[i]) == false){
      std::cout<<"Cannot add numbers to dictionary"<<std::endl;
      return;
    }
  }

  for(int i = 0; i < word.length(); i++)
    word[i] = tolower(word[i]);

  if(dictionary.search(word)){
    std::cout<<"Word already exists in dictionary"<<std::endl;
    return;
  }

  dictionary.insert(word);
  if(dictionary.search(word))
    std::cout<<word<<" successfully added to dictionary"<<std::endl;
  else
    std::cout<<"Error adding "<<word<<" to dictionary"<<std::endl;

  std::cout<<std::endl;
}

//Gets file name from user input then parses each line
//into words. For each line the user will be told which
//words are misspelled and given the option to either add
//that word to the dictionary or to get spelling suggestions
void spellCheckFile(){
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
            if(dictionary.search(word) == false)
            {
              std::cout<<"---"<<printWord<<"---"<<std::endl;
              int choice = 0;
              bool nextWord = false;

              while(nextWord == false)
              {
                choice = fileMenu();

                if(choice == 1){
                  fileGetSuggestions(word);
                  nextWord = true;
                }

                else if(choice == 2){
                  fileAddToDictionary(word);
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

//Adds inputed word to the Trie
void addToDictionary(){
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

  if(dictionary.search(newWord)){
    std::cout<<"Word already exists in dictionary"<<std::endl;
    return;
  }

  dictionary.insert(newWord);
  if(dictionary.search(newWord)){
    std::cout<<newWord<<" successfully added to dictionary"<<std::endl;
  }
  else
    std::cout<<"Error adding "<<newWord<<" to dictionary"<<std::endl;
}

void quit(){
  std::cout<<"Goodbye"<<std::endl;

}


int main(){

  std::cout<<"--------Welcome--------"<<std::endl;
  //Trie Created using txt file
  dictionary.createDictionary("google-10000-english.txt");



  int option = 0;
  bool isQuit = false;
  std::cout<<std::endl;

  while(isQuit == false)
  {
    option=menu();
    std::cout<<"-----------------------"<<std::endl;
    if(option == 1){
      quickLookUp();
    }

    else if(option == 2){
      spellCheckFile();
    }

    else if(option == 3){
      addToDictionary();
    }

    else if(option == 4){
      quit();
      isQuit = true;
    }

    else{
      std::cout<<"Please Enter a Valid Choice"<<std::endl;
    }

  }

}
