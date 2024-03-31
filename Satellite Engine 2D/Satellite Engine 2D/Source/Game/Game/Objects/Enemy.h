#pragma once

#include "../../../Engine/GameObject/GameObject.h"
#include "../../../Engine/Utils/Random.h"
#include "../../../Engine/Rendering/Text.h"

class Enemy : public GameObject
{
	private:
		int current_health;
		int max_health;

		Text* health_text;
		Random* random;

	public:
		Enemy(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0,
			const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0, Color color = Color(255, 255, 255, 255),
			bool flip_x = false, AssetsManager* assets_manager = nullptr, Text* health_text = nullptr, Random* random = nullptr);

		void Render(SDL_Renderer* renderer) override;

		//void TakeDamage(int damage);
};