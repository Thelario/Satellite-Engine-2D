#pragma once

#include "../../../../../Engine/GameObject/GameObject.h"

#include "../DiceInfo.h"

class DiceItem : public GameObject
{
	private:
		DiceInfo* dice_info;

	public:
		DiceItem(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0,
			const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0, Color color = Color(255, 255, 255, 255),
			bool flip_x = false, AssetsManager* assets_manager = nullptr, DiceInfo* dice_info = nullptr);
		~DiceItem() = default;

		void Start() override;
		void Update(double delta_time) override;
		void Render(SDL_Renderer* renderer) override;

		void CheckMouseOverItem();
};