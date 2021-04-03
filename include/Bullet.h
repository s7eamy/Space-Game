#pragma once
#include "Entity.h"

class Bullet : public Entity
{
protected:
	int mDamage = 0;

public:
	static const int BULLET_VEL = 25;
};
