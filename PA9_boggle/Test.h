/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef TEST_H
#define TEST_H

// Test Functions that print SUCCESS or FAIL to console
namespace Test
{
  namespace Board
  {
    void IndexOperator();
    void Randomize();
    void IsValidWord();
    void Duplicates();
    void All(); // run all Board tests
  }

  namespace WordList
  {
    void Empty();
    void Find();
    void Insert();
    void Remove();
    void ReadFile();
    void FindLongestWord();
    void All(); // run all WordList tests
  }

  void All(); // run all tests
}

#endif // !TEST_H
