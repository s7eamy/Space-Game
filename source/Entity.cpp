#include "Entity.h"
#include <iostream>

void Entity::render( LTexture& text, SDL_Rect* clip)
{
	text.render(mPosX, mPosY, clip, rotation);
}
