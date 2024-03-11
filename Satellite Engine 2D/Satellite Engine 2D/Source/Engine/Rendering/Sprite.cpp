#include "Sprite.h"

Sprite::Sprite(std::string assetId, int width, int height, int zIndex, Color color, bool flipX, bool isFixed)
{
	this->assetId = assetId;
	this->width = width;
	this->height = height;
	this->zIndex = zIndex;
	this->color = color;
	this->flipX = flipX;
	this->isFixed = isFixed;
}

const Color Sprite::GetColor() { return color; }

const std::string& Sprite::GetAssetId() { return assetId; }