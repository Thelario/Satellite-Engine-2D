#include "Player.h"

#include "../../../Engine/Logger/Logger.h"

Player::Player( glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager, Random* random, Text* health_text, Text* mana_text)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->current_health = 100;
	this->max_health = 100;

	this->current_mana = 4;
	this->max_mana = 4;

	this->current_hand_size = 0;
	this->max_hand_size = 4;

	this->random = random;
	this->health_text = health_text;
	this->mana_text = mana_text;

	if (health_text != nullptr)
		this->health_text->SetText("H:" + std::to_string(current_health) + "/" + std::to_string(max_health));

	if (mana_text != nullptr)
		this->mana_text->SetText("M:" + std::to_string(current_mana) + "/" + std::to_string(max_mana));

	PlayerDice* player_dice_one = new PlayerDice("dice-basic-attack", false);
	PlayerDice* player_dice_two = new PlayerDice("dice-basic-attack", false);
	PlayerDice* player_dice_three = new PlayerDice("dice-basic-attack", false);
	PlayerDice* player_dice_four = new PlayerDice("dice-basic-deffense", false);
	PlayerDice* player_dice_five = new PlayerDice("dice-basic-deffense", false);
	PlayerDice* player_dice_six = new PlayerDice("dice-basic-deffense", false);

	this->dice_inventory.push_back(player_dice_one);
	this->dice_inventory.push_back(player_dice_two);
	this->dice_inventory.push_back(player_dice_three);
	this->dice_inventory.push_back(player_dice_four);
	this->dice_inventory.push_back(player_dice_five);
	this->dice_inventory.push_back(player_dice_six);
}

Player::~Player()
{
	for (PlayerDice* player_dice : dice_inventory)
	{
		delete player_dice;
	}
}

void Player::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(asset_id);

	SDL_Rect src = texture->GetTileSourceRect(0);

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

std::vector<PlayerDice*> Player::DrawDices()
{
	if (random == nullptr)
	{
		Logger::Error("The player tried to retrieve random X dices and failed because random is nullptr (not initialized).");
		return std::vector<PlayerDice*>();
	}

	std::vector<PlayerDice*> dices_to_draw;

	while (current_hand_size < max_hand_size)
	{
		int dice = -1;
		PlayerDice* player_dice = nullptr;
		
		do {
			dice = random->GenerateRandomInteger(0, static_cast<int>(dice_inventory.size()) - 1);
			player_dice = dice_inventory[dice];
		}
		while (player_dice->IsInHand() == true);
		
		current_hand_size++;
		player_dice->SetInHand(true);
		dices_to_draw.push_back(player_dice);
	}

	return dices_to_draw;
}