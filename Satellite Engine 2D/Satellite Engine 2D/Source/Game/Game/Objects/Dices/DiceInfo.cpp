#include "DiceInfo.h"

#include "../../../../Engine/Logger/Logger.h"

DiceInfo::DiceInfo(const std::string& dice_name, int mana_cost)
{
	this->dice_name = dice_name;
	this->mana_cost = mana_cost;
}

const std::string& DiceInfo::GetDiceName() const { return dice_name; }

int DiceInfo::GetManaCost() const { return mana_cost; }

void DiceInfo::AddFace(Face* face)
{
	faces.push_back(face);
}

Face* DiceInfo::GetFace(int face) const
{
	if (face >= faces.size()) {
		Logger::Error("Trying to get a face bigger than the size of faces.");
		return nullptr;
	}

	return faces[face];
}

std::vector<Face*> DiceInfo::GetFaces() const { return faces; }

const int DiceInfo::GetFacesSize() const { return faces.size(); }

void DiceInfo::PrintFaces()
{
	Logger::Log("Dice: " + dice_name);

	for (Face* face : faces)
	{
		face->PrintFace();
	}
}
