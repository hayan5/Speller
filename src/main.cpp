#include <speller.hpp>
#include <iostream>

int main() {
  
 Speller speller;
  std::cout<<"--------Welcome--------"<<std::endl;
  std::string filename = "dictionary10000.txt";
  speller.dictionary->create(filename);
  
  int option = 0;
  bool isQuit = false;
  std::cout<<std::endl;

  while(isQuit == false)
  {
    option=speller.menu();
    std::cout<<"-----------------------"<<std::endl;
    if(option == 1){
      speller.look_up();
    }

    else if(option == 2){
      speller.spell_check_file();
    }

    else if(option == 3){
      speller.add_to_dictionary();
    }

    else if(option == 4){
      speller.quit();
      isQuit = true;
    }

    else{
      std::cout<<"Please Enter a Valid Choice"<<std::endl;
    }

  }
  
  return 0;
}