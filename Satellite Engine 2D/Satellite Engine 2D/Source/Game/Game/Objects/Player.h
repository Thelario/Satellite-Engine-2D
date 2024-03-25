#pragma once

#include <vector>

#include "./Dices/Dice.h"

class Player : public GameObject
{
	private:
		int current_health;
		int max_health;

		int current_mana;
		int max_mana;

		int current_hand_size;
		int max_hand_size;

		std::vector<Dice*> dice_inventory;

	public:
		Player(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0),
			double rotation = 0, std::string asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr);
};