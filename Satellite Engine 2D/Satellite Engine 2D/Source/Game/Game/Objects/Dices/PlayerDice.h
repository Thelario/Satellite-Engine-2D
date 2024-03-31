#pragma once

#include "DiceInfo.h"

class PlayerDice
{
	private:
		DiceInfo* dice_info;
		bool in_hand;

	public:
		PlayerDice(const std::string& dice_id, bool in_hand = false);

		DiceInfo* GetDiceInfo() const;
		bool IsInHand() const;
		void SetInHand(bool is_in_hand);
};