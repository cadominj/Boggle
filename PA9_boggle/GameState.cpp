/*****************************************************************************
    Authors: Ava Stromme, Kristen Blue, Sarah Janzen
       Date: 4/30/2020
Description: A simplistic game of boggle using SFML graphics library.
*****************************************************************************/
#include "GameState.h"

// default ctor
GameState::GameState() 
  : quit(false), dt(0.0f), nextLevel(State::Exit), font(sf::Font()), event(nullptr), window(nullptr) {}

// dtor
GameState::~GameState() {}

// getters
bool GameState::Quit()const
{ return quit; }

float GameState::DT()const 
{ return dt; }

GameState::State GameState::NextLevel()const
{ return nextLevel; }

sf::Font const& GameState::Font()const
{ return font; }

sf::Event const& GameState::Event()const
{ return *event; }

sf::RenderWindow const& GameState::Window()const
{ return *window; }

// non const getters
sf::Event* GameState::Event()
{ return event; }

sf::RenderWindow* GameState::Window()
{ return window; }

// setters
void GameState::Quit(bool quit)
{ this->quit = quit; }

void GameState::DT(float dt) 
{ this->dt = dt; }

void GameState::NextLevel(State nextLevel)
{ this->nextLevel = nextLevel; }

void GameState::Font(sf::Font const& font) 
{ this->font = font; }

void GameState::Event(sf::Event & event)
{ this->event = &event; }

void GameState::Window(sf::RenderWindow& window)
{ this->window = &window; }
