#include "Face.h"

#include "../BattleRoom.h"
#include "../../../../Engine/Logger/Logger.h"

Face::Face(std::string asset_id, unsigned int image_id, FaceType face_type, int level)
{
	this->asset_id = asset_id;
	this->image_id = image_id;
	this->face_type = face_type;
	this->level = level;
}

void Face::UseFace()
{
	switch (face_type)
	{
		case FaceType::ATTACK:
			//BattleRoom::AttackEnemy(value);
			break;
		case FaceType::DEFENSE:
			//BattleRoom::ShieldPlayer(value);
			break;
		default:
			break;
	}
}

void Face::PrintFace()
{
	std::string type = face_type == FaceType::ATTACK ? "Attack" : "Defense";

	Logger::Log("Face with " + asset_id + ", " + std::to_string(image_id) + ", " + std::to_string(level) + ", " + type);
}
