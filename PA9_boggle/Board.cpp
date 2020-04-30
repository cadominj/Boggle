/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Board.h"
#include <cstdlib>   // rand
#include <ctype.h>   // toupper
#include <exception> // exception handling
#include <iostream>  // cout, endl (printing errors to console)

/*****************************************************************************
Description: Default constructor: creates a square board with sides of size sideLength.
      Input: - sideLength = number of rows and number of columns in the board
*****************************************************************************/
Board::Board(int sideLength) : board(nullptr), colSize(sideLength), rowSize(sideLength), duplicates(true)
{
  try
  {
    MakeBoard();
  }
  catch (std::exception&)
  {
    std::cout << "Error: new [] has failed" << std::endl;
  }
}

/*****************************************************************************
Description: Constructor: creates a (rectangle) board of dimensions colSize x rowSize.
      Input: - colSize = number of columns on the board
             - rowSize = number of rows on the board
*****************************************************************************/
Board::Board(int colSize, int rowSize) : board(nullptr), colSize(colSize), rowSize(rowSize), duplicates(true)
{
  try
  {
    MakeBoard();
  }
  catch (std::exception&)
  {
    std::cout << "Error: new [] has failed" << std::endl;
  }
}

/*****************************************************************************
Description: Destructor: deallocate the board.
*****************************************************************************/
Board::~Board()
{
  ClearBoard();
}

/*****************************************************************************
Description: Randomizes the board with uppercase letters.
*****************************************************************************/
void Board::Randomize()
{
  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)
      board[i][j] = rand() % 26 + 'A';
}

/*****************************************************************************
Description: Duplicates setter.
      Input: - allowDuplicates = true to enable, false to disable duplicates
*****************************************************************************/
void Board::Duplicates(bool allowDuplicates)
{
  duplicates = allowDuplicates;
}

/*****************************************************************************
Description: Duplicates getter.
     Output: Returns true if duplicates are enabled, otherwise false.
*****************************************************************************/
bool Board::Duplicates()const
{
  return duplicates;
}

/*****************************************************************************
Description: Column Size getter.
     Output: Returns the current number of columns. (width of board)
*****************************************************************************/
int Board::ColSize()const
{
  return colSize;
}

/*****************************************************************************
Description: Row Size getter.
     Output: Returns the current number of rows. (height of board)
*****************************************************************************/
int Board::RowSize()const
{
  return rowSize;
}


/*****************************************************************************
Description: Given a valid position (path.top) that holds the first letter of 
             the given word recursively find if that word exists on the board
             (successive letters in the word must be horizontally, vertically, 
             or diagonally adjactent to each other on the board to be valid.)
Assumptions: Assumes that path already holds the first, so-far valid, {row,col} 
             coordinate.
      Input: - word = word to check the validity of
             - path = stack of {row, col} coordinates used to trace the taken path.
     Output: returns true if the word is valid on the board, otherwise returns false.
*****************************************************************************/
bool Board::ValidRecursive(std::string const& word, std::stack<std::pair<int, int> >& path) const
{
  // base case: found the entire word
  if (path.size() == word.size())
    return true;
  // check surroundings: loop through row and column offsets for surrounding letters
  bool valid = false;
  for (int r = -1; !valid && r <= 1; ++r)
  {
    for (int c = -1; !valid && c <= 1; ++c)
    {
      // new row and column
      int row = r + path.top().first;
      int col = c + path.top().second;
      // don't check current position or out of bounds
      if ((r != 0 || c != 0) &&          // not current possition
        !(row < 0 || row >= rowSize ||   // not out of bounds
          col < 0 || col >= colSize))
      {
        // if the new position has the next letter, try it
        if (board[row][col] == toupper(word[path.size()]))
        {
          path.push({ row, col });
          if (!(valid = ValidRecursive(word, path)))
            path.pop();
        }
      }
    }
  }
  return valid;
}

/*****************************************************************************
Description: Determines if the given word is connected on the board.
Assumptions: If duplicates is set to true (use Duplicate() getter/setter),
             then the word may reuse tiles, otherwise the word may not.
      Input: - word = word to check for on the board
     Output: Returns true if the word is valid, otherwise returns false.
*****************************************************************************/
bool Board::IsValidWord(std::string const& word) const
{
  bool valid = false;
  
  // early exit if word doesn't exist
  if (word.length() == 0)
    return valid;

  // find all instances of the first letter on the board
  for (int r = 0; !valid && r < rowSize; ++r)
  {
    for (int c = 0; !valid && c < colSize; ++c)
    {
      // new instance of first letter has been found
      if (board[r][c] == toupper(word[0]))
      {
        // find rest of word
        std::stack < std:: pair<int, int> > path;
        path.push({ r, c }); // first letter
        // if all good: pop stack into frequency array & look for duplicates (same tile used more than once in one word)
        if (valid = ValidRecursive(word, path))
        {
          // if duplicates aren't allowed, weed out valid words that use duplicates
          if (!duplicates)
          {
            // move stack into frequency array (very limited number of possible coordinates)
            int size = rowSize * colSize;
            int* freq = new (std::nothrow) int[size];
            // new was successful in creating space for the array
            if (freq != nullptr)
            {
              for (int i = 0; i < size; ++i)
                freq[i] = 0;
              while (!path.empty())
              {
                // if a duplicate is found, the word is not valid (1D index = r * #col + c)
                if (++freq[path.top().first * colSize + path.top().second] > 1)
                  valid = false;
                path.pop();
              }
              delete[] freq;
            }
          }
        }
        else
          path.pop();
      }
    }
  }
  return valid;
}

/*****************************************************************************
Description: Allocates the board using the current sizes.
Assumptions: Assumes rowSize & colSize are already set (in the constructor).
*****************************************************************************/
void Board::MakeBoard()
{
  if (board == nullptr)
  {
    // set up row pointers (indexed into via row index)
    board = new (std::nothrow) char * [rowSize]; 
    if (board != nullptr)
    {
      // set up each row (indexed into via column index)
      for (int r = 0; r < rowSize; ++r)
      {
        try
        {
          board[r] = new char[colSize];
        }
        // new failed
        catch(std::bad_alloc&)
        {
          // clean up so-far successful allocation
          for (int i = r - 1; i >= 0; --i)
            delete[] board[i];
          delete[] board;
          throw std::exception();
        }
      }
      // all allocations have been successful: the board is now ready for data
    }
    // new failed
    else
      throw std::exception();
  }
  // board is potentially pointing at existing data (or else to garbage address)
  else
    throw std::exception(); 
}

/*****************************************************************************
Description: Deallocates the board and resets sizes to 0.
*****************************************************************************/
void Board::ClearBoard()
{
  if (board != nullptr)
  {
    // delete each row
    for (int r = 0; r < rowSize; ++r)
      delete [] board[r];
    // delete the pointers to the rows
    delete [] board;
    // reset data to empty state
    board = nullptr;
    rowSize = 0;
    colSize = 0;
  }
}

/*****************************************************************************
Description: Sends board to output stream.
      Input: - os  = output stream
             - obj = board to write to output stream 
     Output: Returns the modified output stream.
*****************************************************************************/
std::ostream& operator<<(std::ostream& os, Board const& obj)
{
  for (int r = 0; r < obj.rowSize; ++r)
  {
    for (int c = 0; c < obj.colSize; ++c)
      os << obj.board[r][c] << " ";
    os << std::endl;
  }
  return os;
}

/*****************************************************************************
Description: Proxy constructor
*****************************************************************************/
Board::Proxy::Proxy(char* row) : row(row) {}

/*****************************************************************************
Description: Proxy's operator [], returns the character at location: 
             row = Proxy, col = i
Assumptions: Assumes i is a valid index
      input: - i = index (column number)
     Output: Returns the character at index i (column number)
*****************************************************************************/
char Board::Proxy::operator[](int i) const
{
  return row[i];
}

/*****************************************************************************
Description: Board's operator[], returns the proxy (or row) at row = i
Assumptions: Assumes i is a valid index
      input: - i = index (row number)
     Output: Returns the proxy at index i (row number)
*****************************************************************************/
Board::Proxy Board::operator[](int i) const
{
  return Proxy(board[i]);
}
