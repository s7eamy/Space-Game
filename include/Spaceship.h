#pragma once
#include "Entity.h"

class Spaceship : public Entity
{
protected:
	int mHealth = 0;

public:
	Spaceship();
	
	static const int SHIP_VEL = 10;
	static const int SHIP_WIDTH = 150;
	static const int SHIP_HEIGHT = 150;

	void handleEvent(SDL_Event& e);
	void move();
	friend void calculate_rotation(Spaceship &e);

};
