#pragma once

#include <vector>

#include "../../../../../Engine/GameObject/GameObject.h"

#include "../../../DicesManager/DicesManager.h"
#include "DiceItem.h"
#include "DiceStand.h"

class Inventory : public GameObject
{
	private:
		glm::vec2 dices_position;
		float distance_between_items;

		int screen_width;
		int	screen_height;

		std::vector<DiceItem*> dice_items;

		DicesManager* dices_manager;
		DiceStand* dice_stand;

	public:
		Inventory(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0),
			double rotation = 0, const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr,
			int screen_width = 0, int screen_height = 0, DicesManager* dices_manager = nullptr);
		~Inventory();

		void Start() override;
		void Update(double delta_time) override;
		void Render(SDL_Renderer* renderer) override;

		void RenderBackground(SDL_Renderer* renderer);
};