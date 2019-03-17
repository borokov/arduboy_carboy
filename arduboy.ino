#include "Arduboy.h"
#include "GameState.h"
#include "GameDrawer.h"

// Make an instance of arduboy used for many functions
Arduboy g_arduboy;
GameState g_gameState;
GameDrawer g_gameDrawer;

void setup() {
  g_arduboy.beginNoLogo();

  g_arduboy.setFrameRate(15);
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  // pause render until it's time for the next frame
  if (!(g_arduboy.nextFrame()))
    return;

  g_gameState.updateState(g_arduboy);

  g_gameDrawer.draw(g_arduboy, g_gameState);
}
