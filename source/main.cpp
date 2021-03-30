#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "global_variables.h"

/**
* 1. Implement space rubble
* 2. Implement health
* 3. Implement bullets from spaceship
* 4. Scrolling background
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
		for (int i = 0; i < 4; i++)
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
	if (!gRubbleTexture[0].loadFromFile("rubble1.png"))
	{
		std::cout << "Failed to load rubble1.png\n";
		return false;
	}
	if (!gRubbleTexture[1].loadFromFile("rubble2.png"))
	{
		std::cout << "Failed to load rubble2.png\n";
		return false;
	}
	if (!gRubbleTexture[2].loadFromFile("rubble3.png"))
	{
		std::cout << "Failed to load rubble3.png\n";
		return false;
	}
	if (!gRubbleTexture[3].loadFromFile("rubble4.png"))
	{
		std::cout << "Failed to load rubble4.png\n";
		return false;
	}
	return true;
}