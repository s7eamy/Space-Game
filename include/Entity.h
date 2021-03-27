#pragma once
#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include "LTexture.h"

class Entity
{
private:
	int mPosX;
	int mPosY;
	int mVelX;
	int mVelY;
	LTexture mEntityTexture;
	

public:
	Entity();

	static const int ENTITY_VEL = 10;
	static const int ENTITY_WIDTH = 150;
	static const int ENTITY_HEIGHT = 150;

	void render(SDL_Rect* clip = nullptr);
	void handleEvent(SDL_Event& e);
	void move();

};
