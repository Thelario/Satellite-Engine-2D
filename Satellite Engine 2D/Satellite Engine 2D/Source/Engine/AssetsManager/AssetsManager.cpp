#include "AssetsManager.h"

#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "../Utils/json.hpp"
#include "../Logger/Logger.h"

using json = nlohmann::json;

AssetsManager::AssetsManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;

	if (LoadAssets() == true)
	{
		Logger::Log("Assets Manager created!");
	}
	else
	{
		Logger::Log("Assets Manager created with errors!! BE CAREFUL!!!");
	}
}

AssetsManager::~AssetsManager()
{
	ClearAssets();

	Logger::Log("Assets Manager destroyed!");
}

bool AssetsManager::LoadAssets()
{
	// Loading textures

	const std::string& config_file_name = "./Config/textures_config.json";

	std::ifstream file;

	file.open(config_file_name);

	if (file.fail() == true)
	{
		Logger::Error("Failed to open file: " + config_file_name);
		return false;
	}

	json json_data = json::parse(file);

	std::string file_path = "./Assets/Images/";

	for (const auto& texture_json : json_data["textures"])
	{
		std::string texture_file_path = file_path + texture_json["name"].get<std::string>();

		SDL_Texture* texture = GenerateTexture(texture_file_path);

		Texture* my_texture = new Texture(texture, texture_json["width"], texture_json["height"], texture_json["tile_size"]);

		textures.emplace(texture_json["asset_id"], my_texture);
	}

	file.close();

	// Loading fonts

	AddFont("arial-font", "./Assets/Fonts/arial.ttf", 100);
	AddFont("charriot-font", "./Assets/Fonts/charriot.ttf", 100);

	return true;
}

void AssetsManager::ClearAssets()
{
	for (auto texture : textures)
	{
		delete texture.second;
	}

	textures.clear();

	for (auto font : fonts)
	{
		TTF_CloseFont(font.second);
	}

	fonts.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Textures
//////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture* AssetsManager::GenerateTexture(const std::string& file_path)
{
	// Create a surface based on the imgage file in the file path specified

	SDL_Surface* surface = IMG_Load(file_path.c_str());

	if (surface == NULL)
	{
		Logger::Error("A problem occured when loading image with in file path " + file_path, SDL_GetError());
		return nullptr;
	}

	// Created a texture based on the 

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
	{
		Logger::Error("A problem occured when creating a texture from image in file path " + file_path, SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return texture;
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

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Fonts
//////////////////////////////////////////////////////////////////////////////////////////////////////

void AssetsManager::AddFont(const std::string& asset_id, const std::string& file_path, int font_size)
{
	fonts.emplace(asset_id, TTF_OpenFont(file_path.c_str(), font_size));
}

TTF_Font* AssetsManager::GetFont(const std::string& asset_id) const
{
	if (fonts.find(asset_id) == fonts.end())
	{
		Logger::Error("Trying to get a font with a wrong asset id: " + asset_id);
		return nullptr;
	}

	return fonts.at(asset_id);
}
