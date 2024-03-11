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
		int zIndex;
		bool flipX;
		bool isFixed;
		Color color;

	public:
		Sprite(std::string assetId = "", int width = 0, int height = 0, int zIndex = 0,
			Color color = Color(255, 255, 255, 255), bool flipX = false, bool isFixed = false);
		~Sprite() = default;

		const Color GetColor();
		const std::string& GetAssetId();
};