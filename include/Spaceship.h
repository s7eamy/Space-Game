#pragma once
#include "Entity.h"

class Spaceship : public Entity
{
protected:

public:
	
	static const int SHIP_VEL = 10;
	static const int SHIP_WIDTH = 150;
	static const int SHIP_HEIGHT = 150;

	void setPos(int xpos, int ypos);
	void handleEvent(SDL_Event& e);
	void move();
	friend void calculate_rotation(Spaceship &e);

};
