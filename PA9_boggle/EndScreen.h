/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "GameState.h"

class EndScreen : public GameState
{
public:
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !END_SCREEN_H
