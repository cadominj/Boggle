/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp> // font

class GameState
{
public:
  enum class State
  {
    Exit,
    MainMenu,
    GamePlay,
    Rules,
    SettingsMenu,
    EndScreen
  };

  GameState();
  virtual ~GameState();

  // getters
  bool Quit()const;
  float DT()const;
  State NextLevel()const;
  sf::Font const& Font()const;
  sf::Event const& Event()const;
  sf::RenderWindow const& Window()const;

  // non const getters (safer alternatives if event or window haven't been set)
  sf::Event * Event();
  sf::RenderWindow * Window();

  // setters
  void Quit(bool quit);
  void DT(float dt);
  void NextLevel(State nextLevel);
  void Font(sf::Font const& font);
  void Event(sf::Event & event);
  void Window(sf::RenderWindow & window);

  // pure virtual methods
  virtual void Initialize() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;

protected:
  // data:
  bool quit;                 // when true, move to the nextLevel
  float dt;                  // detla time
  State nextLevel;           // if nextLevel is null ptr and next level tries to load, exists program
  sf::Font font;             // game font
  sf::Event * event;         // last polled event
  sf::RenderWindow * window; // window
};

#endif // !GAME_STATE_H
