#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global_variables.h"

/** 
* TODO:
* 1. Collision detection
* 2. Bullets from spaceship
* 3. Timer/Score tracker
* 4. Show healthbar of rubble/spaceship
* 5. Difficulty increases over time
*/

bool Init();
bool LoadMedia();

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
	gSpaceShip.setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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
			// handle input events
			gSpaceShip.handleEvent(ev);
		}
		// update spaceship position on screen
		gSpaceShip.move();
		// redraw everything
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		// for animating the spaceship
		SDL_Rect* currentClip = &gSpriteClips[frame / 6];
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
		for (int i = 0; i < 3; i++)
		{
			if (gSpaceRubble[i].getHealth() <= 0)
			{
				std::cout << "Initialized " << i << " rubble!\n";
				gSpaceRubble[i].setHealth(100); // 100 should be a symbolic constant, change this later
				gSpaceRubble[i].setRandomPos();
			}
			else
			{
				gSpaceRubble[i].move();
			}
		}
		for (int i = 0; i < 3; i++)
		{
			gSpaceRubble[i].render(gRubbleTexture[i]);
		}
		if (frame / 3 >= 3)
		{
			frame = 0;
		}
		// show changes
		SDL_RenderPresent(gRenderer);
	}
	return 0;
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
	std::string file = "rubble1.png";
	if (!gRubbleTexture[0].loadFromFile(file) || !gRubbleTexture[4].loadFromFile(file) || !gRubbleTexture[8].loadFromFile(file))
	{
		std::cout << "Failed to load rubble1.png\n";
		return false;
	}
	gSpaceRubble[0].setSize(100, 100);
	gSpaceRubble[4].setSize(100, 100);
	gSpaceRubble[8].setSize(100, 100);
	file = "rubble2.png";
	if (!gRubbleTexture[1].loadFromFile(file) || !gRubbleTexture[5].loadFromFile(file) || !gRubbleTexture[9].loadFromFile(file))
	{
		std::cout << "Failed to load rubble2.png\n";
		return false;
	}
	gSpaceRubble[1].setSize(175, 175);
	gSpaceRubble[5].setSize(175, 175);
	gSpaceRubble[9].setSize(175, 175);
	file = "rubble3.png";
	if (!gRubbleTexture[2].loadFromFile(file) || !gRubbleTexture[6].loadFromFile(file) || !gRubbleTexture[10].loadFromFile(file))
	{
		std::cout << "Failed to load rubble3.png\n";
		return false;
	}
	gSpaceRubble[2].setSize(250, 250);
	gSpaceRubble[6].setSize(250, 250);
	gSpaceRubble[10].setSize(250, 250);
	file = "rubble4.png";
	if (!gRubbleTexture[3].loadFromFile(file) || !gRubbleTexture[7].loadFromFile(file) || !gRubbleTexture[11].loadFromFile(file))
	{
		std::cout << "Failed to load rubble4.png\n";
		return false;
	}
	gSpaceRubble[3].setSize(137, 137);
	gSpaceRubble[7].setSize(137, 137);
	gSpaceRubble[11].setSize(137, 137);
	return true;
}