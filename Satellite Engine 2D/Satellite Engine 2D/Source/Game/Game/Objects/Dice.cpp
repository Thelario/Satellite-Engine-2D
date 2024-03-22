#include "Dice.h"
#include <SDL.h>
#include "../../../Engine/InputManager/InputManager.h"

Dice::Dice(glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id,
	int width, int height, int z_index, Color color, bool flip_x, AssetsManager* assets_manager, int face, Uint32 time_rate)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->using_dice = false;
	this->face = face;
	this->time_rate = time_rate;
	this->time = SDL_GetTicks();
}

void Dice::Start() { }

void Dice::Update()
{
	if (using_dice == false)
	{
		// Checking if mouse is over dice

		glm::vec2 mouse_position = InputManager::GetMousePosition();

		float half_width_x = (width * scale.x) / 2;
		float half_height_y = (height * scale.y) / 2;

		bool mouse_over_dice = (position.x - half_width_x  < mouse_position.x &&
								position.x + half_width_x  > mouse_position.x &&
								position.y - half_height_y < mouse_position.y &&
								position.y + half_height_y > mouse_position.y);

		if (mouse_over_dice == false)
		{
			scale = glm::vec2(1);
			return;
		}

		scale = glm::vec2(1.2);

		// Check if 
	}



	//glm::vec2 offset = glm::vec2((scale.x * width - scale.x) / 2, (scale.y * height - scale.y) / 2);

	//position -= offset;

	Uint32 current_time = SDL_GetTicks();

	if (time + time_rate < current_time)
	{
		time = current_time;
		face = (face + 1) % 6;
	}
}

void Dice::Render(SDL_Renderer* renderer)
{
	if (texture == nullptr) {
		return;
	}

	SDL_Rect src = texture->GetTileSourceRect(face);

	float width_x = width * scale.x;
	float height_y = height * scale.y;

	SDL_Rect dest = {
		static_cast<int>(position.x - (width_x / 2)),
		static_cast<int>(position.y - (height_y / 2)),
		static_cast<int>(width_x),
		static_cast<int>(height_y)
	};

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RendererFlip flip = flip_x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, rotation, NULL, flip);
}

void Dice::UseDice()
{

}