#pragma once
#include "Entity.h"

class Bullet : public Entity
{
protected:
	bool mExpired;

public:

	Bullet() : mExpired{ 1 } {}
	static const int BULLET_DMG = 50;
	static const int BULLET_VEL = 25;
	static const int BULLET_WIDTH = 20;
	static const int BULLET_HEIGHT = 21;

	void activate(double rot);
	void expire() { mExpired = 1; }
	void move();
};