#include "PlayerDice.h"

#include "../../DicesManager/DicesManager.h"

PlayerDice::PlayerDice(const std::string& dice_id, bool in_hand)
{
	this->dice_info = DicesManager::GetDice(dice_id);
	this->in_hand = in_hand;
}

DiceInfo* PlayerDice::GetDiceInfo() const { return dice_info; }

bool PlayerDice::IsInHand() const { return in_hand; }

void PlayerDice::SetInHand(bool is_in_hand) { in_hand = is_in_hand; }