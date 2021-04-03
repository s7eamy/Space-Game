#pragma once
#include "Entity.h"

class Rubble : public Entity
{
private:
	int mHealth;

public:

	Rubble(int hp = 0) : mHealth{ hp } {}

	int RUBBLE_VEL = -8;
	int RUBBLE_HEIGHT;
	int RUBBLE_WIDTH;

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
