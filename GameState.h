#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Arduboy.h"

struct Point8
{ 
  Point8(int8_t x_, int8_t y_) : x(x_), y(y_) {}
  Point8() : x(0), y(0) {}
  int8_t x;
  int8_t y;
  Point8 operator+(Point8 v) { return Point8(x + v.x, y + v.y); }
  Point8 operator-(Point8 v) { return Point8(x - v.x, y - v.y); }
  Point8 operator*(float l) { return Point8(l * x, l * y); }
};



class GameState
{
public:
  GameState();
  void updateState(Arduboy& arduboy);
  

  bool m_leftWasPressed;
  bool m_rightWasPressed;

  uint32_t m_currentFrame;

  Point8 m_vanishingPoint;
  Point8 m_deltaVanishingPoint;
  
  Point8 m_leftLine;
  Point8 m_middleLine;
  Point8 m_rightLine;
  static const int8_t s_trackWidth = 50;

  static const uint8_t s_maxSpeed = 18;
  enum Line
  {
    LEFT,
    MIDDLE,
    RIGHT
  };

  struct Car
  {
    Car() : position(0), line(MIDDLE), speed(0) {}

    // position relative to current car. 127 is far away in front, 0 is in our car, -127 is behind.
    int8_t position;
    char line;
    uint8_t speed;
  };
  Car m_player;
  uint8_t m_playerLife;
  Car* opponents[16];
  static const uint8_t s_oponentSpeed = 15;
};

#endif
