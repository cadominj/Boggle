/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/

#include "Board.h"           // 4 x 4 randomized board
#include "Button.h"          // return button
#include "GamePlay.h"        // GamePlay Level
#include "Settings.h"        // settings struct 
#include "Stats.h"           // stats struct
#include "WordList.h"        // the dictionary and correctly guessed words

#include <iostream>          // cout, endl (debugging)
#include <SFML/Graphics.hpp> // text, window
#include <string>            // strings for parsing & saving words
#include <sstream>           // stringstream for parsing multi-word lines

namespace
{
  // Button
  int const btnTextSize = 30;
  float const btnOutlineWidth = 2.0f;
  // Text
  int const characterLimit = 100; // prevent text scrolling out of screen
  float midX;                     // midpoint of the screen (horizontal)
  // text Y positions
  float inputTxtPosY, scoreTxtPosY, updateTxtPosY; 
  int boardSize;
  sf::RectangleShape boardOutline;
  Button returnBtn;
}

GamePlay::GamePlay(WordList& dictionary, Settings& settings, Stats& stats) 
  : score(0), dictionary(dictionary), settings(settings), stats(stats), 
    boardTxt(nullptr), boardSquares(nullptr), words(WordList()), board(Board())
{
  boardSize = board.ColSize() * board.RowSize();
  boardTxt = new sf::Text[boardSize];
  boardSquares = new sf::RectangleShape[boardSize];
}

GamePlay::~GamePlay()
{
  // save statistics 
  stats.score = score;
  stats.longestWord = words.FindLongestWord();

  if (boardTxt)
    delete[] boardTxt;
  if (boardSquares)
    delete[] boardSquares;
}

void GamePlay::Initialize()
{
  float const outlineWidth = 2.0f;

  // Init Board
  board.Randomize();
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
  inputTxt.setFillColor(sf::Color::Green);

  // Init Return Button
  returnBtn.SetButton("RETURN", font, btnTextSize, sf::Color::White, sf::Color::Transparent, sf::Color::White, btnOutlineWidth);
  returnBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  // Text positioning
  midX = window->getSize().x / 2;
  inputTxtPosY = window->getSize().y - window->getSize().y / 3; // 2/3 down the screen
  scoreTxtPosY = window->getSize().y / 6 - scoreTxt.getGlobalBounds().height / 2;
  updateTxtPosY = scoreTxtPosY + window->getSize().y / 10;

  scoreTxt.setPosition(midX - scoreTxt.getGlobalBounds().width / 2, scoreTxtPosY);
  updateTxt.setPosition(midX - updateTxt.getGlobalBounds().width / 2, updateTxtPosY);

  // Return Button position
  returnBtn.Position({ midX - returnBtn.GetGlobalBounds().width / 2.0f, window->getSize().y - window->getSize().y / 6.0f });

  // Init Board Text
  for (int i = 0; i < boardSize; ++i)
  {
    boardTxt[i].setString(board[i / board.ColSize()][i % board.ColSize()]);
    boardTxt[i].setFont(font);
    boardTxt[i].setCharacterSize(60);
  }
  
  // Position Board Txt & Board Squares
  float letterDim = boardTxt[0].getGlobalBounds().height > boardTxt[0].getGlobalBounds().width ? boardTxt[0].getGlobalBounds().height : boardTxt[0].getLocalBounds().width;
  float offsetY = -boardTxt[0].getLocalBounds().top;
  float offsetX = (boardTxt[0].getGlobalBounds().height - boardTxt[0].getLocalBounds().width) / 2.0f;
  if (offsetX < 0) offsetX = -offsetX;
  offsetX -= boardTxt[0].getLocalBounds().left;
  float padding = 5.0, spacing = 10.0;
  float padDim = letterDim + 2 * padding;
  float gridDim = padDim + 2 * spacing;
  sf::Vector2f boxDim = { board.ColSize() * gridDim, board.RowSize() * gridDim };
  sf::Vector2f pos = { midX - boxDim.x / 2, window->getSize().y / 3.0f };

  for (int i = 0; i < boardSize; ++i)
  {
    // Text Position
    boardTxt[i].setPosition({ pos.x + i % board.ColSize() * gridDim + spacing + padding + offsetX, pos.y + i / board.ColSize() * gridDim + spacing + padding + offsetY });
    // Board Square Position + Formatting
    boardSquares[i].setPosition({boardTxt[i].getPosition().x - offsetX - padding, boardTxt[i].getPosition().y - offsetY - padding});
    boardSquares[i].setFillColor(sf::Color(5, 24, 41));
    boardSquares[i].setSize({ padDim, padDim });
    boardSquares[i].setOutlineThickness(outlineWidth / 2);
    boardSquares[i].setOutlineColor(sf::Color(255,255,255,100));
  }
  // Board Outline
  ::boardOutline.setPosition(pos);
  ::boardOutline.setSize(boxDim);
  ::boardOutline.setOutlineThickness(outlineWidth);
  ::boardOutline.setFillColor(sf::Color::Black);
}

void GamePlay::Update()
{
  if (event->type == sf::Event::KeyReleased)
  {
    // Escape Key: exit back to main menu
    if (event->key.code == sf::Keyboard::Escape)
    {
      nextLevel = State::EndScreen;
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
          str = "SCORE: ";
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
  // if click return, go back to main menu
  if (returnBtn.IsMouseOver(*window) && event->type == sf::Event::MouseButtonReleased)
  {
    nextLevel = State::EndScreen;
    quit = true;
  }
}

void GamePlay::Draw()
{
  // Draw Board
  window->draw(::boardOutline);
  for (int i = 0; i < boardSize; ++i)
  {
    window->draw(boardSquares[i]);
    window->draw(boardTxt[i]);
  }
  // Draw Text
  returnBtn.DrawTo(*window);
  window->draw(updateTxt);
  window->draw(scoreTxt);
  window->draw(inputTxt);
}

GamePlay::Validity GamePlay::IsValid(std::string const& word)
{
  Validity valid = Validity::NOT_VALID;
  if (dictionary.Find(word))
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
  int lineScore = 0;                    // total score of the line
  Validity valid = Validity::NOT_VALID; // validity of the last word (for more interesting feedback)
  std::stringstream ss;                 // string stream paser (for multiple words)
  std::string word;                     // singular word to inspect
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
    std::cout
      << "\n/// UPDATED WORD LIST ///\n"
      << words
      << "/////////////////////////\n";
  ////////////////////////////////// DEBUG
  switch (valid)
  {
  case Validity::VALID:
    break;
  case Validity::NOT_WORD:
    word += " is not a word";
    updateTxt.setString(word);
    break;
  case Validity::DUPLICATE:
    word += " has already been used";
    updateTxt.setString(word);
    break;
  case Validity::NOT_VALID_ON_BOARD:
    word += " is not available on the board";
    updateTxt.setString(word);
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
