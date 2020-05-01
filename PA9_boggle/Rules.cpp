/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Button.h"          // button
#include "Rules.h"
#include <SFML/Graphics.hpp> // Text
#include <vector>            // vector for rulesTxt

namespace
{
  int const btnTextSize = 30, const rulesSize = 20;
  float const btnOutlineWidth = 2.0f;
  sf::Text titleTxt, returnTxt;
  Button returnBtn;
}

Rules::Rules(): rulesTxt(std::vector<sf::Text>()){}

void Rules::Initialize()
{
  titleTxt = sf::Text("RULES", font, 45);

  returnBtn.SetButton("RETURN", font, btnTextSize, sf::Color::White, sf::Color::Transparent, sf::Color::White, btnOutlineWidth);
  returnBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  // Initializing the Rules
  rulesTxt.push_back(sf::Text("- The board is a 4 x 4 square of pseudo randomized letters.", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- The goal is to get the highest score possible.", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- The game is played until the player decides to end it (either by clicking EXIT or pressing the escape key).", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Make words from the assortment of random letters by stringing together a series of adjacent letters.", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Multiple words and be put on one line if separated by spaces.", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Send typed words in to be scored by pressing the enter/return key.", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Scoring varies a bit from traditional Boggle.", font, rulesSize));
  rulesTxt.push_back(sf::Text("  Here, the score for the word = number of letters in word + bonus for longer words.", font, rulesSize));
  rulesTxt.push_back(sf::Text("  number of letters: 3 | 4 | 5 | 6 | 7 | 8+", font, rulesSize));
  rulesTxt.push_back(sf::Text("  bonus per word:    1 | 1 | 2 | 3 | 5 | 11", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Multiple meanings of the same word are not counted as individual words and do not earn more points.", font, rulesSize));
  rulesTxt.push_back(sf::Text("  \"lead\" (to guide) is considered the same as \"lead\" (Pb element on the periodic table).", font, rulesSize));
  rulesTxt.push_back(sf::Text("", font, rulesSize));
  rulesTxt.push_back(sf::Text("- Variations of spelling a word, even if it does not change the meaning, are counted as individual words.", font, rulesSize));
  rulesTxt.push_back(sf::Text("  \"run\", \"runs\", and \"running\" are considered different words.", font, rulesSize));
  rulesTxt.push_back(sf::Text("  \"color\" and \"colour\" are considered different words.", font, rulesSize));




  // Positioning
  float midX = window->getSize().x / 2;
  titleTxt.setPosition(midX - titleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - titleTxt.getGlobalBounds().height / 2);
  returnBtn.Position({ midX - returnBtn.GetGlobalBounds().width / 2.0f, window->getSize().y - window->getSize().y / 6.0f });

  float offsetY = rulesTxt[0].getGlobalBounds().height;
  float maxSize = 100.0f * rulesTxt[0].getGlobalBounds().width / rulesTxt[0].getString().getSize();
  sf::Vector2f pos({ midX - maxSize / 2, window->getSize().y / 3.0f }); // starting position
  int i = 0;
  for (std::vector<sf::Text>::iterator it = rulesTxt.begin(); it != rulesTxt.end(); ++it)
    it->setPosition(pos.x, pos.y + offsetY * i++ );
}

void Rules::Update()
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
  // if click return, go back to main menu
  if (returnBtn.IsMouseOver(*window) && event->type == sf::Event::MouseButtonReleased)
  {
    nextLevel = State::MainMenu;
    quit = true;
  }

}

void Rules::Draw()
{
  window->draw(titleTxt);
  returnBtn.DrawTo(*window);
  for (std::vector<sf::Text>::iterator it = rulesTxt.begin(); it != rulesTxt.end(); ++it)
    window->draw(*it);
}

