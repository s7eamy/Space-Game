#pragma once
#include <SDL.h>
#include "include/Entity.h"
#include "include/LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Entity gSpaceShip;
extern LTexture gShipTexture;
extern LTexture gBackgroundTexture;
extern SDL_Rect gSpriteClips[3];
