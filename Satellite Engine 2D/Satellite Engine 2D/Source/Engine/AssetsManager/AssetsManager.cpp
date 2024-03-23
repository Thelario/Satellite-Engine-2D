#include "AssetsManager.h"
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include "../Logger/Logger.h"
#include "json.hpp"

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
	const std::string& file_name = "../../../Config/game_config.json";

	std::ifstream file(file_name);

	if (file.is_open() == false)
	{
		Logger::Error("Failed to open file: " + file_name);
		return false;
	}
	
	json json_data;
	file >> json_data;
	/*
	for (const auto& face : json_data["faces"])
	{
		Face* new_face = new Face(face["asset_id"], face["image_id"], face["face_type"], face["value"]);

		faces.emplace(face["name"], new_face);

		Logger::Log("         ");
		Logger::Log("New face: " + face["name"]);
		Logger::Log("         ");
	}*/

	/*

	for (const auto& diceJson : jsonData["dices"])
	{
		Dice dice;
		dice.name = diceJson["name"];
		for (const auto& faceName : diceJson["faces"]) {
			for (const auto& face : jsonData["faces"]) {
				if (face["name"] == faceName) {
					Face newFace;
					newFace.name = face["name"];
					newFace.face_type = face["face_type"];
					newFace.asset_id = face["asset_id"];
					newFace.image_id = face["image_id"];
					newFace.value = face["value"];
					dice.faces.push_back(newFace);
					break;
				}
			}
		}
		dices.push_back(dice);
	}

	*/

	return true;
}

void AssetsManager::ClearAssets()
{
	// Clearing textures

	for (auto texture : textures)
	{
		delete texture.second;
	}

	textures.clear();

	// Clearing faces

	/*for (auto face : faces)
	{
		delete face.second;
	}

	faces.clear();

	// Clearing dices

	for (auto dice : dices)
	{
		delete dice.second;
	}

	dices.clear();*/
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
/*
void AssetsManager::AddFace(const std::string& face_name, Face* face)
{
	faces.emplace(face_name, face);
}

Face* AssetsManager::GetFace(const std::string& face_name) const
{
	if (faces.find(face_name) == faces.end())
	{
		Logger::Error("Trying to get a face with a wrong name: " + face_name);
		return nullptr;
	}

	return faces.at(face_name);
}

void AssetsManager::AddDice(const std::string& dice_name, Dice* dice)
{
	dices.emplace(dice_name, dice);
}

Dice* AssetsManager::GetDice(const std::string& dice_name) const
{
	if (dices.find(dice_name) == dices.end())
	{
		Logger::Error("Trying to get a dice with a wrong name: " + dice_name);
		return nullptr;
	}

	return dices.at(dice_name);
}*/