#include "Spaceship.h"
#include "global_variables.h"

void Spaceship::setPos(int xpos, int ypos)
{
	mPosX = xpos - SHIP_WIDTH / 2;
	mPosY = ypos - SHIP_HEIGHT / 2;
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

	mPosY += mVelY;
	if ((mPosY < 0) || (mPosY + SHIP_HEIGHT > SCREEN_HEIGHT))
	{
		mPosY -= mVelY;
	}
}

void calculate_rotation(Spaceship& e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= e.mPosX+e.SHIP_WIDTH/2;
	y -= e.mPosY+e.SHIP_HEIGHT/2;
	e.rotation = atan2(y, x);
	e.rotation = e.rotation * 180 / 3.14;
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

