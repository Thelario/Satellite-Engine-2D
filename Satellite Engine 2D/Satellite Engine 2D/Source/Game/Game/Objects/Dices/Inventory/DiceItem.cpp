#include "DiceItem.h"
#include "../../../../../Engine/InputManager/InputManager.h"

DiceItem::DiceItem(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& asset_id,
	int width, int height, int z_index, Color color, bool flip_x, AssetsManager* assets_manager, DiceInfo* dice_info)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->dice_info = dice_info;
}

void DiceItem::Start() { }

void DiceItem::Update(double delta_time)
{
	CheckMouseOverItem();
}

void DiceItem::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Face* face = dice_info->GetFace(0);
	Texture* texture = assets_manager->GetTexture(face->asset_id);
	SDL_Rect src = texture->GetTileSourceRect(face->image_id);

	float real_width = width * scale.x;
	float real_height = height * scale.y;

	SDL_Rect dest = {
		static_cast<int>(position.x - (real_width / 2)),
		static_cast<int>(position.y - (real_height / 2)),
		static_cast<int>(real_width),
		static_cast<int>(real_height)
	};

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RendererFlip flip = flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void DiceItem::CheckMouseOverItem()
{
	glm::vec2 mouse_position = InputManager::GetMousePosition();

	float half_width_x = (width * scale.x) / 2;
	float half_height_y = (height * scale.y) / 2;

	bool mouse_over_dice = (position.x - half_width_x  < mouse_position.x&&
		position.x + half_width_x  > mouse_position.x &&
		position.y - half_height_y < mouse_position.y&&
		position.y + half_height_y > mouse_position.y);

	if (mouse_over_dice == false)
	{
		scale = glm::vec2(1);
		return;
	}

	scale = glm::vec2(1.2f);
}