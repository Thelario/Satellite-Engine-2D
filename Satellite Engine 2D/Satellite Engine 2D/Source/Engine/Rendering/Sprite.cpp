#include "Sprite.h"
#include "../Logger/Logger.h"

Sprite::Sprite(std::string assetId, int width, int height, int size, int zIndex,
	int tileSetWidth, int tileSetHeight, Color color, bool flipX, bool isFixed)
{
	this->assetId = assetId;
	this->width = width;
	this->height = height;
	this->size = size;
	this->zIndex = zIndex;
	this->tileSetWidth = tileSetWidth;
	this->tileSetHeight = tileSetHeight;
	this->color = color;
	this->flipX = flipX;
	this->isFixed = isFixed;
}

const SDL_Rect Sprite::GetSourceRect(int id)
{
	int columns = tileSetWidth / size;
	int rows = tileSetHeight / size;

	if (id < 0 || id > columns * rows)
	{
		Logger::Error("The id passed as parameter is not a valid id for current texture.");
	}

	int row = id % columns;
	int column = id / columns;

	SDL_Rect srcRect =
	{
		row * size,
		column * size,
		size,
		size
	};

	return srcRect;
}

const int Sprite::GetSize()
{
	return size;
}

const Color Sprite::GetColor()
{
	return color;
}

const std::string& Sprite::GetAssetId()
{
	return assetId;
}