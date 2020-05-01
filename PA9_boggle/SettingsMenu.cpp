/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Button.h"          // button
#include "SettingsMenu.h"
#include "Test.h"            // run the tests in console

#include <SFML/Graphics.hpp> // Text


namespace
{
  //float const offsetY = 100.0f;
  int const btnTextSize = 30;
  float const btnOutlineWidth = 2.0f;

  sf::Text titleTxt;
  Button returnBtn, runTestsBtn;
}

SettingsMenu::SettingsMenu(Settings& settings) : settings(settings) {}

void SettingsMenu::Initialize()
{
  titleTxt = sf::Text("SETTINGS", font, 45);

  runTestsBtn.SetButton("RUN TESTS", font, btnTextSize, sf::Color::White, sf::Color::Transparent, sf::Color::White, btnOutlineWidth);
  runTestsBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  returnBtn.SetButton("RETURN", font, btnTextSize, sf::Color::White, sf::Color::Transparent, sf::Color::White, btnOutlineWidth);
  returnBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  float midX = window->getSize().x / 2;
  titleTxt.setPosition(midX - titleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - titleTxt.getGlobalBounds().height / 2);
  runTestsBtn.Position({ midX - runTestsBtn.GetGlobalBounds().width / 2.0f, window->getSize().y / 3.0f });
  returnBtn.Position({ midX - returnBtn.GetGlobalBounds().width / 2.0f, window->getSize().y - window->getSize().y / 6.0f });
}

void SettingsMenu::Update()
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

  // if click run tests, run all tests (they print to console)
  if (runTestsBtn.IsMouseOver(*window) && event->type == sf::Event::MouseButtonReleased)
    Test::All();
  // if click return, go back to main menu
  if (returnBtn.IsMouseOver(*window) && event->type == sf::Event::MouseButtonReleased)
  {
    nextLevel = State::MainMenu;
    quit = true;
  }
}

void SettingsMenu::Draw()
{
  window->draw(titleTxt);
  runTestsBtn.DrawTo(*window);
  returnBtn.DrawTo(*window);
}
