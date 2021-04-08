#pragma once
#include "Entity.h"

class Bullet : public Entity
{
protected:
	bool mExpired;

public:

	Bullet() : mExpired{ 1 } {}
	static const int BULLET_DMG = 50;
	static const int BULLET_VEL = 40;
	static const int BULLET_WIDTH = 20;
	static const int BULLET_HEIGHT = 21;

	bool isActive() { return !mExpired; }
	void activate(double rot);
	void expire();
	void move();
};
