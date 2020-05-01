/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Button.h"          // button
#include "EndScreen.h"
#include <SFML/Graphics.hpp> // text, window
#include <string>            // string

namespace
{
  float const offsetY = 100.0f;
  sf::Text titleTxt, scoreTxt, longestWordTxt;
  Button returnBtn;
}

EndScreen::EndScreen(Stats& stats) : stats(stats) {}

void EndScreen::Initialize()
{
  titleTxt = sf::Text("RESULTS",font,45);
  std::string str = "Score: ";
  str += std::to_string(stats.score);
  scoreTxt = sf::Text(str, font);
  str = "Longest Word: ";
  str += stats.longestWord;
  longestWordTxt = sf::Text(str, font);

  returnBtn.SetButton("RETURN", font, 30, sf::Color::White, sf::Color::Transparent, sf::Color::White, 2.0f);
  returnBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  float midX = window->getSize().x / 2;

  // Find longest string of the middle strings
  float maxSize = 0, size;
  if ((size = scoreTxt.getGlobalBounds().width) > maxSize) maxSize = size;
  if ((size = longestWordTxt.getGlobalBounds().width) > maxSize) maxSize = size;

  titleTxt.setPosition(midX - titleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - titleTxt.getGlobalBounds().height / 2);
  scoreTxt.setPosition(midX - maxSize / 2, window->getSize().y / 3.0f);
  longestWordTxt.setPosition(midX - maxSize / 2, scoreTxt.getPosition().y + offsetY);
  returnBtn.Position({ midX - returnBtn.GetGlobalBounds().width / 2.0f, window->getSize().y - window->getSize().y / 6.0f });
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

  // if clicked, return to main menu
  if (returnBtn.IsMouseOver(*window) && event->type == sf::Event::MouseButtonReleased)
  {
    nextLevel = State::MainMenu;
    quit = true;
  }
}

void EndScreen::Draw()
{
  window->draw(titleTxt);
  window->draw(scoreTxt);
  window->draw(longestWordTxt);
  returnBtn.DrawTo(*window);
}
