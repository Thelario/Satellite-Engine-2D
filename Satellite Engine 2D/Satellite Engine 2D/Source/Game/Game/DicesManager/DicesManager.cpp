#include "DicesManager.h"

#include "../../../Engine/Logger/Logger.h"

DicesManager::DicesManager()
{
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

Dice* DicesManager::GetDice(const std::string& dice_name) const
{
	if (dices.find(dice_name) == dices.end())
	{
		Logger::Error("Trying to get a dice with a wrong name: " + dice_name);
		return nullptr;
	}

	return dices.at(dice_name);
}