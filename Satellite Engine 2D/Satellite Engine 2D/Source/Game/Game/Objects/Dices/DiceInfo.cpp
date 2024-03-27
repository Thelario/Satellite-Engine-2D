#include "DiceInfo.h"

#include "../../../../Engine/Logger/Logger.h"

DiceInfo::DiceInfo(std::string dice_name, int mana_cost)
{
	this->dice_name = dice_name;
	this->mana_cost = mana_cost;
}

std::string DiceInfo::GetDiceName() { return dice_name; }

int DiceInfo::GetManaCost() { return mana_cost; }

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

int DiceInfo::GetFacesSize() { return faces.size(); }

void DiceInfo::PrintFaces()
{
	Logger::Log("Dice: " + dice_name);

	for (Face* face : faces)
	{
		face->PrintFace();
	}
}
