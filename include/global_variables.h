#pragma once
#include <SDL.h>
#include <array>
#include "Entity.h"
#include "Rubble.h"
#include "Spaceship.h"
#include "LTexture.h"
#include "Bullet.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int BULLET_COUNT;
extern const int MAX_BULLETS;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Spaceship gSpaceShip;
extern Rubble gSpaceRubble[12];
extern std::array<Bullet, 50> gShipBullets;
extern LTexture gShipTexture;
extern LTexture gRubbleTexture[12];
extern LTexture gBackgroundTexture;
extern LTexture gBulletTexture;
extern SDL_Rect gSpriteClips[3];
