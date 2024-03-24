#pragma once

#include <vector>

#include "Dice.h"

class Player : public GameObject
{
	private:
		std::vector<Dice*> dice_inventory;

	public:
		Player(std::string name = "", glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0),
			double rotation = 0, std::string asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr);
};