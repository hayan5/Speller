# Speller
Spell correction and auto complete implemented using a trie

After completeing this project for my data structures class I plan to continue working on this repository
until I have a completely optimized working user friendly application.

__________________________________________________________________________________
**---Future Implementations---**
1) Optimized Levenstien Distance Algorithm
2) Memory optimized trie
3) Fix small issues in user options
4) Create user interface
______________________________________________________________________________________

**Version: 0.1.0**
--***FINAL PROJECT VERSION***

 ***CSCI-Data Structures Final Project (First Release & Complete Project)***

  Implemented trie data structure to store dictionary with fast search and insertion 
  
  User has options to add to:
  
    1) search for word (prefix search)
    2) spell check a file 
    3) add word to dictionary
  
  **Trie Data Structure:**
  
    -Initiatally created at start using a txt file of 10000 most common words with O(word_length) insertion time
    -Each node contains an array of pointer to its children nodes (size 26) and a boolean value marking the last letter 
     of a word
    -worst case space compelxity: O(26 * avg._word_length * number_of_words)
    
      Issues:
      -Large unnecessary memory usage (each node has an array taking up 208 bits, even if only 8 are needed)
 
  **Prefix Search:**
  
    -Class function returns a vector of suffix words by traversing through the trie to the entered prefix then passes prefix 
     string and current node to helper function 
    -Helper function returns a vector of all children words in alphabetical order
    -Main function takes the returned class function vector and prints out first 5 words
    
      Issues:
      -Although working without any issues, giving users suggested words in alphabetical order isnt ideal, expecially when
      there are signifcantly more that 5 suggested words in the vector.
  
  **File Spell Check:**
  
    -Reads in file parsing out all punctuation and letters
    -Searches for word in trie and if non-existant outputs top 5 suggested words
    -Suggested words are found using the Levenshtien Distance algorithm (2 or less cost)
    
      Issues:
      -I currently have a very simple implementation of the Levenshtien Distance algorithm which individualy computes
      the cost for each word in the trie. Very slow and inefficent. Works for misspelled words of 4 letters or less but
      the time to find suggestions increases exponentailly for each additional letter.
  
  **Add Word to dictionary:**
  
    -Makes sure word does not alreadt exist in trie, if not uses the insertion class method
    
    Issues: 
     -Currently doesnt added word to txt file so users added words are not saved between sessions (Currently not supported
     to prevent user from adding multiple words by mistake or if they want to start fresh dictionary)



