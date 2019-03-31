#include "GameDrawer.h"


#define SCREEN_LEFT 0
#define SCREEN_RIGHT 128
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 64
#define SCREEN_WIDTH 128

GameDrawer::GameDrawer()
{
}

//-----------------------------------------------------------------------
void GameDrawer::draw(Arduboy& arduboy, GameState& gameState)
{
  // we clear our screen to black
  arduboy.clear();

  drawSpeed(arduboy, gameState);

  drawLife(arduboy, gameState);

  drawMyCar(arduboy, gameState);

  drawTrack(arduboy, gameState);

  drawOpponent(arduboy, gameState);

  // then we finaly we tell the arduboy to display what we just wrote to the display.
  arduboy.display();
}

//-----------------------------------------------------------------------
void GameDrawer::drawSpeed(Arduboy& arduboy, GameState& gameState)
{
  arduboy.setCursor(2, 2);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(String(gameState.m_carSpeed).c_str());
}

//-----------------------------------------------------------------------
void GameDrawer::drawLife(Arduboy& arduboy, GameState& gameState)
{
  arduboy.setCursor(20, 2);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(String(gameState.m_carLife).c_str());
}

//-----------------------------------------------------------------------
void GameDrawer::drawMyCar(Arduboy& arduboy, GameState& gameState)
{ 
  drawCar(arduboy, gameState.m_currentLine, gameState.m_carPosition, gameState);
}

//-----------------------------------------------------------------------
void GameDrawer::drawCar(Arduboy& arduboy, char line, int8_t position, GameState& gameState)
{
  const uint8_t CAR_WIDTH = 32;
  const uint8_t CAR_HEIGHT = 8;
  float lambda = position / 127.0f;
  Point8 linePoint;
  switch( line )
  {
    case GameState::LEFT:
    linePoint = gameState.m_leftLine;
    break;
    case GameState::MIDDLE:
    linePoint = gameState.m_middleLine;
    break;
    case GameState::RIGHT:
    linePoint = gameState.m_rightLine;
    break;
  }

  Point8 carPos = linePoint + (gameState.m_vanishingPoint - linePoint) * lambda;

  uint8_t scaledWidth = (1.0f - lambda) * CAR_WIDTH;
  uint8_t scaleHeight = (1.0f - lambda) * CAR_HEIGHT;
  arduboy.drawRect(carPos.x - scaledWidth/2, carPos.y - scaleHeight/2, scaledWidth, scaleHeight, WHITE);
}

//-----------------------------------------------------------------------
void GameDrawer::drawTrack(Arduboy& arduboy, GameState& gameState)
{
  arduboy.drawLine(gameState.m_vanishingPoint.x, gameState.m_vanishingPoint.y, 
                   gameState.m_leftLine.x - gameState.s_trackWidth/2, gameState.m_leftLine.y, 
                   WHITE);

  arduboy.drawLine(gameState.m_vanishingPoint.x, gameState.m_vanishingPoint.y, 
                   gameState.m_middleLine.x - gameState.s_trackWidth/2, gameState.m_middleLine.y,  
                   WHITE);
   
  arduboy.drawLine(gameState.m_vanishingPoint.x, gameState.m_vanishingPoint.y, 
                   gameState.m_middleLine.x + gameState.s_trackWidth/2, gameState.m_middleLine.y,  
                   WHITE);

  arduboy.drawLine(gameState.m_vanishingPoint.x, gameState.m_vanishingPoint.y, 
                   gameState.m_rightLine.x + gameState.s_trackWidth/2, gameState.m_rightLine.y,  
                   WHITE);
}

//-----------------------------------------------------------------------
void GameDrawer::drawOpponent(Arduboy& arduboy, GameState& gameState)
{
  for ( uint8_t i = 0; i < sizeof(gameState.opponents) / sizeof(void*); i++ )
  {
    if ( gameState.opponents[i] == NULL )
      continue;

    drawCar(arduboy, gameState.opponents[i]->line, gameState.opponents[i]->position, gameState);
  }
}
