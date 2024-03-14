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

	bool mouseOverDice = (position.x                    < mousePosition.x &&
						  position.x + width * scale.x  > mousePosition.x &&
						  position.y                    < mousePosition.y &&
						  position.y + height * scale.y > mousePosition.y);

	if (mouseOverDice == false)
	{
		scale = glm::vec2(1);
		return;
	}

	scale = glm::vec2(1.1);

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

	SDL_Rect dest = {
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(width * scale.x),
		static_cast<int>(height * scale.y)
	};

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RendererFlip flip = flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_RenderCopyEx(renderer, texture->GetTexture(), &src, &dest, rotation, NULL, flip);
}