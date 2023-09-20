/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "WordList.h"
#include <fstream>    // file IO

/*****************************************************************************
Description: Default constructor; creates an empty word list.
*****************************************************************************/
WordList::WordList() : words(std::set<std::string>()) {}

/*****************************************************************************
Description: Creates a word list from the given file.
             (may be useful for saving a game & coming back to later, 
             or for initializing a dictionary word list) 
Assumptions:
      Input: - filename = name of the file to read into the word list
                          (separate words should be separated by a line break)
*****************************************************************************/
WordList::WordList(std::string const& filename) : words(std::set<std::string>())
{
  ReadFile(filename);
}

/*****************************************************************************
Description: A trivial implementation for a destructor. 
             Dynmaic memory is handled by the STL containers.
*****************************************************************************/
WordList::~WordList(){}


/*****************************************************************************
Description: Returns true if the word list is empty, otherwise returns false.
*****************************************************************************/
bool WordList::Empty() const
{
  return words.empty();
}

/*****************************************************************************
Description: Determines if the given word exists in the word list, and returns
             a handle to that data.
Assumptions: The words must match exactly character-for-character for it to exist.
      Input: - word = word to find in the word list
     Output: Returns the data of the found node, if nothing was found, returns nullptr.
*****************************************************************************/
std::string* WordList::FindNode(std::string const& word) const
{
  std::string* address = nullptr; // address of the word in the list
  for (std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it)
    if (*it == word)
      address = const_cast<std::string *>(&*it);
  return address;
}

/*****************************************************************************
Description: Determines if the given word exists in the word list.
Assumptions: The words must match exactly character-for-character for it to exist.
      Input: - word = word to check the existance of
     Output: Returns true if the word exists in the list, otherwise returns false.
*****************************************************************************/
bool WordList::Find(std::string const& word) const
{
  return FindNode(word) != nullptr;
}

/*****************************************************************************
Description: Adds the given word to the word list.
Assumptions: Assumes the word is valid (only alpha characters, no spaces).
      Input: - word = word to insert into the word list
*****************************************************************************/
void WordList::Insert(std::string const& word)
{
  words.insert(word);
}

/*****************************************************************************
Description: Removes the given word from the word list.
      Input: - word = word to remove from the word list
*****************************************************************************/
void WordList::Remove(std::string const& word)
{
  words.erase(word);
}

/*****************************************************************************
Description: Inserts all of the words in a given file into an existing word list.
Assumptions: Assumes that the file does not use special characters or spaces.
      Input: - filename = name of file to read into the word list
*****************************************************************************/
void WordList::ReadFile(std::string const& filename)
{
  std::ifstream file(filename);
  // if the file opened successfully
  if (file.is_open())
  {
    std::string line;
    // read each line as a single word into the word list
    while (std::getline(file, line))
      Insert(line);
    file.close();
  }
  // if the file failed to open
  else
  {
    // throw exception or print error
    std::cout << "Error: Could not open file \"" << filename << "\" for read." << std::endl;
  }
}

/*****************************************************************************
Description: Sends word list to an output stream.
      Input: - os  = output stream to write the word list into
             - obj = the word list
     Output: Returns the modified output stream.
*****************************************************************************/
std::ostream& operator<<(std::ostream& os, WordList const& obj)
{
  for (std::set<std::string>::iterator it = obj.words.begin(); it != obj.words.end(); ++it)
    os << *it << std::endl;
  return os;
}
