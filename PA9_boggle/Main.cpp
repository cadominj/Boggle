/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
      Class: CPT_S 122
 Assignment: PA9
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/

#include <SFML/Graphics.hpp>

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

/*
  Example:

  (create the 4 x 4 board of randomized characters)
  A  N  E  T
  P  Qu I  P
  E  B  O  V
  R  Y  S  W

  player can create words:
  BOVINE (3 points)
  SOVIET (3 points)
  QuIET  (2 points)
  QuITE  (2 points)
  QuERY  (2 points)
  PINE   (1 point)
  VINE   (1 point)
  BITE   (1 point)
  BOYS   (1 point)
  VOWS   (1 point)
  VOW    (1 point)
  BOY    (1 point)
  BOW    (1 point)
  BIT    (1 point)
  NET    (1 point)
  TIN    (1 point)
  TIE    (1 point)
  PEN    (1 point)
  SOY    (1 point)
  PAN    (1 point)
  APE    (1 point)
  ... (and so on)
*/

// currently just a test that SFML is statically linking and operating smoothly
int main()
{
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}