#include "Entity.h"
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void calculate_rotation(Entity& e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= e.mPosX+e.ENTITY_WIDTH/2;
	y -= e.mPosY+e.ENTITY_HEIGHT/2;
	e.rotation = atan2(y, x);
	e.rotation = e.rotation * 180 / 3.14;
	e.rotation += 90;
}

void Entity::move()
{
	//double radians = (rotation * 3.14) / 180;
	calculate_rotation(*this);
	mPosX += mVelX;
	if ((mPosX < 0) || (mPosX + ENTITY_WIDTH > SCREEN_WIDTH))
	{
		mPosX -= mVelX;
	}

	mPosY += mVelY;
	if ((mPosY < 0) || (mPosY + ENTITY_HEIGHT > SCREEN_HEIGHT))
	{
		mPosY -= mVelY;
	}
}

void Entity::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			mVelY -= ENTITY_VEL;
			break;

			case SDLK_s:
			mVelY += ENTITY_VEL;
			break;

			case SDLK_a:
			mVelX -= ENTITY_VEL;
			break;

			case SDLK_d:
			mVelX += ENTITY_VEL;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			mVelY += ENTITY_VEL;
			break;

			case SDLK_s:
			mVelY -= ENTITY_VEL;
			break;

			case SDLK_a:
			mVelX += ENTITY_VEL;
			break;

			case SDLK_d:
			mVelX -= ENTITY_VEL;
			break;
		}
	}
}


void Entity::render( LTexture& text, SDL_Rect* clip)
{
	text.render(mPosX, mPosY, clip, rotation);
}
