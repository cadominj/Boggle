/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef WORD_LIST_H
#define WORD_LIST_H

#define DICTIONARY_FILE "Dictionary/words_alpha.txt"

#include <set>       // underlying structure of WordList is a tree for fast searching
#include <string>    // string for the word type
#include <iostream>  // ostream for op<<


class WordList
{
protected:
  // data
  std::set<std::string> words;
  // protected methods
  std::string* FindNode(std::string const& word) const; // more powerful internal find function
public:
  // constructors
  WordList();                               // default ctor -- empty word list
  WordList(std::string const& filename);    // initialize from file
  // destuctor
  ~WordList();

  bool Empty()const;                        // returns true if empty, otherwise returns false
  bool Find(std::string const& word) const; // returns true if the word exists, otherwise returns false

  void Insert(std::string const& word);     // adds a word to the word list
  void Remove(std::string const& word);     // removes a word from the word list

  void ReadFile(std::string const& filename = DICTIONARY_FILE); // takes all words from the file and inserts them

  friend std::ostream& operator<<(std::ostream & os, WordList const& obj);
};

#endif