#include "global_variables.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
Spaceship gSpaceShip;
Rubble gSpaceRubble[12];
std::array<Bullet, 50> gShipBullets;
LTexture gShipTexture;
LTexture gRubbleTexture[12];
LTexture gBackgroundTexture;
LTexture gBulletTexture;
SDL_Rect gSpriteClips[3];