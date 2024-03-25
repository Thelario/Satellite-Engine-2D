#include "DiceInfo.h"

#include "../../../../Engine/Logger/Logger.h"

DiceInfo::DiceInfo(std::string dice_name)
{
	this->dice_name = dice_name;
}

std::string DiceInfo::GetDiceName() { return dice_name; }

void DiceInfo::AddFace(Face* face)
{
	faces.push_back(face);
}

Face* DiceInfo::GetFace(int face)
{
	if (face >= faces.size()) {
		Logger::Error("Trying to get a face bigger than the size of faces.");
		return nullptr;
	}

	return faces[face];
}

std::vector<Face*> DiceInfo::GetFaces() { return faces; }

void DiceInfo::PrintFaces()
{
	Logger::Log("Dice: " + dice_name);

	for (Face* face : faces)
	{
		face->PrintFace();
	}
}
