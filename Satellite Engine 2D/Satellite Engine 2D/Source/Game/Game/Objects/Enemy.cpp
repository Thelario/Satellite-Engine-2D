#include "Enemy.h"

Enemy::Enemy(glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	current_health = 100;
	max_health = 100;
}

void Enemy::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(asset_id);

	SDL_Rect src = texture->GetTileSourceRect(1);

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