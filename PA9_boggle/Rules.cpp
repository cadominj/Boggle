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

namespace
{
  int const btnTextSize = 30;
  float const btnOutlineWidth = 2.0f;
  sf::Text titleTxt, returnTxt;
  Button returnBtn;
}

void Rules::Initialize()
{

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

  titleTxt = sf::Text("RULES", font, 45);

  returnBtn.SetButton("RETURN", font, btnTextSize, sf::Color::White, sf::Color::Transparent, sf::Color::White, btnOutlineWidth);
  returnBtn.SetHover(sf::Color::Black, sf::Color::White, sf::Color::White);

  float midX = window->getSize().x / 2;

  titleTxt.setPosition(midX - titleTxt.getGlobalBounds().width / 2, window->getSize().y / 6 - titleTxt.getGlobalBounds().height / 2);
  returnBtn.Position({ midX - returnBtn.GetGlobalBounds().width / 2.0f, window->getSize().y -  window->getSize().y / 6.0f });
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
}

