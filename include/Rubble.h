#pragma once
#include "Entity.h"

class Rubble : public Entity
{
private:
	int mHealth;

public:

	Rubble(int hp = 0) : mHealth{ hp } {}

	static const int RUBBLE_VEL = -8;

	int getHealth() {
		return mHealth;
	}

	void setHealth(int hp) {
		mHealth = hp;
	}

	void setRandomPos();

	void move();

};
