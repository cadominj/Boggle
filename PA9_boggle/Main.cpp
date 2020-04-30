/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "EndScreen.h"       // End Screen Level
#include "MainMenu.h"        // Main Menu Level
#include "WordList.h"        // the dictionary and correctly guessed words
#include "GameState.h"       // GameState
#include "GamePlay.h"        // GamePlay Level
#include "Rules.h"           // Rules Level
#include "Settings.h"        // Settings to be modified in settings menu
#include "SettingsMenu.h"    // Settings Menu Level
#include "Utility.h"         // DEBUG

#include <cstdlib>           // srand
#include <ctime>             // time for srand
#include <iostream>          // cout, endl (debugging)
#include <SFML/Graphics.hpp> // Font, Event


/*
  The rules of boggle:
  - 4 x 4 square of pseudo randomized letters
  - (traditionally at least 2 players or more, but we should probably make it single-player)
  - goal is to get highest total points
  - player makes words from the assorment of random letters by stringing
    together a series of adjacent letters.
    (sequential letters in the player's words have to be next to each other 
    vertically, horizontally, or diagonally) 
  - (traditionally the players have a time limit for making words, we could 
    keep this or let them have as long as they choose, or have some way of 
    deciding when the game is over)
  - scoring (in general: more letters = more points)
    number of letters: 3 | 4 | 5 | 6 | 7 | 8+
    points per word:   1 | 1 | 2 | 3 | 5 | 11
    (we could change the point system)
  - multiple meanings of the same word are not counted as individual words and 
    do not earn more points ("lead" as in the verb meaning to guide is not 
    counted as a different word from "lead" as in the noun meaning the metal 
    / Pb element on the periodic table)
  - variations of spelling a word (even if it does not change the meaning) are 
    counted as individual words ("run", "runs", and "running" are different words)
  - the cube Qu is counted as 2 letters
    (could change this if the programming gets too weird; 
    we could alternatively change Qu to just be Q, since we don't have the limitation
    of using six sided dice; though it would be ideal to have a U neighbor in
    the case that a Q is placed)
*/

// currently just a test that SFML is statically linking and operating smoothly
int main()
{
///[ Initialize ]/////////////////////////////////////////////////////////////
  // Random
  srand((unsigned int)time(NULL)); // initialize rand()
  // Word Lists
#if !DEBUG
  WordList dictionary;
  dictionary.ReadFile();
#endif
  // Window
  sf::RenderWindow window(sf::VideoMode(1500, 1000), "Boggle");
  window.setFramerateLimit(60);
  // Background
  sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
  background.setFillColor(sf::Color(5, 24, 41)); // dark blue colored background
  // Font
  sf::Font font;
  font.loadFromFile("./Font/consola.ttf"); // kind of annoying that we can't just write "consola.ttf"
  // Settings
  Settings settings;
//////////////////////////////////////////////////////////////////////////////

  // game states/levels
  GameState* level = new MainMenu; //GamePlay(&dictionary, &words); // first level is the main menu
  level->Font(font);
  level->Window(window);
  level->Initialize();

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      // if user closes the window
      if (event.type == sf::Event::Closed)
        window.close();

      level->Event(event);
      level->Update();
    }

    window.clear();
    // draw background
    window.draw(background);
    // draw foreground
    level->Draw();
    window.display();

    // switch levels
    if (level->Quit())
    {
      GameState::State nextLevel = level->NextLevel();
      delete level;
      level = nullptr;
      switch (nextLevel)
      {
      case GameState::State::MainMenu:
        level = new MainMenu;
        break;
      case GameState::State::GamePlay:
#if !DEBUG
        level = new GamePlay(&dictionary);
#endif
        break;
      case GameState::State::Rules:
        level = new Rules;
        break;
      case GameState::State::SettingsMenu:
        level = new SettingsMenu(settings);
        break;
      case GameState::State::EndScreen:
        level = new EndScreen();
        break;
      default:
        window.close();
      }
      // initialize level
      if (level != nullptr)
      {
        level->Font(font);
        level->Window(window);
        level->Initialize();
      }
    }
  }
  return 0;
}