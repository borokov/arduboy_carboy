#ifndef GAME_DRAWER_H
#define GAME_DRAWER_H

#include "Arduboy.h"
#include "GameState.h"

class GameDrawer
{
public:
  GameDrawer();

  void draw(Arduboy& arduboy, GameState& gameState);
  
private:
  void drawSpeed(Arduboy& arduboy, GameState& gameState);
  void drawTrack(Arduboy& arduboy, GameState& gameState);
  void drawOpponent(Arduboy& arduboy, GameState& gameState);
  void drawMyCar(Arduboy& arduboy,GameState& gameState);

  void drawCar(Arduboy& arduboy, char line, int8_t position, GameState& gameState);

  Arduboy& m_arduboy;
  GameState& m_gameState;
};

#endif
