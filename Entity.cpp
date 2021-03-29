#include "include/Entity.h"
#include "include/global_variables.h"
#include <iostream>

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

Entity::Entity()
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
	rotation = 0.0;
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
		// check double->int casts
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			mVelY -= ENTITY_VEL;
			break;

			case SDLK_DOWN:
			mVelY += ENTITY_VEL;
			break;

			case SDLK_LEFT:
			mVelX -= ENTITY_VEL;
			break;

			case SDLK_RIGHT:
			mVelX += ENTITY_VEL;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			mVelY += ENTITY_VEL;
			break;

			case SDLK_DOWN:
			mVelY -= ENTITY_VEL;
			break;

			case SDLK_LEFT:
			mVelX += ENTITY_VEL;
			break;

			case SDLK_RIGHT:
			mVelX -= ENTITY_VEL;
			break;
		}
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
	}
}


void Entity::render(SDL_Rect* clip)
{
	gShipTexture.render(mPosX, mPosY, clip, rotation);
}
