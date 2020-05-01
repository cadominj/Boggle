/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "Button.h"

namespace
{
  float const padding = 10.0f;
}

// default constructor
Button::Button() { isHovering = false; }

//Consructor
Button::Button(std::string const& txt, int charSize, sf::Color const& textColor, sf::Color const& bgColor, sf::Color const& outlineColor, float outlineWidth)
{
  // Text
  text.setString(txt);
  text.setFillColor(textColor);
  text.setCharacterSize(charSize);

  // Button
  button.setSize({ text.getGlobalBounds().width + 2 * padding, text.getGlobalBounds().height + 2 * padding });
  button.setFillColor(bgColor);
  button.setOutlineColor(outlineColor);
  button.setOutlineThickness(outlineWidth);

  // Hover
  SetHover(textColor, bgColor, outlineColor);
  isHovering = false;
}

void Button::SetButton(std::string const& txt, sf::Font const& font, int charSize, sf::Color const& textColor,
  sf::Color const& bgColor, sf::Color const& outlineColor, float outlineWidth)
{
  // Text
  text.setFont(font);
  text.setString(txt);
  text.setFillColor(textColor);
  text.setCharacterSize(charSize);

  // Button
  button.setSize({ text.getGlobalBounds().width + 2 * padding, text.getGlobalBounds().height + 2 * padding });
  button.setFillColor(bgColor);
  button.setOutlineColor(outlineColor);
  button.setOutlineThickness(outlineWidth);

  // Hover
  SetHover(textColor, bgColor, outlineColor);
  isHovering = false;
}

void Button::SetHover(sf::Color const& txt, sf::Color const& bg, sf::Color const& outline)
{
  // Colors
  hoverTxt.setFillColor(txt);
  hover.setFillColor(bg);
  hover.setOutlineColor(outline);

  // adopt other data from text
  hoverTxt.setFont(*text.getFont());
  hoverTxt.setString(text.getString());
  hoverTxt.setCharacterSize(text.getCharacterSize());

  // adopt other data from button
  hover.setSize(button.getSize());
  hover.setOutlineThickness(button.getOutlineThickness());
}

//Set the font 
void Button::Font(sf::Font const& font)
{
  text.setFont(font);
}

// Sets the background square color for the button 
void Button::ButtonColor(sf::Color const& fill, sf::Color const& outline)
{
  button.setFillColor(fill);
  button.setOutlineColor(outline);
}

// Sets the text color for the button 
void Button::TextColor(sf::Color const& color)
{
  text.setFillColor(color);
}

/***********************************************************
// Sets the position of the button and calculates          *
// where the text should be placed based on the button     *
************************************************************/
void Button::Position(sf::Vector2f pos)
{
  button.setPosition(pos);
  hover.setPosition(pos);

  //float xPos = (pos.x + button.getLocalBounds().width / 7) - (text.getLocalBounds().width / 2);
  //float yPos = (pos.y + button.getLocalBounds().height / 7) - (text.getLocalBounds().height / 2);
  //text.setPosition({ xPos, yPos });

  text.setPosition(pos.x + padding - text.getLocalBounds().left, pos.y + padding - text.getLocalBounds().top);
  hoverTxt.setPosition(text.getPosition());
}

// Allows both the button and text to be drawn to the window
//Button should be drawn before text so that text lays on top of the button 
void Button::DrawTo(sf::RenderWindow& window)
{
  if (!isHovering)
  {
    window.draw(button);
    window.draw(text);
  }
  else
  {
    window.draw(hover);
    window.draw(hoverTxt);
  }
}

// getter for the global bounds of the button (Coords)
sf::FloatRect Button::GetGlobalBounds() const
{
  return button.getGlobalBounds();
}

sf::Vector2f const& Button::Position() const
{
  return button.getPosition();
}

/***********************************************************
// Checks if the mouse is within the boundaries of the     *
// button and returns true or false.                       *
************************************************************/
bool Button::IsMouseOver(sf::RenderWindow& window)
{
  float mouseX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
  float mouseY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;
  return isHovering = button.getGlobalBounds().contains(mouseX, mouseY);
}

bool Button::GetHover()
{
  return isHovering;
}