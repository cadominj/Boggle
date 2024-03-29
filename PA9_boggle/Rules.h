/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef RULES_H
#define RULES_H

#include "GameState.h"

class Rules : public GameState
{
public:
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !RULES_H
