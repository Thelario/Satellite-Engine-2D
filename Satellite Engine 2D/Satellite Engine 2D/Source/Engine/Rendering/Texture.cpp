#include "Texture.h"

#include "../Logger/Logger.h"

Texture::Texture(SDL_Texture* texture, int width, int height)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->tile_size = 0;
}

Texture::Texture(SDL_Texture* texture, int width, int height, int tile_size)
{
	this->texture = texture;
	this->width = width;
	this->height = height;
	this->tile_size = tile_size;
}

Texture::~Texture() { SDL_DestroyTexture(texture); }

SDL_Texture* Texture::GetTexture() const { return texture; }

int Texture::GetWidth() const { return width; }

int Texture::GetHeight() const { return height; }

int Texture::GetTileSize() const { return tile_size; }

const SDL_Rect Texture::GetSourceRect() const { return { 0, 0, width, height }; }

const SDL_Rect Texture::GetTileSourceRect(int id) const
{
	if (tile_size == 0) {
		Logger::Error("The current texture has a tileSize of 0, which means that it is not a tileSet and just a single image.");
		return { 0, 0, 0, 0 };
	}

	int columns = width / tile_size;
	int rows = height / tile_size;

	if (id < 0 || id > columns * rows) {
		Logger::Error("The id passed as parameter is not a valid id for current texture.");
	}

	int row = id % columns;
	int column = id / columns;

	SDL_Rect src_rect =
	{
		row * tile_size,
		column * tile_size,
		tile_size,
		tile_size
	};

	return src_rect;
}