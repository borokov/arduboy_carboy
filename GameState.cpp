#include "GameState.h"

GameState::GameState()
{
  m_carSpeed = 0;
  m_currentLine = MIDDLE;
  m_currentFrame = 0;
  memset(opponents, 0, sizeof(opponents) / sizeof(void*));
  m_carLife = 3;

  m_vanishingPoint = Point8(64, -50);
  m_middleLine = Point8(64 , 64);
  m_leftLine = Point8(m_middleLine.x - s_trackWidth, 64);
  m_rightLine = Point8(m_middleLine.x + s_trackWidth, 64);

  m_deltaVanishingPoint = Point8(1, 1);
}

void
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

  m_carPosition = 15 * m_carSpeed / s_maxSpeed;

  m_leftWasPressed = arduboy.pressed(LEFT_BUTTON);
  m_rightWasPressed = arduboy.pressed(RIGHT_BUTTON);

  //----------------------------------------------------------
  // Update vanishing point
  if ( m_vanishingPoint.x > 80 )
  {
    m_deltaVanishingPoint.x = random(-2, 0);
    m_deltaVanishingPoint.y = random(-1, 1);
  }

  if ( m_vanishingPoint.x < 40 )
  {
    m_deltaVanishingPoint.x = random(0, 2);
    m_deltaVanishingPoint.y = random(-1, 1);
  }

  if ( m_vanishingPoint.y < -60 )
  {
    m_deltaVanishingPoint.x = random(0, 2) - 1;
    m_deltaVanishingPoint.y = random(0, 2);
  }

  if ( m_vanishingPoint.y > -40 )
  {
    m_deltaVanishingPoint.x = random(0, 2) - 1;
    m_deltaVanishingPoint.y = random(-2, 0);
  }
  
  m_vanishingPoint = m_vanishingPoint + m_deltaVanishingPoint;

  //----------------------------------------------------------
  // Update oponents
  for ( uint8_t i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
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

  //----------------------------------------------------------
  // Check colisions
  for ( uint8_t i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
  {
    if ( opponents[i] == NULL )
      continue;
      
    opponents[i]->position += (opponents[i]->speed - m_carSpeed);
    // If oponent get behind us (or very far awayt in front=> int overflow),
    // delete it.
    if ( m_currentLine == opponents[i]->line && m_carPosition <= opponents[i]->position && opponents[i]->position <= m_carPosition + 5 )
    {
      m_carSpeed = 0;
      m_carLife--;
      for ( uint8_t i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
      {
        delete opponents[i];
        opponents[i] = NULL;
      }
      break;
    }
  }

  //-----------------------------------------------------------
  // generate 0, 1 or 2 oponents every 8 frames
  if ( m_currentFrame % 8 == 0 )
  {
    for ( uint8_t i = 0; i < 2; i++ )
    {
      for ( uint8_t j = 0; j < sizeof(opponents) / sizeof(void*); j++ )
      {
        if ( opponents[j] == NULL )
        {
          opponents[j] = new Opponent();
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
