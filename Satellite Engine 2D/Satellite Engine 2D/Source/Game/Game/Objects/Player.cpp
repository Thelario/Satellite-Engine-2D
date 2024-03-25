#include "Player.h"

Player::Player( glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	current_health = 100;
	max_health = 100;

	current_mana = 2;
	max_mana = 2;

	current_hand_size = 4;
	max_hand_size = 4;
}