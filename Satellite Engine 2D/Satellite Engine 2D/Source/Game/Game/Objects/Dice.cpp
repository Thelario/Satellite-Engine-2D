#include "Dice.h"
#include <SDL.h>
#include "../../../Engine/InputManager/InputManager.h"

Dice::Dice(glm::vec2 position, glm::vec2 scale, double rotation, std::string assetId,
	int width, int height, int zIndex, Color color, bool flipX, AssetsManager* assetsManager, int face, Uint32 timeRate)
	: GameObject(position, scale, rotation, assetId, width, height, zIndex, color, flipX, assetsManager)
{
	this->face = face;
	this->timeRate = timeRate;
	this->time = SDL_GetTicks();
}

void Dice::Start() { }

void Dice::Update()
{
	glm::vec2 mousePosition = InputManager::GetMousePosition();

	float half_width_x = (width * scale.x) / 2;
	float half_height_y = (height * scale.y) / 2;

	bool mouseOverDice = (position.x - half_width_x  < mousePosition.x &&
						  position.x + half_width_x  > mousePosition.x &&
						  position.y - half_height_y < mousePosition.y &&
						  position.y + half_height_y > mousePosition.y);

	if (mouseOverDice == false)
	{
		scale = glm::vec2(1);
		return;
	}

	scale = glm::vec2(1.2);

	//glm::vec2 offset = glm::vec2((scale.x * width - scale.x) / 2, (scale.y * height - scale.y) / 2);

	//position -= offset;

	Uint32 currentTime = SDL_GetTicks();

	if (time + timeRate < currentTime)
	{
		time = currentTime;
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

	SDL_RendererFlip flip = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, rotation, NULL, flip);
}