#include "Rubble.h"
#include "global_variables.h"
#include <random>
#include <iostream>

void Rubble::setRandomPos()
{
	mPosX = SCREEN_WIDTH - 200; // 300 should be RUBBLE_WIDTH instead, change this later
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, (SCREEN_HEIGHT - 200)); // 200 should be sym const
	mPosY = dist(rng);
}

void Rubble::move()
{
	
}