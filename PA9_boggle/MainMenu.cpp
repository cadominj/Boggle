/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "MainMenu.h"
#include <SFML/Graphics.hpp>

namespace
{
  sf::Text PlayTxt, RulesTxt, SettingsTxt, QuitTxt;
  sf::RectangleShape PlayBox, RulesBox, SettingsBox, QuitBox;
}

void MainMenu::Initialize()
{
  // Text
  int const vOffset = 100; // vertical offset

  PlayTxt.setString("Play");
  PlayTxt.setFont(font);
  PlayTxt.setPosition(window->getSize().x / 3, 100);
  PlayTxt.setFillColor(sf::Color::White);
  RulesTxt.setString("Rules");
  RulesTxt.setFont(font);
  RulesTxt.setPosition(PlayTxt.getPosition().x, PlayTxt.getPosition().y + vOffset);
  RulesTxt.setFillColor(sf::Color::White);
  SettingsTxt.setString("Settings");
  SettingsTxt.setFont(font);
  SettingsTxt.setPosition(PlayTxt.getPosition().x, RulesTxt.getPosition().y + vOffset);
  SettingsTxt.setFillColor(sf::Color::White);
  QuitTxt.setString("Quit");
  QuitTxt.setFont(font);
  QuitTxt.setPosition(PlayTxt.getPosition().x, SettingsTxt.getPosition().y + vOffset);
  QuitTxt.setFillColor(sf::Color::White);

  // Text Boxes / Bubbles
  float outlineSize = 2.0f;

  PlayBox.setOutlineColor(sf::Color::White);
  RulesBox.setOutlineColor(sf::Color::White);
  SettingsBox.setOutlineColor(sf::Color::White);
  QuitBox.setOutlineColor(sf::Color::White);
  
  PlayBox.setOutlineThickness(outlineSize);
  RulesBox.setOutlineThickness(outlineSize);
  SettingsBox.setOutlineThickness(outlineSize);
  QuitBox.setOutlineThickness(outlineSize);

  
}

void MainMenu::Update()
{
  if (event->type == sf::Event::KeyReleased)
  {
    // Escape Key: exit out of application
    if (event->key.code == sf::Keyboard::Escape)
    {
      nextLevel = State::Exit;
      quit = true;
    }
  }
  // if user clicks on any button, set the next pointer, & set quit to true for that option
  // if user clicks exit, just set quit to true
}

void MainMenu::Draw()
{
  // Text Boxes / Bubbles
  window->draw(PlayBox);
  window->draw(RulesBox);
  window->draw(SettingsBox);
  window->draw(QuitBox);

  // Text
  window->draw(PlayTxt);
  window->draw(RulesTxt);
  window->draw(SettingsTxt);
  window->draw(QuitTxt);
}