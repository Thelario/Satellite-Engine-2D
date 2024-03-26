#pragma once

#include "../../../Engine/GameObject/GameObject.h"

class Enemy : public GameObject
{
	private:
		int current_health;
		int max_health;

	public:
		Enemy(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0),
			double rotation = 0, std::string asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr);

		void Render(SDL_Renderer* renderer) override;
};