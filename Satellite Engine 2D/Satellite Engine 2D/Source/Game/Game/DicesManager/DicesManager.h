#pragma once

#include <map>
#include <string>

#include "../Objects/Dice.h"

class DicesManager
{
	private:
		std::map<std::string, Dice*> dices;

	public:
		DicesManager();
		~DicesManager();

		bool LoadDices();
		void ClearDices();

		Dice* GetDice(const std::string& dice_name) const;
};