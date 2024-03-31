#include "GameObject.h"
#include "../InputManager/InputManager.h"

GameObject::GameObject(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& asset_id,
	int width, int height, int z_index, Color color, bool flip_x, AssetsManager* assets_manager)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	this->asset_id = asset_id;
	this->width = width;
	this->height = height;
	this->z_index = z_index;
	this->color = color;
	this->flip_x = flip_x;
	this->assets_manager = assets_manager;
}

void GameObject::Start() { }

void GameObject::Update(double delta_time) { }

void GameObject::Render(SDL_Renderer* renderer)
{
	if (assets_manager == nullptr) {
		return;
	}

	Texture* texture = assets_manager->GetTexture(asset_id);

	SDL_Rect src = texture->GetSourceRect();

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

void GameObject::SetPosition(glm::vec2 position)
{
	this->position = position;
}