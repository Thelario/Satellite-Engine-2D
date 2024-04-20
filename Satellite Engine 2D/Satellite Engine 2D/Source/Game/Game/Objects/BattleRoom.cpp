#include "BattleRoom.h"

#include "../../../Engine/Logger/Logger.h"

#include "Player.h"

Turn BattleRoom::turn = Turn::PLAYER;

BattleRoom::BattleRoom(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager, int screen_width, int screen_height, Random* random)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	this->random = random;

	ConfigureRoom();
}

BattleRoom::~BattleRoom()
{
	delete player;
	delete enemy;

	delete player_health_text;
	delete player_mana_text;
	delete enemy_health_text;
}

void BattleRoom::Start()
{

}

void BattleRoom::Update(double delta_time)
{
	switch (turn)
	{
		case Turn::PLAYER:
			player->Update(delta_time);
			for (Dice* dice : player_dices) {
				dice->Update(delta_time);
			}
			break;
		case Turn::ENEMY:
			enemy->Update(delta_time);
			break;
	}
}

void BattleRoom::Render(SDL_Renderer* renderer)
{
	RenderBackground(renderer);

	player->Render(renderer);
	enemy->Render(renderer);

	for (Dice* dice : player_dices)
	{
		dice->Render(renderer);
	}

	player_health_text->Render(renderer);
	player_mana_text->Render(renderer);
	enemy_health_text->Render(renderer);
}

void BattleRoom::ClearRoom()
{

}

void BattleRoom::ConfigureRoom()
{
	dice_hand_initial_position = glm::vec2(96, screen_height - 96);
	dice_hand_separation_between_dices = 96;

	player_position = glm::vec2(screen_width / 5, screen_height / 2.5);
	enemy_position = glm::vec2(screen_width - (screen_width / 5), screen_height / 2.5);

	turn = Turn::PLAYER;
	
	player_health_text = nullptr;
	player_mana_text = nullptr;
	enemy_health_text = nullptr;

	player_health_text = new Text(player_position + glm::vec2(0, 128), glm::vec2(0.25), "100/100", "arial-font", assets_manager);
	player_mana_text = new Text(player_position + glm::vec2(0, 160), glm::vec2(0.25), "100/100", "arial-font", assets_manager);
	enemy_health_text = new Text(enemy_position + glm::vec2(-24, 128), glm::vec2(0.25), "100/100", "arial-font", assets_manager);

	player = new Player(player_position, glm::vec2(1.5), 0.0, "guys", 128, 128, 0, Color(255, 255, 255, 255),
		false, assets_manager, random, player_health_text, player_mana_text);

	enemy = new Enemy(enemy_position, glm::vec2(1.5), 0.0, "guys", 128, 128, 0, Color(255, 255, 255, 255),
		false, assets_manager, enemy_health_text, random);

	std::vector<PlayerDice*> player_draw_dices = player->DrawDices();

	for (int i = 0; i < player_draw_dices.size(); i++)
	{
		DiceInfo* player_dice_info = player_draw_dices[i]->GetDiceInfo();

		Dice* dice = new Dice(player_dice_info->GetDiceName(), dice_hand_initial_position + glm::vec2(dice_hand_separation_between_dices * i, 0),
			glm::vec2(1), 0.0, player_dice_info->GetDiceName(), 64, 64, 0, Color(255, 255, 255, 255), false, assets_manager, 25,
			glm::vec2(screen_width / 2, screen_height / 2), 150, random, player_dice_info);

		player_dices.push_back(dice);
	}
}

void BattleRoom::RenderBackground(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(asset_id);

	SDL_Rect src = texture->GetSourceRect();

	float real_width = width * scale.x;
	float real_height = height * scale.y;

	SDL_Rect dest = {
		static_cast<int>(position.x - (real_width / 2)),
		static_cast<int>(position.y - (real_height / 2)),
		static_cast<int>(real_width),
		static_cast<int>(real_height)
	};

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RendererFlip flip = flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, rotation, NULL, flip);
}

Turn BattleRoom::GetTurn() { return turn; }

void BattleRoom::SetTurn(Turn new_turn) { turn = new_turn; }

void BattleRoom::AttackPlayer(int damage)
{

}

void BattleRoom::ShieldPlayer(int defense)
{

}

void BattleRoom::AttackEnemy(int damage)
{
	Logger::Log("ATTACKING FUCKING ENEMY");
}