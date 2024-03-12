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

void AssetsManager::AddTexture(const std::string& assetId, const std::string& filePath, int tileSize)
{
	// Create a surface based on the imgage file in the file path specified

	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (surface == NULL)
	{
		Logger::Error("A problem occured when loading image with " + assetId + " in file path " + filePath, SDL_GetError());
		return;
	}

	// Created a texture based on the 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		Logger::Error("A problem occured when creating a texture from image with " + assetId + " in file path " + filePath, SDL_GetError());
		return;
	}

	Texture* myTexture = new Texture(texture, surface->w, surface->h, tileSize);

	SDL_FreeSurface(surface);

	textures.emplace(assetId, myTexture);
}

Texture* AssetsManager::GetTexture(const std::string& assetId) const
{
	if (textures.find(assetId) == textures.end())
	{
		Logger::Error("Trying to get a texture with a wrong asset id: " + assetId);
		return nullptr;
	}

	return textures.at(assetId);
}