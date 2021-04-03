#include "global_variables.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
Spaceship gSpaceShip;
Rubble gSpaceRubble[12];
LTexture gShipTexture;
LTexture gRubbleTexture[12];
LTexture gBackgroundTexture;
SDL_Rect gSpriteClips[3];