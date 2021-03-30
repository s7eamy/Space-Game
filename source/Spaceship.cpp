#include "Spaceship.h"

void Spaceship::setPos(int xpos, int ypos)
{
	mPosX = xpos - ENTITY_WIDTH / 2;
	mPosY = ypos - ENTITY_HEIGHT / 2;
}