#include "BattleRoom.h"

#include "Player.h"

Turn BattleRoom::turn = Turn::PLAYER;

BattleRoom::BattleRoom(glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager, int screen_width, int screen_height)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;

	ConfigureRoom();
}

BattleRoom::~BattleRoom()
{
	delete player;
	delete enemy;
}

void BattleRoom::Start()
{

}

void BattleRoom::Update()
{
	player->Update();
	enemy->Update();
}

void BattleRoom::Render(SDL_Renderer* renderer)
{
	RenderBackground(renderer);

	player->Render(renderer);
	enemy->Render(renderer);

	// Render hand of dices
}

void BattleRoom::ClearRoom()
{

}

void BattleRoom::ConfigureRoom()
{
	dice_hand_initial_position = glm::vec2(32, screen_height - 32);
	dice_hand_separation_between_dices = 32;

	player_position = glm::vec2(screen_width / 4, screen_height / 2);
	enemy_position = glm::vec2(screen_width - (screen_width / 4), screen_height / 2);

	turn = Turn::PLAYER;

	player = new Player();
	enemy = new GameObject();
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

}