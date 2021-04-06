#include "Bullet.h"
#include "global_variables.h"
#define PI 3.14

void Bullet::activate(double rot)
{
	rotation = rot;
	mPosX = gSpaceShip.getPosX() + gSpaceShip.SHIP_WIDTH/2;
	mPosY = gSpaceShip.getPosY() + gSpaceShip.SHIP_HEIGHT/2;
}

void Bullet::move()
{
	double radians = (rotation * PI) / 180;
	// fix this
	int x_vel = sin(radians) * BULLET_VEL;
	int y_vel = cos(radians) * BULLET_VEL;

	mPosX += x_vel;
	if (mPosX < 0 || mPosX > SCREEN_WIDTH)
	{
		expire();
	}
	mPosY += y_vel;
	if (mPosY < 0 || mPosY > SCREEN_HEIGHT)
	{
		expire();
	}
}