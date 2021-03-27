#include "include/Entity.h"
#include "include/global_variables.h"
#include <iostream>

Entity::Entity()
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
	mEntityTexture = LTexture();
}

void Entity::move()
{
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
			case SDLK_UP:
			mVelY -= ENTITY_VEL;
			std::cout << "User pressed up!\n";
			break;

			case SDLK_DOWN:
			mVelY += ENTITY_VEL;
			std::cout << "User pressed down!\n";
			break;

			case SDLK_LEFT:
			mVelX -= ENTITY_VEL;
			std::cout << "User pressed left!\n";
			break;

			case SDLK_RIGHT:
			mVelX += ENTITY_VEL;
			std::cout << "User pressed right!\n";
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			mVelY += ENTITY_VEL;
			std::cout << "User released up!\n";
			break;

			case SDLK_DOWN:
			mVelY -= ENTITY_VEL;
			std::cout << "User released down!\n";
			break;

			case SDLK_LEFT:
			mVelX += ENTITY_VEL; 
			std::cout << "User released left!\n";
			break;

			case SDLK_RIGHT:
			mVelX -= ENTITY_VEL;
			std::cout << "User released right!\n";
			break;
		}
	}
}


void Entity::render(SDL_Rect* clip)
{
	gShipTexture.render(mPosX, mPosY, clip);
}
