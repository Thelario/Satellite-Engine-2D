#pragma once

#include <map>
#include <string>

#include "../FacesManager/FacesManager.h"
#include "../Objects/Dices/DiceInfo.h"
#include "../../../Engine/AssetsManager/AssetsManager.h"
#include "../../../Engine/Utils/Random.h"

class DicesManager
{
	private:
		std::map<std::string, DiceInfo*> dices;

		FacesManager* faces_manager;
		AssetsManager* assets_manager;
		Random* random;

	public:
		DicesManager(FacesManager* faces_manager, AssetsManager* assets_manager, Random* random);
		~DicesManager();

		bool LoadDices();
		void ClearDices();

		DiceInfo* GetDice(const std::string& dice_name) const;
};