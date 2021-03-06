#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global_variables.h"

/** 
* TODO:
* 1. Bullets from spaceship
* 2. Timer/Score tracker
* 3. Show healthbar of rubble/spaceship
* 4. Difficulty increases over time
*/

int num_of_rubble = 3;

bool Init();
bool LoadMedia();
bool CheckCollision(SDL_Rect a, SDL_Rect b);

int main(int argc, char* args[])
{
	if (!Init())
	{
		std::cout << "Failed to initialize!" << std::endl;
		return 1;
	}
	if (!LoadMedia())
	{
		std::cout << "Failed to load media!" << std::endl;
		return 1;
	}
	bool gameOver = 0;
	int frame = 0;
	SDL_Event ev;
	int scrollingOffset = 0;
	while (!gameOver)
	{
		while (SDL_PollEvent(&ev) > 0)
		{
			if (ev.type == SDL_QUIT)
			{
				gameOver = 1;
			}
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				double rot = gSpaceShip.getRotation();
				if (BULLET_COUNT < 50)
					gShipBullets[BULLET_COUNT].activate(rot);
				else
					std::cout << "No ammo left! Wait a bit.\n";
			}
			// handle input events
			gSpaceShip.handleEvent(ev);
		}
		// update spaceship position on screen
		gSpaceShip.move();
		// update rubble position on screen
		for (int i = 0; i < num_of_rubble; i++)
		{
			if (gSpaceRubble[i].getHealth() <= 0)
			{
				gSpaceRubble[i].setHealth(100); // 100 should be a sym const, change this later
				gSpaceRubble[i].setRandomPos();
			}
			else
			{
				gSpaceRubble[i].move();
			}
		}
		// update bullet position on screen
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if( gShipBullets[i].isActive() )
				gShipBullets[i].move();
		}
		// redraw everything
		// clear the screen white
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		// for animating the spaceship
		SDL_Rect* currentClip = &gSpriteClips[frame / 6];
		if (frame / 3 >= 3)
		{
			frame = 0;
		}
		// render scrolling background
		gBackgroundTexture.render(scrollingOffset, 0);
		gBackgroundTexture.render(scrollingOffset + gBackgroundTexture.getWidth(), 0);
		scrollingOffset--;
		if (scrollingOffset < -gBackgroundTexture.getWidth())
		{
			scrollingOffset = 0;
		}
		// render spaceship
		gSpaceShip.render( gShipTexture, currentClip );
		frame++;
		// render rubble
		for (int i = 0; i < num_of_rubble; i++)
		{
			gSpaceRubble[i].render(gRubbleTexture[i]);
			if (CheckCollision(gSpaceRubble[i].mCollider, gSpaceShip.mCollider))
			{
				// do collision stuff (-health for rubble & ship)
			}
			for (int j = 0; j < MAX_BULLETS; j++)
			{
				if(gShipBullets[j].isActive())
					if (CheckCollision(gSpaceRubble[i].mCollider, gShipBullets[j].mCollider))
					{
						std::cout << "Collision between rubble and bullet!\n";
					}
			}
		}
		// render bullets
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if( gShipBullets[i].isActive() )
				gShipBullets[i].render(gBulletTexture);
		}
		// show changes
		SDL_RenderPresent(gRenderer);
	}
	return 0;
}

bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// calculate rect a
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	// calculate rect b
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// check collision
	// |-----topA-----|
	// |              |
	// |              |
	// |-----topB-----|
	// |              |
	// |----bottomA---|
	// |              |
	// |----bottomB---|
	if (bottomA <= topB) return false; 
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;
	return true;
}

bool Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning! Linear texture filtering not enabled!" << std::endl;
	}
	gWindow = SDL_CreateWindow("Space Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr)
	{
		std::cout << "Failed to create window! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "IMG failed to initialize! IMG Error: " << IMG_GetError() << std::endl;
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (gRenderer == nullptr)
	{
		std::cout << "Failed to create renderer! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);
	return true;
}

bool LoadMedia()
{
	if (!gShipTexture.loadFromFile("rocketship.png"))
	{
		std::cout << "Failed to load rocketship.png\n";
		return false;
	}
	else
	{
		gSpriteClips[0] = { 0, 0, 150, 150 };
		gSpriteClips[1] = { 150, 0, 150, 150 };
		gSpriteClips[2] = { 300, 0, 150, 150 };
	}
	if (!gBackgroundTexture.loadFromFile("background.png"))
	{
		std::cout << "Failed to load background.png\n";
		return false;
	}
	// hardcoded values in .setSize() are dimensions of the .png pictures
	std::string file = "rubble1.png";
	if (!gRubbleTexture[0].loadFromFile(file) || !gRubbleTexture[4].loadFromFile(file) || !gRubbleTexture[8].loadFromFile(file))
	{
		std::cout << "Failed to load rubble1.png\n";
		return false;
	}
	gSpaceRubble[0].setSize(81, 72);
	gSpaceRubble[4].setSize(81, 72);
	gSpaceRubble[8].setSize(81, 72);
	file = "rubble2.png";
	if (!gRubbleTexture[1].loadFromFile(file) || !gRubbleTexture[5].loadFromFile(file) || !gRubbleTexture[9].loadFromFile(file))
	{
		std::cout << "Failed to load rubble2.png\n";
		return false;
	}
	gSpaceRubble[1].setSize(150, 157);
	gSpaceRubble[5].setSize(150, 157);
	gSpaceRubble[9].setSize(150, 157);
	file = "rubble3.png";
	if (!gRubbleTexture[2].loadFromFile(file) || !gRubbleTexture[6].loadFromFile(file) || !gRubbleTexture[10].loadFromFile(file))
	{
		std::cout << "Failed to load rubble3.png\n";
		return false;
	}
	gSpaceRubble[2].setSize(240, 224);
	gSpaceRubble[6].setSize(240, 224);
	gSpaceRubble[10].setSize(240, 224);
	file = "rubble4.png";
	if (!gRubbleTexture[3].loadFromFile(file) || !gRubbleTexture[7].loadFromFile(file) || !gRubbleTexture[11].loadFromFile(file))
	{
		std::cout << "Failed to load rubble4.png\n";
		return false;
	}
	gSpaceRubble[3].setSize(126, 129);
	gSpaceRubble[7].setSize(126, 129);
	gSpaceRubble[11].setSize(126, 129);
	if (!gBulletTexture.loadFromFile("bullet.png"))
	{
		std::cout << "Failed to load bullet.png\n";
		return false;
	}
	return true;
}