/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Board.h"    // Board for TestBoard
#include "Test.h"
#include "WordList.h" // WordList to test

#include <fstream>    // read from file
#include <iostream>   // cout, endl
#include <iomanip>    // setw
#include <string>     // string for filename

using std::cout;
using std::endl;

namespace
{
  /* Test Board
   *  P A I N
   *  E B L G
   *  C O D E
   *  H S S R
   */
  class TestBoard : public Board
  {
  public:
    TestBoard() : Board()
    {
      char const cStr[] = "PAINEBLGCODEHSSR";
      for (int r = 0; r < rowSize; ++r)
        for (int c = 0; c < colSize; ++c)
          board[r][c] = cStr[r * colSize + c];
    }
    char GetChar(int r, int c)
    {
      char const cStr[] = "PAINEBLGCODEHSSR";
      return cStr[r * colSize + c];
    }
  };

  void PrintResult(std::string const& str, bool success)
  {
    int const w = 60;
    cout << std::setfill('.') << std::left << std::setw(w) << str 
      << (success ? "SUCCESS" : "FAIL") << endl 
      << std::setfill(' ') <<std::right;
  }
}

void Test::Board::IndexOperator()
{
  TestBoard board;
  int row = board.RowSize(), col = board.ColSize();
  bool success = true;
  for (int r = 0; r < row; ++r)
    for (int c = 0; c < col; ++c)
      if (board[r][c] != board.GetChar(r, c)) success = false;
  PrintResult("Index Operator", success);
}

// uses index operator to test
void Test::Board::Randomize()
{
  TestBoard board;
  int row = board.RowSize(), col = board.ColSize();
  // test that known board becomes scrambled
  board.Randomize();
  
  bool success = false;
  for (int r = 0; r < row; ++r)
    for (int c = 0; c < col; ++c)
      if (board[r][c] != board.GetChar(r,c)) success = true;
  PrintResult("Randomize", success);
}

void Test::Board::IsValidWord()
{
  TestBoard board;
  // test empty word
  PrintResult("IsValidWord: Testing Empty Word", !board.IsValidWord(""));
  // test good words
  {
    bool success = true;
    // Test known good words (more realistic case)
    if (!board.IsValidWord("in")) success = false;
    if (!board.IsValidWord("lab")) success = false;
    if (!board.IsValidWord("lap")) success = false;
    if (!board.IsValidWord("bald")) success = false;
    if (!board.IsValidWord("sold")) success = false;
    if (!board.IsValidWord("hole")) success = false;
    if (!board.IsValidWord("bale")) success = false;
    if (!board.IsValidWord("pail")) success = false;
    if (!board.IsValidWord("pale")) success = false;
    if (!board.IsValidWord("codes")) success = false;
    if (!board.IsValidWord("coder")) success = false;
    if (!board.IsValidWord("gloss")) success = false;
    if (!board.IsValidWord("chose")) success = false;
    if (!board.IsValidWord("loser")) success = false;
    if (!board.IsValidWord("ebola")) success = false;
    if (!board.IsValidWord("bling")) success = false;
    if (!board.IsValidWord("holder")) success = false;
    if (!board.IsValidWord("colder")) success = false;
    if (!board.IsValidWord("bolder")) success = false;
    if (!board.IsValidWord("pealed")) success = false;
    if (!board.IsValidWord("resold")) success = false;
    if (!board.IsValidWord("pealing")) success = false;
    if (!board.IsValidWord("pealers")) success = false;
    if (!board.IsValidWord("glossed")) success = false;
    
    // Testing non words (since this just checks connectivity & not if a word)
    // Singles
    if (!board.IsValidWord("p")) success = false;
    if (!board.IsValidWord("a")) success = false;
    if (!board.IsValidWord("i")) success = false;
    if (!board.IsValidWord("n")) success = false;
    if (!board.IsValidWord("b")) success = false;
    if (!board.IsValidWord("l")) success = false;
    if (!board.IsValidWord("g")) success = false;
    if (!board.IsValidWord("c")) success = false;
    if (!board.IsValidWord("o")) success = false;
    if (!board.IsValidWord("d")) success = false;
    if (!board.IsValidWord("e")) success = false;
    if (!board.IsValidWord("h")) success = false;
    if (!board.IsValidWord("s")) success = false;
    if (!board.IsValidWord("r")) success = false;
    // Horizontals
    if (!board.IsValidWord("pain")) success = false;
    if (!board.IsValidWord("eblg")) success = false;
    if (!board.IsValidWord("code")) success = false;
    if (!board.IsValidWord("hssr")) success = false;
    if (!board.IsValidWord("niap")) success = false;
    if (!board.IsValidWord("glbe")) success = false;
    if (!board.IsValidWord("edoc")) success = false;
    if (!board.IsValidWord("rssh")) success = false;
    // Verticals
    if (!board.IsValidWord("pech")) success = false;
    if (!board.IsValidWord("abos")) success = false;
    if (!board.IsValidWord("ilds")) success = false;
    if (!board.IsValidWord("nger")) success = false;
    if (!board.IsValidWord("regn")) success = false;
    if (!board.IsValidWord("sdli")) success = false;
    if (!board.IsValidWord("soba")) success = false;
    if (!board.IsValidWord("hcep")) success = false;
    // Diagonals
    if (!board.IsValidWord("p")) success = false;
    if (!board.IsValidWord("ea")) success = false;
    if (!board.IsValidWord("cbi")) success = false;
    if (!board.IsValidWord("holn")) success = false;
    if (!board.IsValidWord("sdg")) success = false;
    if (!board.IsValidWord("se")) success = false;
    if (!board.IsValidWord("r")) success = false;
    if (!board.IsValidWord("es")) success = false;
    if (!board.IsValidWord("gds")) success = false;
    if (!board.IsValidWord("nloh")) success = false;
    if (!board.IsValidWord("ibc")) success = false;
    if (!board.IsValidWord("ae")) success = false;
    // Combination ... something here is failing
    if (!board.IsValidWord("painglbecoderssh")) success = false;
    if (!board.IsValidWord("hssredoceblgniap")) success = false;
    if (!board.IsValidWord("pechsobaildsregn")) success = false;
    if (!board.IsValidWord("ngersdliaboshcep")) success = false;
    // Print the results
    PrintResult("IsValidWord: Testing Known Good Words", success);
  }
  // test bad words
  {
    bool success = true;
    // Test known bad words (real words: more realistic case)
    if (board.IsValidWord("softly")) success = false;
    if (board.IsValidWord("painful")) success = false;
    if (board.IsValidWord("clearly")) success = false;
    if (board.IsValidWord("shoulder")) success = false;
    // Bad words with all letters on the board (real words: more realistic case)
    if (board.IsValidWord("cash")) success = false;
    if (board.IsValidWord("boil")) success = false;
    if (board.IsValidWord("pare")) success = false;
    if (board.IsValidWord("lingo")) success = false;
    if (board.IsValidWord("peach")) success = false;
    if (board.IsValidWord("despair")) success = false;

    // Testing non words (since this just checks connectivity & not if a word)
    // Contain letters not on the board
    if (board.IsValidWord("t")) success = false;
    if (board.IsValidWord("f")) success = false;
    if (board.IsValidWord("m")) success = false;
    if (board.IsValidWord("y")) success = false;
    if (board.IsValidWord("q")) success = false;
    if (board.IsValidWord("bits")) success = false;
    if (board.IsValidWord("mites")) success = false;
    if (board.IsValidWord("squishy")) success = false;
    if (board.IsValidWord("abcdefghijklmnopqrstuvwxyz")) success = false;

    // All letters on the board, but disconnected
    if (board.IsValidWord("ocsr")) success = false;
    if (board.IsValidWord("ssai")) success = false;
    if (board.IsValidWord("peer")) success = false;
    if (board.IsValidWord("cache")) success = false;
    if (board.IsValidWord("regen")) success = false;
    if (board.IsValidWord("ceping")) success = false;
    if (board.IsValidWord("pechilds")) success = false;
    if (board.IsValidWord("codehssr")) success = false;

    // Print the results
    PrintResult("IsValidWord: Testing Known Bad Words", success);
  }
}

void Test::Board::Duplicates()
{
  TestBoard board; // duplicates are allowed/on by default
  // duplicates on, these should work
  {
    bool success = true;
    // turn duplicates on (on by default, but for assurance)
    board.Duplicates(true);
    // Test Real Words (more realistic case)
    if (!board.IsValidWord("coded")) success = false;
    if (!board.IsValidWord("losers")) success = false;
    // Test Non Real Words
    if (!board.IsValidWord("ingln")) success = false;
    if (!board.IsValidWord("painiap")) success = false;
    if (!board.IsValidWord("pbdregerdbp")) success = false;
    PrintResult("Duplicates: Testing Duplicates Allowed", success);
  }
 
  // duplicates off, these should not work
  {
    bool success = true;
    // turn duplicates off
    board.Duplicates(false);
    // Test Real Words (more realistic case)
    if (board.IsValidWord("coded")) success = false;
    if (board.IsValidWord("losers")) success = false;
    // Test Non Real Words
    if (board.IsValidWord("ingln")) success = false;
    if (board.IsValidWord("painiap")) success = false;
    if (board.IsValidWord("pbdregerdbp")) success = false;
    PrintResult("Duplicates: Testing Duplicates Disallowed", success);
  }

}

void Test::Board::All()
{
  cout << "/// TESTING BOARD ///\n";
  Test::Board::IndexOperator();
  Test::Board::Randomize();
  Test::Board::IsValidWord();
  Test::Board::Duplicates();
}

// relies on insert
void Test::WordList::Empty()
{
  ::WordList wordlist;
  PrintResult("Empty: Is Empty", wordlist.Empty());
  wordlist.Insert("A");
  PrintResult("Empty: Is Not Empty", !wordlist.Empty());
}

void Test::WordList::Find()
{
  ::WordList wordlist;
  // Find all letters in alphabet word list
  {
    bool success = true;
    for (int i = 'A'; i <= 'Z'; ++i)
      wordlist.Insert(std::to_string((char)i));
    for (int i = 'A'; i <= 'Z'; ++i)
      if (!wordlist.Find(std::to_string((char)i))) success = false;
    PrintResult("Find: Test Finding All Letters in Alphabet Word List", success);
  }
  // Find all inserted strings
  {
    bool success = true;
    char const * str[] =
    {
      "muledeer","white tailed deer","chicken","salamander","duck","dog","wolf",
      "fox","bear","mountain lion","puma","cougar","panther","leopard","snail",
      "slug","snake","lizard","turtle"
    };
    int size = sizeof(str) / sizeof(*str);
    for (int i = 0; i < size; ++i)
      wordlist.Insert(str[i]);
    for (int i = 0; i < size; ++i)
      if (!wordlist.Find(str[i])) success = false;
    PrintResult("Find: Test Finding All Strings In Small Word List", success);
  }
}

// insert is just a wrapper for the stl's insert, so it may not be neccessary to test
void Test::WordList::Insert()
{
  ::WordList wordlist;
  wordlist.Insert("frogs");
  PrintResult("Insert: Testing One Element", !wordlist.Empty());
  wordlist.Insert("frogs");
  wordlist.Remove("frogs");
  PrintResult("Insert: Does Not Insert Duplicate Elements", wordlist.Empty());
}

// remove is just a wrapper for the stl's remove, so it may not be neccessary to test
void Test::WordList::Remove()
{
  ::WordList wordlist;
  wordlist.Insert("frogs");
  wordlist.Insert("dogs");
  wordlist.Insert("apples");
  wordlist.Insert("ankles");
  wordlist.Remove("frogs");
  wordlist.Remove("dogs");
  wordlist.Remove("apples");
  wordlist.Remove("ankles");
  PrintResult("Remove", wordlist.Empty());
}

// this test may act out depending on how the files are organized
// would take too long to reread in the giant dictionary file
void Test::WordList::ReadFile()
{
  std::string filename("Settings.h"); // small file to test with
  std::ifstream file(filename);
  if (file.is_open())
  {
    ::WordList wordlist(filename);
    PrintResult("ReadFile: Inserted from File", !wordlist.Empty());
    bool success = true;

    // read file line by line & use Find to check that each line exists in wordlist
    std::string line;
    while (success && std::getline(file, line))
      if (!wordlist.Find(line)) success = false;
    PrintResult("ReadFile: Inserted Each Line From File As A Word", success);
    file.close();
  }
  else
    cout << "ReadFile: Error: Could Not Open " << filename << " For Read\n";
}

void Test::WordList::FindLongestWord()
{
  ::WordList wordlist;
  char const* str[] =
  {
    "muledeer","white tailed deer","chicken","salamander","duck","dog","wolf",
    "fox","bear","mountain lion","puma","cougar","panther","leopard","snail",
    "slug","snake","lizard","turtle"
  };
  int size = sizeof(str) / sizeof(*str);
  for (int i = 0; i < size; ++i)
    wordlist.Insert(str[i]);
  PrintResult("FindLongestWord", ("white tailed deer" == wordlist.FindLongestWord()));
}


void Test::WordList::All()
{
  cout << "/// TESTING WORD LIST ///\n";
  Test::WordList::Empty();
  Test::WordList::Find();
  Test::WordList::Insert();
  Test::WordList::Remove();
  Test::WordList::ReadFile();
  Test::WordList::FindLongestWord();
}

void Test::All()
{
  cout << "/// TESTING ALL ///\n";
  Test::Board::All();
  Test::WordList::All();
}