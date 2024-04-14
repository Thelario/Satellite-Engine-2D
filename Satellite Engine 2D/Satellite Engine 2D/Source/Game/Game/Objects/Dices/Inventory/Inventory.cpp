#include "Inventory.h"

Inventory::Inventory(glm::vec2 position, glm::vec2 scale, double rotation, const std::string& asset_id, int width, int height,
	int z_index, Color color, bool flip_x, AssetsManager* assets_manager, int screen_width, int screen_height, DicesManager* dices_manager)
	: GameObject(position, scale, rotation, asset_id, width, height, z_index, color, flip_x, assets_manager)
{
	this->screen_width = screen_width;
	this->screen_height = screen_height;
	this->dices_manager = dices_manager;
	this->dice_stand = new DiceStand(assets_manager);

	this->dices_position = glm::vec2(64, 64);
	this->distance_between_items = 96;

	int i = 0;
	int j = 0;
	for (std::pair<std::string, DiceInfo*> dice_info : dices_manager->GetDices())
	{
		glm::vec2 new_position = dices_position + glm::vec2(i * distance_between_items, j * distance_between_items);

		if (new_position.x >= screen_width)
		{
			i = 0;
			j++;
			new_position = dices_position + glm::vec2(i * distance_between_items, j * distance_between_items);
		}

		DiceItem* dice_item = new DiceItem(new_position, glm::vec2(1), 0.0, dice_info.second->GetDiceName(), 64, 64, 0,
			Color(255, 255, 255, 255), false, assets_manager, dice_info.second);
		
		dice_items.push_back(dice_item);

		i++;
	}
}

Inventory::~Inventory()
{
	delete dice_stand;

	for (auto i = 0; i < dice_items.size(); i++) {
		delete dice_items[i];
	}
}

void Inventory::Start()
{
	for (auto i = 0; i < dice_items.size(); i++) {
		dice_items[i]->Start();
	}
}

void Inventory::Update(double delta_time)
{
	for (auto i = 0; i < dice_items.size(); i++) {
		dice_items[i]->Update(delta_time);
	}
}

void Inventory::Render(SDL_Renderer* renderer)
{
	RenderBackground(renderer);

	for (auto i = 0; i < dice_items.size(); i++) {
		dice_items[i]->Render(renderer);
	}
}

void Inventory::RenderBackground(SDL_Renderer* renderer)
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
