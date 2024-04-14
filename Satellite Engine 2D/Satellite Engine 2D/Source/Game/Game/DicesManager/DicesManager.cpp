#include "DicesManager.h"

#include <iostream>
#include <fstream>

#include "../../../Engine/Utils/json.hpp"
#include "../../../Engine/Logger/Logger.h"

using json = nlohmann::json;

std::map<std::string, DiceInfo*> DicesManager::dices = { };

DicesManager::DicesManager(FacesManager* faces_manager, AssetsManager* assets_manager, Random* random)
{
	this->faces_manager = faces_manager;
	this->assets_manager = assets_manager;
	this->random = random;

	if (LoadDices() == true)
	{
		Logger::Log("Dices Manager successfully created!!!");
	}
	else
	{
		Logger::Error("A problem occured when loading the dices!!!");
	}
}

DicesManager::~DicesManager()
{
	ClearDices();
}

bool DicesManager::LoadDices()
{
	if (faces_manager == nullptr)
	{
		Logger::Error("Faces Manager in Dices Manager is nullptr!!!");
		return false;
	}

	const std::string& config_file_name = "./Config/dices_config.json";

	std::ifstream file;

	file.open(config_file_name);

	if (file.fail() == true)
	{
		Logger::Error("Failed to open file: " + config_file_name);
		return false;
	}

	json json_data = json::parse(file);

	for (const auto& dice_json : json_data["dices"])
	{
		std::string dice_name = dice_json["name"];

		DiceInfo* dice = new DiceInfo(dice_name, dice_json["mana_cost"]);

		for (const auto& face_name : dice_json["faces"])
		{
			dice->AddFace(faces_manager->GetFace(face_name));
		}

		dices.emplace(dice_name, dice);
	}

	for (auto iterator : dices)
	{
		iterator.second->PrintFaces();
	}

	file.close();

	return true;
}

void DicesManager::ClearDices()
{
	for (auto dice : dices)
	{
		delete dice.second;
	}

	dices.clear();
}

std::map<std::string, DiceInfo*> DicesManager::GetDices() const
{
	return dices;
}

DiceInfo* DicesManager::GetDice(const std::string& dice_name)
{
	if (dices.find(dice_name) == dices.end())
	{
		Logger::Error("Trying to get a dice with a wrong name: " + dice_name);
		return nullptr;
	}

	return dices.at(dice_name);
}