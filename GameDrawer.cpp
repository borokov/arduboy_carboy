#include "GameDrawer.h"


#define SCREEN_LEFT 0
#define SCREEN_RIGHT 128
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 64
#define SCREEN_WIDTH 128

GameDrawer::GameDrawer()
{
}

void GameDrawer::draw(Arduboy& arduboy, GameState& gameState)
{
  // we clear our screen to black
  arduboy.clear();

  drawSpeed(arduboy, gameState);

  drawCar(arduboy, gameState);

  drawTrack(arduboy, gameState);

  drawOpponent(arduboy, gameState);

  // then we finaly we tell the arduboy to display what we just wrote to the display.
  arduboy.display();
}

void GameDrawer::drawSpeed(Arduboy& arduboy, GameState& gameState)
{
  arduboy.setCursor(2, 2);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(String(gameState.m_carSpeed).c_str());
}

void GameDrawer::drawCar(Arduboy& arduboy, GameState& gameState)
{
  const unsigned char CAR_WIDTH = 32;
  const unsigned char CAR_HEIGHT = 8;
  int8_t x;
  int8_t y = 50;
  switch( gameState.m_currentLine )
  {
    case GameState::LEFT:
    x = 4;
    break;
    case GameState::MIDDLE:
    x = 48;
    break;
    case GameState::RIGHT:
    x = 92;
    break;
  }
  
  arduboy.drawRect(x, y, CAR_WIDTH, CAR_HEIGHT, WHITE);
}

void GameDrawer::drawTrack(Arduboy& arduboy, GameState& gameState)
{
  const int8_t x0 = SCREEN_WIDTH/2;
  const int8_t y0 = -50;

  const int8_t trackWidth = 50;
  
  arduboy.drawLine(x0, y0, SCREEN_WIDTH/2 - trackWidth/2 - trackWidth, SCREEN_BOTTOM, WHITE);

  arduboy.drawLine(x0, y0, SCREEN_WIDTH/2 - trackWidth/2, SCREEN_BOTTOM, WHITE);

  arduboy.drawLine(x0, y0, SCREEN_WIDTH/2 + trackWidth/2, SCREEN_BOTTOM, WHITE);

  arduboy.drawLine(x0, y0, SCREEN_WIDTH/2 + trackWidth/2 + trackWidth, SCREEN_BOTTOM, WHITE);
}

void GameDrawer::drawOpponent(Arduboy& arduboy, GameState& gameState)
{
  for ( int i = 0; i < sizeof(gameState.opponents) / sizeof(void*); i++ )
  {
    if ( gameState.opponents[i] == NULL )
      continue;
    
    const unsigned char CAR_WIDTH = 32;
    const unsigned char CAR_HEIGHT = 8;
    int8_t x;
    int8_t y = gameState.opponents[i]->position;
    switch( gameState.opponents[i]->line )
    {
      case GameState::LEFT:
      x = 4;
      break;
      case GameState::MIDDLE:
      x = 48;
      break;
      case GameState::RIGHT:
      x = 92;
      break;
    }
   
    arduboy.drawRect(x, y, CAR_WIDTH, CAR_HEIGHT, WHITE);
  }
}
