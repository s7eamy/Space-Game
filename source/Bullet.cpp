#include <iostream>
#include "Bullet.h"
#include "global_variables.h"
#define PI 3.14

void Bullet::expire()
{
	mExpired = 1;
	BULLET_COUNT--;
	std::cout << "A bullet expired! " << BULLET_COUNT << " bullets left.\n";
}

void Bullet::activate(double rot)
{
	mExpired = 0;
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
	mCollider.x = mPosX;
	mCollider.y = mPosY;
	mCollider.h = BULLET_HEIGHT;
	mCollider.w = BULLET_WIDTH;
	BULLET_COUNT++;
}

void Bullet::move()
{
	mPosX += mVelX;
	if (mPosX < 0 || mPosX > SCREEN_WIDTH)
	{
		expire();
	}
	mCollider.x = mPosX;
	mPosY -= mVelY;
	if (mPosY < 0 || mPosY > SCREEN_HEIGHT)
	{
		expire();
	}
	mCollider.y = mPosY;
}