#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Arduboy.h"

class GameState
{
public:
  GameState();
  updateState(Arduboy& arduboy);
  
  unsigned char m_carSpeed;
  enum Line
  {
    LEFT,
    MIDDLE,
    RIGHT
  };
  char m_currentLine;

  bool m_leftWasPressed;
  bool m_rightWasPressed;

  uint8_t m_currentFrame;

  struct Opponent
  {
    Opponent(uint8_t playerSpeed);

    // position relative to current car. 0 is far away in fron, 127 is behind.
    int8_t position;
    char line;
    static const uint8_t speed = 15;
  };

  Opponent* opponents[4];
};

#endif
