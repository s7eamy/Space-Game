#pragma once
#include "Entity.h"

class Rubble : public Entity
{
protected:
	int mHealth;

public:

	Rubble(int hp = 0) : mHealth{ hp }
	{
		mCollider.w = RUBBLE_WIDTH;
		mCollider.h = RUBBLE_HEIGHT;
	}

	int RUBBLE_VEL = -8;
	int RUBBLE_HEIGHT = 0;
	int RUBBLE_WIDTH = 0;

	int getHealth() {
		return mHealth;
	}

	void setHealth(int hp) {
		mHealth = hp;
	}

	void setRandomPos();
	void setSize(const int w, const int h);
	void move();

};
