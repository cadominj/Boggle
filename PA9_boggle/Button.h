/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp> // RectangleShape, Text

class Button
{
  // the button shape and the text on top of it
  sf::RectangleShape button;
  sf::Text text;

  // hover (will be set to regular until they are explicitly set)
  bool isHovering;
  sf::RectangleShape hover;
  sf::Text           hoverTxt;

public:
  Button(); // default ctor
  Button(std::string const& txt, int charSize, sf::Color const& textColor, 
    sf::Color const& bgColor, sf::Color const& outlineColor, float outlineWidth);

  // setters
  void SetButton(std::string const& txt, sf::Font const& font, int charSize, sf::Color const& textColor,
    sf::Color const& bgColor, sf::Color const& outlineColor, float outlineWidth);
  void SetHover(sf::Color const& txt, sf::Color const& bg, sf::Color const& outline);

  void Font(sf::Font const& font);
  void ButtonColor(sf::Color const& fill, sf::Color const& outline);
  void TextColor(sf::Color const& color);

  void Position(sf::Vector2f pos);

  // getters
  sf::FloatRect GetGlobalBounds()const;
  sf::Vector2f const& Position()const;

  void DrawTo(sf::RenderWindow& window);
  bool IsMouseOver(sf::RenderWindow& window); // sets isHovering (& returns the result)
  bool GetHover(); // gets isHovering
};

#endif