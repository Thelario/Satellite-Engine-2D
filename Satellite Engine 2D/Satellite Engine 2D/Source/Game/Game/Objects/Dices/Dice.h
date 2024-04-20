#pragma once

#include <vector>

#include "../../../../Engine/GameObject/GameObject.h"
#include "../../../../Engine/Utils/Random.h"
#include "../../../../Engine/Rendering/Text.h"

#include "Face.h"
#include "DiceInfo.h"

class BattleRoom;
class Dice : public GameObject
{
	protected:
		bool using_dice;
		bool dice_used;
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
		Texture* mana_cost_texture;
		Text* mana_cost_text;
		BattleRoom* battle_room;

	public:
		Dice(const std::string& name = "", glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0,
			const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0, Color color = Color(255, 255, 255, 255),
			bool flip_x = false, AssetsManager* assets_manager = nullptr, Uint32 time_rate = 0, glm::vec2 screen_center = glm::vec2(0),
			Uint32 time_rate_limit = 0, Random* random = nullptr, DiceInfo* dice_info = nullptr, BattleRoom* battle_room = nullptr);

		void Start() override;
		void Update(double delta_time) override;
		void Render(SDL_Renderer* renderer) override;

		void RenderDice(SDL_Renderer* renderer);
		void RenderManaCost(SDL_Renderer* renderer);

		void ResetDice();
		void UseDice(double delta_time);
		void CheckMouseOverDice();
};