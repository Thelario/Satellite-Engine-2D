#include "Texture.h"
#include "../Logger/Logger.h"

Texture::Texture(SDL_Texture* texture, int width, int height)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->tileSize = 0;
}

Texture::Texture(SDL_Texture* texture, int width, int height, int tileSize)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
}

Texture::~Texture() { SDL_DestroyTexture(texture); }

SDL_Texture* Texture::GetTexture() { return texture; }

int Texture::GetWidth() { return width; }

int Texture::GetHeight() { return height; }

int Texture::GetTileSize() { return tileSize; }

const SDL_Rect Texture::GetSourceRect()
{
	SDL_Rect srcRect =
	{
		0,
		0,
		width,
		height
	};

	return srcRect;
}

const SDL_Rect Texture::GetTileSourceRect(int id)
{
	int columns = width / tileSize;
	int rows = height / tileSize;

	if (id < 0 || id > columns * rows)
	{
		Logger::Error("The id passed as parameter is not a valid id for current texture.");
	}

	int row = id % columns;
	int column = id / columns;

	SDL_Rect srcRect =
	{
		row * tileSize,
		column * tileSize,
		tileSize,
		tileSize
	};

	return srcRect;
}