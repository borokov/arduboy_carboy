#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Arduboy.h"

struct Point8
{ 
  int8_t x;
  int8_t y;
  Point8 operator+(Point8 v) { return {x + v.x, y + v.y}; }
  Point8 operator-(Point8 v) { return {x - v.x, y - v.y}; }
  Point8 operator*(float l) { return {l * x, l * y}; }
};



class GameState
{
public:
  GameState();
  updateState(Arduboy& arduboy);
  
  uint8_t m_carSpeed;
  static const uint8_t s_maxSpeed = 20;
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
    Opponent();

    // position relative to current car. 127 is far away in front, 0 is in our car, -127 is behind.
    int8_t position;
    char line;
    static const uint8_t speed = 15;
  };

  Opponent* opponents[4];

  Point8 m_vanishingPoint;
  Point8 m_deltaVanishingPoint;
  
  Point8 m_leftLine;
  Point8 m_middleLine;
  Point8 m_rightLine;

  static const int8_t s_trackWidth = 50;
};

#endif
