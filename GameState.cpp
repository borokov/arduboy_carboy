#include "GameState.h"

GameState::GameState()
{
  m_currentFrame = 0;
  memset(opponents, 0, sizeof(opponents) / sizeof(void*));
  m_playerLife = 3;

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
  if ( arduboy.pressed(B_BUTTON) && m_player.speed < s_maxSpeed )
    m_player.speed++;

  if ( arduboy.notPressed(B_BUTTON) && m_player.speed > 0 )
    m_player.speed--;
  
   if ( arduboy.pressed(LEFT_BUTTON) && !m_leftWasPressed && m_player.line != LEFT )
    m_player.line--;

   if ( arduboy.pressed(RIGHT_BUTTON) && !m_rightWasPressed && m_player.line != RIGHT )
    m_player.line++;

  m_player.position = 15 * m_player.speed / s_maxSpeed;

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
  
  m_vanishingPoint = m_vanishingPoint + m_deltaVanishingPoint * (float)((2 * m_player.speed / (float)s_maxSpeed));

  //----------------------------------------------------------
  // Update oponents
  for ( uint8_t i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
  {
    if ( opponents[i] == NULL )
      continue;
      
    opponents[i]->position += (opponents[i]->speed - m_player.speed);
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
      
    opponents[i]->position += (opponents[i]->speed - m_player.speed);
    // If oponent get behind us (or very far awayt in front=> int overflow),
    // delete it.
    if ( m_player.line == opponents[i]->line && m_player.position <= opponents[i]->position && opponents[i]->position <= m_player.position + 5 )
    {
      m_player.speed = 0;
      m_playerLife--;
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
          opponents[j] = new Car();
          opponents[j]->line = random(0, 3);
          opponents[j]->position = 127;
          opponents[j]->speed = s_oponentSpeed;
          break;
        }
      }
    }
  }

  m_currentFrame++;
}

