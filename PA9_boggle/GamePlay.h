/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include "Board.h"     // Board
#include "GameState.h"
#include "WordList.h"  // for the dictionary & running word list

class GamePlay : public GameState
{
  // data
  WordList * dictionary;
  WordList * words;
  Board board;

  sf::String inputStr;
  sf::Text inputWord;
public:
  GamePlay(WordList* dictionary, WordList* words);
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !GAME_PLAY_H
