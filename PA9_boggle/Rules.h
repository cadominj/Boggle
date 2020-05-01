/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef RULES_H
#define RULES_H

#include "GameState.h"

class Rules : public GameState
{
  std::vector<sf::Text> rulesTxt;
public:
  Rules();
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !RULES_H
