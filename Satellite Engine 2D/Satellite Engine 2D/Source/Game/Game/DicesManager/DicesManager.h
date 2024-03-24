#pragma once

#include <map>
#include <string>

#include "../FacesManager/FacesManager.h"
#include "../Objects/Dice.h"

class DicesManager
{
	private:
		std::map<std::string, Dice*> dices;

		FacesManager* faces_manager;
		AssetsManager* assets_manager;

	public:
		DicesManager(FacesManager* faces_manager, AssetsManager* assets_manager);
		~DicesManager();

		bool LoadDices();
		void ClearDices();

		Dice* GetDice(const std::string& dice_name) const;
};