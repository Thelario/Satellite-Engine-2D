#include "GameObject.h"
#include "../InputManager/InputManager.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 scale, double rotation, std::string assetId,
	int width, int height, int zIndex, Color color, bool flipX, AssetsManager* assetsManager)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	this->assetId = assetId;
	this->width = width;
	this->height = height;
	this->zIndex = zIndex;
	this->color = color;
	this->flipX = flipX;

	if (assetsManager != nullptr) {
		texture = assetsManager->GetTexture(assetId);
	}
}

void GameObject::Start() { }

void GameObject::Update()
{

}

void GameObject::Render(SDL_Renderer* renderer)
{
	if (texture == nullptr) {
		return;
	}

	SDL_Rect src = texture->GetSourceRect();

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
