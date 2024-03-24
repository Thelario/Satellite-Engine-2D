#include "FacesManager.h"

#include <iostream>
#include <fstream>

#include "../../../Engine/Utils/json.hpp"
#include "../../../Engine/Logger/Logger.h"

using json = nlohmann::json;

FacesManager::FacesManager()
{
	if (LoadFaces() == true)
	{
		Logger::Log("Faces Manager successfully created!!!");
	}
	else
	{
		Logger::Error("A problem occured when loading the faces!!!");
	}
}

FacesManager::~FacesManager()
{
	ClearFaces();
}

bool FacesManager::LoadFaces()
{
	const std::string& config_file_name = "./Config/game_config.json";

	std::ifstream file;

	file.open(config_file_name);

	if (file.fail() == true)
	{
		Logger::Error("Failed to open file: " + config_file_name);
		return false;
	}

	json json_data = json::parse(file);

	for (const auto& face : json_data["faces"])
	{
		Face* new_face = new Face(face["asset_id"], face["image_id"], face["face_type"], face["value"]);

		faces.emplace(face["name"], new_face);
	}

	for (auto iterator : faces)
	{
		iterator.second->PrintFace();
	}

	file.close();

	json_data.clear();

	return true;
}

void FacesManager::ClearFaces()
{
	for (auto face : faces)
	{
		delete face.second;
	}

	faces.clear();
}

Face* FacesManager::GetFace(const std::string& face_name) const
{
	if (faces.find(face_name) == faces.end())
	{
		Logger::Error("Trying to get a face with a wrong name: " + face_name);
		return nullptr;
	}

	return faces.at(face_name);
}