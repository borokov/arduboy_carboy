#include "GameState.h"

#define MAX_SPEED 20

GameState::GameState()
{
  m_carSpeed = 0;
  m_currentLine = MIDDLE;
  m_currentFrame = 0;
  memset(opponents, 0, sizeof(opponents) / sizeof(void*));
}

GameState::updateState(Arduboy& arduboy)
{
  //----------------------------------------------------------
  // Update car pos
  if ( arduboy.pressed(B_BUTTON) && m_carSpeed < MAX_SPEED )
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
  // Update oponents
  for ( int i = 0; i < sizeof(opponents) / sizeof(void*); i++ )
  {
    if ( opponents[i] == NULL )
      continue;
      
    opponents[i]->position += (m_carSpeed - opponents[i]->speed);
    if ( opponents[i]->position > 64 )
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
          opponents[i] = new Opponent(m_carSpeed);
          break;
        }
      }
    }
  }

  m_currentFrame++;
}

GameState::Opponent::Opponent(uint8_t playerSpeed)
{
  line = random(0, 3);
  if ( playerSpeed > speed )
    position = 0;
  else
    position = 70;
}
