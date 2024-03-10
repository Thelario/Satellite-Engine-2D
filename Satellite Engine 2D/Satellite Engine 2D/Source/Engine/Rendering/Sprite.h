#pragma once

#include <SDL.h>
#include <string>
#include "../Utils/Color.h"

class Sprite
{
	private:
		std::string assetId;
		int width;
		int height;
		int size;
		int tileSetWidth;
		int tileSetHeight;
		int zIndex;
		bool flipX;
		bool isFixed;
		Color color;

	public:
		Sprite(std::string assetId = "", int width = 0, int height = 0, int size = 0, int zIndex = 0,
			int tileSetWidth = 0, int tileSetHeight = 0, Color color = Color(255, 255, 255, 255), bool flipX = false, bool isFixed = false);
		~Sprite() = default;

		const SDL_Rect GetSourceRect(int id);
		const int GetSize();
		const Color GetColor();
		const std::string& GetAssetId();
};