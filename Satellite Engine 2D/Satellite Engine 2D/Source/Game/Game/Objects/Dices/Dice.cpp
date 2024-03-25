#include "Dice.h"

#include <SDL.h>

#include "../../../../Engine/InputManager/InputManager.h"
#include "../../../../Engine/Logger/Logger.h"

Dice::Dice(std::string name, glm::vec2 position, glm::vec2 scale, double rotation, std::string asset_id,
	int width, int height, int z_index, Color color, bool flip_x,
	AssetsManager* assets_manager, Uint32 time_rate, glm::vec2 screen_center, Uint32 time_rate_limit, Random* random)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->rotating_dice = false;
	this->using_dice = false;
	this->face = 0;
	this->selected_face = -1;
	this->move_speed = 25;
	this->time_rate_increase = 15;
	this->time_rate = time_rate;
	this->time_rate_limit = time_rate_limit;
	this->screen_center = screen_center;
	this->time = SDL_GetTicks();
	this->direction = screen_center - position;
	this->direction = glm::normalize(direction);
	this->random = random;
}

void Dice::Start() { }

void Dice::Update()
{
	if (InputManager::GetMouseButtonDown(1))
	{
		ResetDice();
	}

	if (using_dice == false)
	{
		CheckMouseOverDice();
	}
	else
	{
		UseDice();
	}
}

void Dice::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(dice_info->GetFace(face)->asset_id);

	SDL_Rect src = texture->GetTileSourceRect(dice_info->GetFace(face)->image_id);

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

void Dice::ResetDice()
{

}

void Dice::UseDice()
{
	/*
	if (selected_face == -1) // Calculate random face only first time
	{
		selected_face = random->GenerateRandomInteger(0, faces.size() - 1);
	}
	*/

	float distance = glm::distance(screen_center, position);

	if (glm::abs(distance) > 20) // Move the dice if not in center
	{
		position += move_speed * direction;
	}
	else
	{
		// If time rate limit reach, search for random face and stop when found

		if (time_rate >= time_rate_limit)
		{
			Logger::Log("Time rate limit reached. Selected face: " + std::to_string(selected_face) + ", current face: " + std::to_string(face));

			if (face == selected_face) {
				return;
			}
		}

		// If time rate imit not reached, keep animating dice throw

		Uint32 current_time = SDL_GetTicks();

		if (time + time_rate < current_time)
		{
			time = current_time;
			face = (face + 1) % 6;
			time_rate += time_rate_increase;
		}
	}
}

void Dice::CheckMouseOverDice()
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

	scale = glm::vec2(1.2f);

	// Check if the player presses the dice

	if (InputManager::GetMouseButtonDown(0))
	{
		using_dice = true;
		scale = glm::vec2(1);
	}
}