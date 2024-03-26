#include "PlayerDice.h"

#include "../../DicesManager/DicesManager.h"

PlayerDice::PlayerDice(std::string dice_id, bool in_hand)
{
	this->dice_info = DicesManager::GetDice(dice_id);
	this->in_hand = in_hand;
}

DiceInfo* PlayerDice::GetDiceInfo() { return dice_info; }

bool PlayerDice::IsInHand() { return in_hand; }

void PlayerDice::SetInHand(bool is_in_hand) { in_hand = is_in_hand; }