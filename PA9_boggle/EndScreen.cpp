/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "EndScreen.h"
#include <SFML/Graphics.hpp> // text, window

namespace
{
  sf::Text titleTxt, returnTxt;
}

EndScreen::EndScreen(Stats& stats) : stats(stats) {}

void EndScreen::Initialize()
{
  titleTxt.setString("RESULTS");
  returnTxt.setString("RETURN");

  titleTxt.setFont(font);
  returnTxt.setFont(font);

  titleTxt.setCharacterSize(45);
  returnTxt.setCharacterSize(20);

  titleTxt.setFillColor(sf::Color::White);
  returnTxt.setFillColor(sf::Color::White);

  float midX = window->getSize().x / 2;

  titleTxt.setPosition(midX - titleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - titleTxt.getGlobalBounds().height / 2);
  returnTxt.setPosition(midX - returnTxt.getGlobalBounds().width / 2, window->getSize().y / 3);
}

void EndScreen::Update()
{
  if (event->type == sf::Event::KeyReleased)
  {
    // Escape Key: return to Main Menu
    if (event->key.code == sf::Keyboard::Escape)
    {
      nextLevel = State::MainMenu;
      quit = true;
    }
  }
}

void EndScreen::Draw()
{
  window->draw(titleTxt);
  window->draw(returnTxt);
}
