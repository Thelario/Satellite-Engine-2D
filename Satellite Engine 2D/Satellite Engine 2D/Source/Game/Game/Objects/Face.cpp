#include "Face.h"

#include "BattleRoom.h"

Face::Face(std::string asset_id, unsigned int image_id, FaceType face_type, int value)
{
	this->asset_id = asset_id;
	this->image_id = image_id;
	this->face_type = face_type;
	this->value = value;
}

void Face::UseFace()
{
	switch (face_type)
	{
		case FaceType::ATTACK:
			BattleRoom::AttackEnemy(value);
			break;
		case FaceType::DEFENSE:
			BattleRoom::ShieldPlayer(value);
			break;
		default:
			break;
	}
}