#include "Spaceship.h"
#include "global_variables.h"
#define PI 3.14

Spaceship::Spaceship()
{
	mCollider.w = SHIP_WIDTH;
	mCollider.h = SHIP_HEIGHT;
	mPosX = SCREEN_WIDTH / 2 - SHIP_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2 - SHIP_HEIGHT / 2;
}

void Spaceship::move()
{
	//double radians = (rotation * 3.14) / 180;
	calculate_rotation(*this);
	mPosX += mVelX;
	if ((mPosX < 0) || (mPosX + SHIP_WIDTH > SCREEN_WIDTH))
	{
		mPosX -= mVelX;
	}
	mCollider.x = mPosX;

	mPosY += mVelY;
	if ((mPosY < 0) || (mPosY + SHIP_HEIGHT > SCREEN_HEIGHT))
	{
		mPosY -= mVelY;
	}
	mCollider.y = mPosY;
}

void calculate_rotation(Spaceship& e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= e.mPosX+e.SHIP_WIDTH/2;
	y -= e.mPosY+e.SHIP_HEIGHT/2;
	e.rotation = atan2(y, x); // returns radians
	e.rotation = e.rotation * 180 / PI; // convert to degrees
	e.rotation += 90;
}

void Spaceship::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			mVelY -= SHIP_VEL;
			break;

			case SDLK_s:
			mVelY += SHIP_VEL;
			break;

			case SDLK_a:
			mVelX -= SHIP_VEL;
			break;

			case SDLK_d:
			mVelX += SHIP_VEL;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
			mVelY += SHIP_VEL;
			break;

			case SDLK_s:
			mVelY -= SHIP_VEL;
			break;

			case SDLK_a:
			mVelX += SHIP_VEL;
			break;

			case SDLK_d:
			mVelX -= SHIP_VEL;
			break;
		}
	}
}
