#pragma once

#include "../../../Engine/GameObject/GameObject.h"

class Dice : public GameObject
{
	protected:
		bool using_dice;
		int face;
		Uint32 time_rate;
		Uint32 time;

	public:
		Dice(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0, std::string asset_id = "", int width = 0,
			int height = 0, int z_index = 0, Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr,
			int face = 0, Uint32 time_rate = 0);

		void Start() override;
		void Update() override;
		void Render(SDL_Renderer* renderer) override;
		void UseDice();
};