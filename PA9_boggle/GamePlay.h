/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include "Board.h"     // Board
#include "GameState.h"
#include "Settings.h"  // settings struct 
#include "Stats.h"     // stats struct
#include "WordList.h"  // for the dictionary & running word list

#include <vector>      // vector for wordsTxt


class GamePlay : public GameState
{
  enum class Validity
  {
    VALID,              // valid
    NOT_VALID,          // not valid: general case
    NOT_WORD,           // not valid: not a word (not in dictionary)
    DUPLICATE,          // not valid: duplicate (already in word list)
    NOT_VALID_ON_BOARD  // not valid: no valid placement on the board
  };

  // data
  int score;
  WordList & dictionary;
  Settings& settings;
  Stats& stats;
  sf::Text* boardTxt;
  sf::RectangleShape* boardSquares;
  WordList words;
  Board board;

  std::vector<sf::Text> wordsTxt;

  sf::String inputStr;
  sf::Text inputTxt;
  sf::Text scoreTxt;
  sf::Text updateTxt;

  // helper functions
  Validity IsValid(std::string const& word);
  int GetWords(std::string const& line);
  int GetScore(std::string const& word);
public:
  GamePlay(WordList & dictionary, Settings & settings, Stats & stats);
  ~GamePlay();
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !GAME_PLAY_H
