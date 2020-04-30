/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef BOARD_H
#define BOARD_H
#define BOARD_DEFAULT_SIDE_LEN 4

#include <iostream> // for op<<
#include <string>   // string for word checking
#include <stack>     // path backtracking
#include <utility>   // pair (row, column coordinates)

class Board
{
  // data
  char** board;
  int colSize;
  int rowSize;

  // if true: allowed to return to the same tile more than once in a word
  bool duplicates; 

  // helper functions
  void MakeBoard();  // allocates data for the board
  void ClearBoard(); // decallocates data for the board, sets sizes to 0

  // recursive helper for IsValid function
  bool ValidRecursive(std::string const& word, std::stack<std::pair<int, int> >& path)const;

public:
  // constructors
  Board(int sideLength = BOARD_DEFAULT_SIDE_LEN); // default dtor = square board
  Board(int colSize, int rowSize);                // rectangle board
  // destructor
  ~Board();

  // setters
  void Duplicates(bool allowDuplicates);

  // getters
  bool Duplicates()const;
  int ColSize()const;
  int RowSize()const;

  // randomizes the characters on the board
  void Randomize(); 

  // determine if a word is valid; returns true if the word is valid on the board
  bool IsValidWord(std::string const& word) const;

  friend std::ostream& operator<<(std::ostream& os, Board const& obj);

  // overloading [][] operator using proxy
  class Proxy
  {
    char* row;
  public:
    Proxy(char* row);
    char operator[](int i) const;
  };
  Proxy operator[](int i) const;
};

#endif // !BOARD_H
