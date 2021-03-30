#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Rubble.h"
#include "Spaceship.h"
#include "LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Spaceship gSpaceShip;
extern Rubble gSpaceRubble[4];
extern LTexture gShipTexture;
extern LTexture gRubbleTexture[4];
extern LTexture gBackgroundTexture;
extern SDL_Rect gSpriteClips[3];
