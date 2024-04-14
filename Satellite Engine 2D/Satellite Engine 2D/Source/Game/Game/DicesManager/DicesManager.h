#pragma once

#include <map>
#include <string>

#include "../../../Engine/AssetsManager/AssetsManager.h"
#include "../../../Engine/Utils/Random.h"

#include "../FacesManager/FacesManager.h"
#include "../Objects/Dices/DiceInfo.h"

class DicesManager
{
	private:
		static std::map<std::string, DiceInfo*> dices;

		FacesManager* faces_manager;
		AssetsManager* assets_manager;
		Random* random;

	public:
		DicesManager(FacesManager* faces_manager, AssetsManager* assets_manager, Random* random);
		~DicesManager();

		bool LoadDices();
		void ClearDices();

		std::map<std::string, DiceInfo*> GetDices() const;

		static DiceInfo* GetDice(const std::string& dice_name);
};