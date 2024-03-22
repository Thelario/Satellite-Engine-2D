#pragma once

#include <SDL.h>

class Texture
{
	private:
		SDL_Texture* texture;
		int width;
		int height;
		int tile_size;

	public:
		Texture(SDL_Texture* texture, int width, int height);
		Texture(SDL_Texture* texture, int width, int height, int tile_size);
		~Texture();

		SDL_Texture* GetTexture();
		int GetWidth();
		int GetHeight();
		int GetTileSize();
		const SDL_Rect GetSourceRect();
		const SDL_Rect GetTileSourceRect(int id);
};