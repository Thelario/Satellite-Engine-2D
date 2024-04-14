#include "DiceStand.h"

DiceStand::DiceStand(AssetsManager* assets_manager)
{
	faces_size = 64;

	dice_stand_faces_position = {
		glm::vec2(100, 200), glm::vec2(200, 200), glm::vec2(300, 200),
		glm::vec2(400, 200), glm::vec2(200, 300), glm::vec2(200, 100)
	};

	current_dice_on_stand = nullptr;
	assets_manager = assets_manager;
}

void DiceStand::LoadStand(DiceInfo* dice_info)
{
	current_dice_on_stand = dice_info;
}

void DiceStand::ClearStand()
{
	current_dice_on_stand = nullptr;
}

void DiceStand::Render(SDL_Renderer* renderer)
{
	if (current_dice_on_stand == nullptr || assets_manager == nullptr) {
		return;
	}

	for (int i = 0; i < dice_stand_faces_position.size(); i++)
	{
		Face* face = current_dice_on_stand->GetFaces().at(i);
		Texture* texture = assets_manager->GetTexture(face->asset_id);
		SDL_Rect src = texture->GetTileSourceRect(face->image_id);

		SDL_Rect dest = {
			static_cast<int>(dice_stand_faces_position.at(i).x - (faces_size / 2)),
			static_cast<int>(dice_stand_faces_position.at(i).y - (faces_size / 2)),
			static_cast<int>(faces_size),
			static_cast<int>(faces_size)
		};

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
	}
}