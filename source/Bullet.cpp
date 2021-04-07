#include <iostream>
#include "Bullet.h"
#include "global_variables.h"
#define PI 3.14

void Bullet::activate(double rot)
{
	rotation = rot;
	double radians = (rotation * PI) / 180;
	mVelX = sin(radians) * BULLET_VEL;
	mVelY = cos(radians) * BULLET_VEL;
	/*
	std::cout << "Rotation: " << rotation << '\n';
	std::cout << "Velocity X: " << mVelX << '\n';
	std::cout << "Velocity Y:" << mVelY << '\n';
	std::cout << std::endl;
	*/
	mPosX = gSpaceShip.getPosX() + gSpaceShip.SHIP_WIDTH/2;
	mPosY = gSpaceShip.getPosY() + gSpaceShip.SHIP_HEIGHT/2;
}

void Bullet::move()
{
	mPosX += mVelX;
	if (mPosX < 0 || mPosX > SCREEN_WIDTH)
	{
		expire();
	}
	mPosY -= mVelY;
	if (mPosY < 0 || mPosY > SCREEN_HEIGHT)
	{
		expire();
	}
}