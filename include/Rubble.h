#pragma once
#include "Entity.h"

class Rubble : public Entity
{
private:
	int mHealth;

public:
	Rubble(int xposr = 1080, int hp = 0, int h = 0, int w = 0) : 
		mHealth{ hp }, Entity{ 0, 0, xposr, 0, 0.0 }, RUBBLE_WIDTH{ w }, RUBBLE_HEIGHT{ h }
	{
	}

	static const int RUBBLE_VEL = 5;
	int RUBBLE_WIDTH, RUBBLE_HEIGHT;

	void move();

};
