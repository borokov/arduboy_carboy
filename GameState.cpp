#include "GameState.h"

GameState::GameState()
{
  m_carSpeed = 0;
  m_currentLine = MIDDLE;
  m_currentFrame = 0;
  memset(opponents, 0, sizeof(opponents) / sizeof(void*));

  m_vanishingPoint = {64, -50};
  m_middleLine = {64 , 64};
  m_leftLine = {m_middleLine.x - s_trackWidth, 64};
  m_rightLine = {m_middleLine.x + s_trackWidth, 64};

  m_deltaVanishingPoint = {1, 1};
}

GameState::updateState(Arduboy& arduboy)
{
  //----------------------------------------------------------
  // Update car pos
  if ( arduboy.pressed(B_BUTTON) && m_carSpeed < s_maxSpeed )
    m_carSpeed++;

  if ( arduboy.notPressed(B_BUTTON) && m_carSpeed > 0 )
    m_carSpeed--;
  
   if ( arduboy.pressed(LEFT_BUTTON) && !m_leftWasPressed && m_currentLine != LEFT )
    m_currentLine--;

   if ( arduboy.pressed(RIGHT_BUTTON) && !m_rightWasPressed && m_currentLine != RIGHT )
    m_currentLine++;

  m_leftWasPressed = arduboy.pressed(LEFT_BUTTON);
  m_rightWasPressed = arduboy.pressed(RIGHT_BUTTON);

  //----------------------------------------------------------
  // Update vanishing point
  if ( m_vanishingPoint.x > 100 )
  {
    m_deltaVanishingPoint.x = random(-2, 0);
    m_deltaVanishingPoint.y = random(-1, 1);
  }

  if ( m_vanishingPoint.x < 30 )
  {
    m_deltaVanishingPoint.x = random(0, 2);
    m_deltaVanishingPoint.y = random(-1, 1);
  }

  if ( m_vanishingPoint.y < -60 )
  {
    m_deltaVanishingPoint.x = random(0, 2) - 1;
    m_deltaVanishingPoint.y = random(0, 2);
  }

  if ( m_vanishingPoint.y > 5 )
  {
    m_deltaVanishingPoint.x = random(0, 2) - 1;
    m_deltaVanishingPoint.y = random(-2, 0);
  }
  
  m_vanishingPoint = m_vanishingPoint + m_deltaVanishingPoint;

  //----------------------------------------------------------
  // Update oponents
  for ( int i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
  {
    if ( opponents[i] == NULL )
      continue;
      
    opponents[i]->position += (opponents[i]->speed - m_carSpeed);
    // If oponent get behind us (or very far awayt in front=> int overflow),
    // delete it.
    if ( opponents[i]->position < -5 )
    {
      delete opponents[i];
      opponents[i] = NULL;
    }
  }

  //-----------------------------------------------------------
  // generate 1 or 2 oponents
  if ( m_currentFrame % 8 == 0 )
  {
    for ( int i = 0; i <= random(0, 2); i++ )
    {
      for ( int i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
      {
        if ( opponents[i] == NULL )
        {
          opponents[i] = new Opponent();
          break;
        }
      }
    }
  }

  m_currentFrame++;
}

GameState::Opponent::Opponent()
{
  line = random(0, 3);
  position = 127;
}
