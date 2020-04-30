/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
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
  int const characterLimit = 100; // prevent text scrolling out of screen
  float midX;                     // midpoint of the screen (horizontal)
  // text Y positions
  float inputTxtPosY, scoreTxtPosY, updateTxtPosY; 
}

GamePlay::GamePlay(WordList* dictionary) : score(0), dictionary(dictionary) {}

void GamePlay::Initialize()
{
  // Init Board
  board.Randomize();
  std::cout << board; //////////////////////DEBUG
  // Init Text
  scoreTxt.setString("SCORE: 0");
  updateTxt.setString("Start Typing!");

  scoreTxt.setFont(font);
  updateTxt.setFont(font);
  inputTxt.setFont(font);
  
  scoreTxt.setCharacterSize(50);
  updateTxt.setCharacterSize(15);
  inputTxt.setCharacterSize(20); // pixels

  scoreTxt.setFillColor(sf::Color::White);
  updateTxt.setFillColor(sf::Color::White);
  inputTxt.setFillColor(sf::Color(222, 152, 13)); // bright orange text

  // Text positioning
  midX = window->getSize().x / 2;
  inputTxtPosY = window->getSize().y - window->getSize().y / 3; // 2/3 down the screen
  scoreTxtPosY = window->getSize().y / 6 - scoreTxt.getGlobalBounds().height / 2;
  updateTxtPosY = scoreTxtPosY + window->getSize().y / 10;

  scoreTxt.setPosition(midX - scoreTxt.getGlobalBounds().width / 2, scoreTxtPosY);
  updateTxt.setPosition(midX - updateTxt.getGlobalBounds().width / 2, updateTxtPosY);
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
        int lineScore = 0;
        // If the score has changed
        if (lineScore = GetWords(inputStr))
        {
          score += lineScore;
          // Set update message
          std::string str = "+ ";
          str += std::to_string(lineScore);
          updateTxt.setString(str);
          // realiagn update text at center
          updateTxt.setPosition(midX - updateTxt.getGlobalBounds().width / 2, updateTxtPosY);
          // Update the score text string
          str = "Score: ";
          str += std::to_string(score);
          scoreTxt.setString(str);
          // realign score text at center
          scoreTxt.setPosition(midX - scoreTxt.getGlobalBounds().width / 2, scoreTxtPosY);
        }
        else
        {
          //updateTxt.setString("word not valid");
          updateTxt.setPosition(midX - updateTxt.getGlobalBounds().width / 2, updateTxtPosY);
        }
        inputStr.clear();
        inputTxt.setString(inputStr);
      }
    }
  }
  if (event->type == sf::Event::TextEntered)
  {
    // ignore escape, tab, and enter
    if (event->text.unicode == 27 || event->text.unicode == 9 || event->text.unicode == 11 || event->text.unicode == 13) {}
    // Backspace: erase the last character
    else if (event->text.unicode == 8) //'\b'
    {
      if (!inputStr.isEmpty())
      {
        inputStr.erase(inputStr.getSize() - 1, 1);
        inputTxt.setString(inputStr);
        inputTxt.setPosition(midX - inputTxt.getGlobalBounds().width / 2, inputTxtPosY);
      }
    }
    // Other Characters: concat to the current word 
    else if (inputStr.getSize() < characterLimit)
    {
      inputStr += event->text.unicode;
      inputTxt.setString(inputStr);
      inputTxt.setPosition(midX - inputTxt.getGlobalBounds().width / 2, inputTxtPosY);
    }
  }
}

void GamePlay::Draw()
{
  window->draw(inputTxt);
  window->draw(updateTxt);
  window->draw(scoreTxt);
}

GamePlay::Validity GamePlay::IsValid(std::string const& word)
{
  Validity valid = Validity::NOT_VALID;
  if (dictionary->Find(word))
  {
    if (!words.Find(word))
    {
      if (board.IsValidWord(word))
        valid = Validity::VALID;
      else
        valid = Validity::NOT_VALID_ON_BOARD;
    }
    else
      valid = Validity::DUPLICATE;
  }
  else
    valid = Validity::NOT_WORD;
  return valid;
}

// returns true if score changed
int GamePlay::GetWords(std::string const& line)
{
  int lineScore = 0;   // total score of the line
  Validity valid;      // validity of the last word (for more interesting feedback)
  std::stringstream ss;
  std::string word;
  ss << line;
  while (ss >> word)
  {
    if ((valid = IsValid(word)) == Validity::VALID)
    {
      lineScore += GetScore(word);
      words.Insert(word);
    }
  }
  ////////////////////////////////// DEBUG
  if (lineScore)
    std::cout << "score += " << lineScore
    << "\n/// UPDATED WORD LIST ///\n"
    << words
    << "/////////////////////////\n";
  std::cout << board; 
  ////////////////////////////////// DEBUG
  switch (valid)
  {
  case Validity::VALID:
    break;
  case Validity::NOT_WORD:
    updateTxt.setString("word not valid: not a word");
    break;
  case Validity::DUPLICATE:
    updateTxt.setString("word not valid: already used");
    break;
  case Validity::NOT_VALID_ON_BOARD:
    updateTxt.setString("word not valid: word not available on the board");
    break;
  default:
    break;
  }
  return lineScore; // false if linescore is 0, true otherwise
}

/*****************************************************************************
Description: Calculate the score for the given word.
             (in general: more letters = more points)
             Here, score is the number of letters plus a bonus for longer words.
             number of letters: 3 | 4 | 5 | 6 | 7 | 8+
             bonus per word:    1 | 1 | 2 | 3 | 5 | 11
      Input: - word = word to get the score for
     Output: Returns the computed score.
*****************************************************************************/
int GamePlay::GetScore(std::string const& word)
{
  int bonus = 0; // longer words will get a bonus
  switch (word.size())
  {
  case 1:
  case 2:
    break;
  case 3:
  case 4:
    bonus = 1;
    break;
  case 5:
    bonus = 2;
    break;
  case 6:
    bonus = 3;
    break;
  case 7:
    bonus = 5;
    break;
  default: // 8+
    bonus = 11;
    break;
  }
  return word.size() + bonus;
}
