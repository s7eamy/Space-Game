#include "Rubble.h"
#include "global_variables.h"
#include <random>
#include <iostream>

void Rubble::setRandomPos()
{
	mPosX = SCREEN_WIDTH;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, (SCREEN_HEIGHT - RUBBLE_HEIGHT));
	mPosY = dist(rng);
}

void Rubble::setSize(const int w, const int h)
{
	RUBBLE_HEIGHT = h;
	RUBBLE_WIDTH = w;
}

void Rubble::move()
{
	mPosX += RUBBLE_VEL;
	if ((mPosX < -RUBBLE_WIDTH))
	{
		mPosX -= RUBBLE_VEL;
		mHealth = 0;
	}
}