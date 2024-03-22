#include "AssetsManager.h"
#include <SDL_image.h>
#include "../Logger/Logger.h"

AssetsManager::AssetsManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	Logger::Log("Assets Manager created!");
}

AssetsManager::~AssetsManager()
{
	ClearAssets();

	Logger::Log("Assets Manager destroyed!");
}

void AssetsManager::ClearAssets()
{
	for (auto texture : textures)
	{
		delete texture.second;
	}

	textures.clear();
}

void AssetsManager::AddTexture(const std::string& asset_id, const std::string& file_path, int tile_size)
{
	// Create a surface based on the imgage file in the file path specified

	SDL_Surface* surface = IMG_Load(file_path.c_str());

	if (surface == NULL)
	{
		Logger::Error("A problem occured when loading image with " + asset_id + " in file path " + file_path, SDL_GetError());
		return;
	}

	// Created a texture based on the 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		Logger::Error("A problem occured when creating a texture from image with " + asset_id + " in file path " + file_path, SDL_GetError());
		return;
	}

	Texture* my_texture = new Texture(texture, surface->w, surface->h, tile_size);

	SDL_FreeSurface(surface);

	textures.emplace(asset_id, my_texture);
}

Texture* AssetsManager::GetTexture(const std::string& asset_id) const
{
	if (textures.find(asset_id) == textures.end())
	{
		Logger::Error("Trying to get a texture with a wrong asset id: " + asset_id);
		return nullptr;
	}

	return textures.at(asset_id);
}