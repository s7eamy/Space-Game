#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "include/Entity.h"
#include "include/LTexture.h"
#include "include/global_variables.h"

/**
* 1. Fix right side collision error ( THIS HAPPENS BECAUSE OF SPRITE SHEET, SINCE TEXTURE IS VERY WIDE. USE CURRENTCLIP )
* 2. Implement rotation with right & left keys
* 3. Implement space rubble
* 4. Implement health
* 5. Implement bullets from spaceship
*/

bool Init();

int main(int argc, char* args[])
{
	if (!Init())
	{
		std::cout << "Failed to initialize!" << std::endl;
		return 1;
	}
	if (!gShipTexture.loadFromFile("rocketship.png"))
	{
		std::cout << "Failed to load rocketship.png!\n";
		return 1;
	}
	else
	{
		gSpriteClips[0] = { 0, 0, 150, 150 };
		gSpriteClips[1] = { 150, 0, 150, 150 };
		gSpriteClips[2] = { 300, 0, 150, 150 };
	}
	if (!gBackgroundTexture.loadFromFile("background.png"))
	{
		std::cout << "Failed to load background.png!\n";
		return 1;
	}
	bool gameOver = 0;
	int frame = 0;
	SDL_Event ev;
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
		// render the currently selected sprite
		gBackgroundTexture.render(0, 0);
		gSpaceShip.render( currentClip );
		SDL_RenderPresent(gRenderer);
		frame++;
		if (frame / 3 >= 3)
		{
			frame = 0;
		}
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