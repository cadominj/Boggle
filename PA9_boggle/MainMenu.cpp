/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "MainMenu.h"
#include <SFML/Graphics.hpp> // Text, RectangleShape

namespace
{
  sf::Text TitleTxt, PlayTxt, RulesTxt, SettingsTxt, QuitTxt;
  sf::RectangleShape PlayBox, RulesBox, SettingsBox, QuitBox;
  GameState::State Inside; // which button mouse is inside
}

void MainMenu::Initialize()
{
  // Text
  int const vOffset = 100;              // vertical offset
  float midX = window->getSize().x / 2; // middle of screen (horizontal)

  TitleTxt.setCharacterSize(70);

  TitleTxt.setString("BOGGLE");
  PlayTxt.setString("Play");
  RulesTxt.setString("Rules");
  SettingsTxt.setString("Settings");
  QuitTxt.setString("Quit");

  TitleTxt.setFont(font);
  PlayTxt.setFont(font);
  RulesTxt.setFont(font);
  SettingsTxt.setFont(font);
  QuitTxt.setFont(font);

  TitleTxt.setPosition(midX - TitleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - TitleTxt.getGlobalBounds().height / 2);
  PlayTxt.setPosition(midX - PlayTxt.getGlobalBounds().width / 2, window->getSize().y / 3);
  RulesTxt.setPosition(midX - RulesTxt.getGlobalBounds().width / 2, PlayTxt.getPosition().y + vOffset);
  SettingsTxt.setPosition(midX - SettingsTxt.getGlobalBounds().width / 2, RulesTxt.getPosition().y + vOffset);
  QuitTxt.setPosition(midX - QuitTxt.getGlobalBounds().width / 2, SettingsTxt.getPosition().y + vOffset);

  TitleTxt.setFillColor(sf::Color::Green);
  PlayTxt.setFillColor(sf::Color::White);
  RulesTxt.setFillColor(sf::Color::White);
  SettingsTxt.setFillColor(sf::Color::White);
  QuitTxt.setFillColor(sf::Color::White);

  // Text Boxes / Bubbles
  float outlineWidth = 2.0f;
  float padding = 10.0f;

  PlayBox.setOutlineColor(sf::Color::White);
  RulesBox.setOutlineColor(sf::Color::White);
  SettingsBox.setOutlineColor(sf::Color::White);
  QuitBox.setOutlineColor(sf::Color::White);
  
  PlayBox.setOutlineThickness(outlineWidth);
  RulesBox.setOutlineThickness(outlineWidth);
  SettingsBox.setOutlineThickness(outlineWidth);
  QuitBox.setOutlineThickness(outlineWidth);
  
  PlayBox.setSize({ PlayTxt.getGlobalBounds().width + 2 * padding, PlayTxt.getGlobalBounds().height + 2 * padding });
  RulesBox.setSize({ RulesTxt.getGlobalBounds().width + 2 * padding, RulesTxt.getGlobalBounds().height + 2 * padding });
  SettingsBox.setSize({ SettingsTxt.getGlobalBounds().width + 2 * padding, SettingsTxt.getGlobalBounds().height + 2 * padding });
  QuitBox.setSize({ QuitTxt.getGlobalBounds().width + 2 * padding, QuitTxt.getGlobalBounds().height + 2 * padding });
  
  PlayBox.setFillColor(sf::Color::Transparent);
  RulesBox.setFillColor(sf::Color::Transparent);
  SettingsBox.setFillColor(sf::Color::Transparent);
  QuitBox.setFillColor(sf::Color::Transparent);

  PlayBox.setPosition({ PlayTxt.getGlobalBounds().left - padding, PlayTxt.getGlobalBounds().top - padding });
  RulesBox.setPosition({ RulesTxt.getGlobalBounds().left - padding, RulesTxt.getGlobalBounds().top - padding });
  SettingsBox.setPosition({ SettingsTxt.getGlobalBounds().left - padding, SettingsTxt.getGlobalBounds().top - padding });
  QuitBox.setPosition({ QuitTxt.getGlobalBounds().left - padding, QuitTxt.getGlobalBounds().top - padding });

  // Mouse Position
  Inside = State::MainMenu; // not inside a button ... assuming
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
  
  float mouseX = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
  float mouseY = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;

  // if inside the bounding box of Play
  if (PlayBox.getGlobalBounds().contains(mouseX, mouseY))
  {
    if (Inside != State::GamePlay)
    {
      Inside = State::GamePlay;
      PlayBox.setFillColor(sf::Color::White);
      PlayTxt.setFillColor(sf::Color::Black);
    }
  }
  // if inside the bounding box of Rules
  else if (RulesBox.getGlobalBounds().contains(mouseX, mouseY))
  {
    if (Inside != State::Rules)
    {
      Inside = State::Rules;
      RulesBox.setFillColor(sf::Color::White);
      RulesTxt.setFillColor(sf::Color::Black);
    }
  }
  // if inside the bounding box of Settings
  else if (SettingsBox.getGlobalBounds().contains(mouseX, mouseY))
  {
    if (Inside != State::Settings)
    {
      Inside = State::Settings;
      SettingsBox.setFillColor(sf::Color::White);
      SettingsTxt.setFillColor(sf::Color::Black);
    }
    
  }
  // if inside the bounding box of Exit
  else if (QuitBox.getGlobalBounds().contains(mouseX, mouseY))
  {
    if (Inside != State::Exit)
    {
      Inside = State::Exit;
      QuitBox.setFillColor(sf::Color::White);
      QuitTxt.setFillColor(sf::Color::Black);
    }
  }
  else
  {
    if (Inside != State::MainMenu)
    {
      switch (Inside)
      {
      case State::GamePlay:
        PlayBox.setFillColor(sf::Color::Transparent);
        PlayTxt.setFillColor(sf::Color::White);
        break;
      case State::Rules:
        RulesBox.setFillColor(sf::Color::Transparent);
        RulesTxt.setFillColor(sf::Color::White);
        break;
      case State::Settings:
        SettingsBox.setFillColor(sf::Color::Transparent);
        SettingsTxt.setFillColor(sf::Color::White);
        break;
      case State::Exit:
        QuitBox.setFillColor(sf::Color::Transparent);
        QuitTxt.setFillColor(sf::Color::White);
      }
      Inside = State::MainMenu;
    }
  }

  // if user clicks on any button, set the next pointer, & set quit to true for that option
  // if user clicks exit, just set quit to true
  if (event->type == sf::Event::MouseButtonReleased)
  {
    if (Inside != State::MainMenu)
    {
      quit = true;
      nextLevel = Inside;
    }
  }
}

void MainMenu::Draw()
{
  // Text Boxes / Bubbles
  window->draw(TitleTxt);
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