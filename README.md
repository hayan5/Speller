# Speller

  make: all, run, clean


  Implemented trie data structure to store dictionary with fast search and insertion 
  
  User has options to add to:
  
    1) search for word (prefix search)
    2) spell check a file 
    3) add word to dictionary
  
  **Trie Data Structure:**
  
    -Initiatally created at start using a txt file of 10000 most common words with O(word_length) insertion time
    -Each node contains an array of pointer to its children nodes (size 26) and a boolean value marking the last letter 
     of a word
    
 
  **Prefix Search:**
  
    -Class function returns a vector of suffix words by traversing through the trie to the entered prefix then passes prefix 
     string and current node to helper function 
    -Helper function returns a vector of all children words in alphabetical order
    -Main function takes the returned class function vector and prints out first 5 words

    
  
  **File Spell Check:**
  
    -Reads in file parsing out all punctuation and letters
    -Searches for word in trie and if non-existant outputs top 5 suggested words
    -Suggested words are found using the Levenshtien Distance algorithm (2 or less cost)
    
  
  **Add Word to dictionary:**
  
    -Makes sure word does not alreadt exist in trie, if not uses the insertion class method




