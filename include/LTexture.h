#pragma once
#include <stdint.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class LTexture
{
public:
	// ctor & dtor
	LTexture();
	~LTexture();

	// loads image from specified path
	bool loadFromFile(std::string path);
	
	// deallocates texture
	void free();

	// set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// render texture
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// get image dimensions
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }

private:
	SDL_Texture* mTexture;
	
	int mWidth;
	int mHeight;
};
