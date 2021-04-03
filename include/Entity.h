#pragma once
#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include "LTexture.h"

class Entity
{
protected:
	int mPosX;
	int mPosY;
	int mVelX;
	int mVelY;
	double rotation;

	Entity(int xvel = 0, int yvel = 0, int xpos = 0, int ypos = 0, double rot = 0.0) :
		mPosX{ xpos }, mPosY{ ypos }, mVelX{ xvel }, mVelY{ yvel }, rotation{ rot }, mCollider{ 0, 0, 0, 0 }
	{
	}

public:
	SDL_Rect mCollider;
	void render( LTexture& text, SDL_Rect* clip = nullptr);
};
