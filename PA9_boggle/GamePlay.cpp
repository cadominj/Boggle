/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/

#include "Board.h"           // 4 x 4 randomized board
#include "GamePlay.h"        // GamePlay Level
#include "WordList.h"        // the dictionary and correctly guessed words

#include <iostream>          // cout, endl (debugging)
#include <SFML/Graphics.hpp> // text, window
#include <string>            // strings for parsing & saving words
#include <sstream>           // stringstream for parsing multi-word lines

namespace
{
  void GetWord(WordList& dictionary, WordList& words, Board& board, std::string const& line)
  {
    bool changed = false; // at least 1 new word
    std::stringstream ss;
    std::string word;
    ss << line;
    while (ss >> word)
    {
      if (dictionary.Find(word))
      {
        std::cout << word << " is a word";
        if (!words.Find(word))
        {
          if (board.IsValidWord(word))
          {
            changed = true;
            std::cout << "\n";
            words.Insert(word);
          }
          else
            std::cout << " but is not valid on the board\n";
        }
        else
          std::cout << " but has already been used\n";
      }
      else
        std::cout << word << " is NOT a word\n";
    }
    if (changed)
      std::cout << "\n/// UPDATED WORD LIST ///\n"
      << words
      << "/////////////////////////\n";

    std::cout << board; ////////////////////////////////// DEBUG

  }
}

GamePlay::GamePlay(WordList* dictionary, WordList* words) : dictionary(dictionary), words(words), board(Board()) {}

void GamePlay::Initialize()
{
  // Init Board
  board.Randomize();
  std::cout << board; //////////////////////DEBUG
  // Init Text
  inputWord.setFont(font);
  inputWord.setCharacterSize(18); // pixels
  inputWord.setFillColor(sf::Color(222, 152, 13)); // bright orange text
}

void GamePlay::Update()
{
  if (event->type == sf::Event::KeyReleased)
  {
    // Escape Key: exit back to main menu
    if (event->key.code == sf::Keyboard::Escape)
    {
      nextLevel = State::MainMenu;
      quit = true;
    }
    // Enter: try to input text into the player's word list
    else if (event->key.code == sf::Keyboard::Enter)
    {
      if (!inputStr.isEmpty())
      {
        GetWord(*dictionary, *words, board, inputStr);
        inputStr.clear();
        inputWord.setString(inputStr);
      }
    }
  }
  if (event->type == sf::Event::TextEntered)
  {
    // ignore tab and enter
    //if (event.text.unicode == 9 || event.text.unicode == 11 || event.text.unicode == 13) {}
    // Backspace: erase the last character
    if (event->text.unicode == 8) //'\b'
    {
      if (!inputStr.isEmpty())
      {
        inputStr.erase(inputStr.getSize() - 1, 1);
        inputWord.setString(inputStr);
      }
    }
    // Other Characters: concat to the current word 
    else
    {
      inputStr += event->text.unicode;
      inputWord.setString(inputStr);
    }
  }
}

void GamePlay::Draw()
{
  window->draw(inputWord);
}
