#pragma once

#include <SDL.h>

class Texture
{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		int tileSize;

	public:
		Texture(SDL_Texture* texture, int width, int height, int tileSize);
		~Texture();

		SDL_Texture* GetTexture();
		int GetWidth();
		int GetHeight();
		int GetTileSize();
		const SDL_Rect GetSourceRect(int id);
};