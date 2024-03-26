#pragma once

#include "DiceInfo.h"

class PlayerDice
{
	private:
		DiceInfo* dice_info;
		bool in_hand;

	public:
		PlayerDice(std::string dice_id, bool in_hand = false);

		DiceInfo* GetDiceInfo();
		bool IsInHand();
		void SetInHand(bool is_in_hand);
};