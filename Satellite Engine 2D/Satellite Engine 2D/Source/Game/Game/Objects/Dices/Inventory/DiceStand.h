#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

#include "../../../../../Engine/AssetsManager/AssetsManager.h"

#include "../DiceInfo.h"

class DiceStand
{
	private:
		int faces_size;

		std::vector<glm::vec2> dice_stand_faces_position;

		DiceInfo* current_dice_on_stand;
		AssetsManager* assets_manager;

	public:
		DiceStand(AssetsManager* assets_manager = nullptr);

		void LoadStand(DiceInfo* dice_info);
		void ClearStand();

		void Render(SDL_Renderer* renderer);
};