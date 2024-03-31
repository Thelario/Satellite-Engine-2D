#pragma once

#include "Player.h"
#include "Enemy.h"

#include "../../../Engine/Rendering/Text.h"

enum Turn { PLAYER, ENEMY };

class BattleRoom : public GameObject
{
	private:
		int screen_width;
		int screen_height;

		glm::vec2 dice_hand_initial_position;
		int dice_hand_separation_between_dices;

		glm::vec2 player_position;
		glm::vec2 enemy_position;

		static Turn turn;

		Player* player;
		Enemy* enemy;

		Text* player_health_text;
		Text* player_mana_text;
		Text* enemy_health_text;

		Random* random;

		std::vector<Dice*> player_dices;

	public:
		BattleRoom(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0),
			double rotation = 0, const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255), bool flip_x = false, AssetsManager* assets_manager = nullptr,
			int screen_width = 0, int screen_height = 0, Random* random = nullptr);
		~BattleRoom();

		void Start() override;
		void Update(double delta_time) override;
		void Render(SDL_Renderer* renderer) override;

		void ClearRoom();
		void ConfigureRoom();
		void RenderBackground(SDL_Renderer* renderer);
		
		static Turn GetTurn();
		static void SetTurn(Turn new_turn);
		static void AttackPlayer(int damage);
		static void ShieldPlayer(int defense);
		static void AttackEnemy(int damage);
};