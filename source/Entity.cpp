#include "Entity.h"
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;



void Entity::render( LTexture& text, SDL_Rect* clip)
{
	text.render(mPosX, mPosY, clip, rotation);
}
