/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include "GameState.h"

class SettingsMenu : public GameState
{
public:
  virtual void Initialize();
  virtual void Update();
  virtual void Draw();
};

#endif // !SETTINGS_H
