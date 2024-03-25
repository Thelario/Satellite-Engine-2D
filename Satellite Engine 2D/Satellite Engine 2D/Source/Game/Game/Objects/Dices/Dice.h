#pragma once

#include <vector>

#include "../../../../Engine/GameObject/GameObject.h"
#include "../../../../Engine/Utils/Random.h"

#include "Face.h"
#include "DiceInfo.h"

class Dice : public GameObject
{
	protected:
		bool using_dice;
		bool rotating_dice;

		int face;
		int selected_face;
		
		Uint32 time;
		Uint32 time_rate;
		Uint32 time_rate_increase;
		Uint32 time_rate_limit;
		
		float move_speed;
		glm::vec2 screen_center;
		glm::vec2 direction;
		
		DiceInfo* dice_info;

		Random* random;

	public:
		Dice(std::string name = "", glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0, std::string asset_id = "",
			int width = 0, int height = 0, int z_index = 0, Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr,
			Uint32 time_rate = 0, glm::vec2 screen_center = glm::vec2(0), Uint32 time_rate_limit = 0, Random* random = nullptr);

		void AddFace(Face* face);
		void PrintFaces();

		void Start() override;
		void Update() override;
		void Render(SDL_Renderer* renderer) override;

		void ResetDice();
		void UseDice();
		void CheckMouseOverDice();
};