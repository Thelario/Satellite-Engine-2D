#include "BattleRoom.h"

void BattleRoom::Start() { }

void BattleRoom::Update()
{

}

void BattleRoom::Render(SDL_Renderer* renderer)
{
	// Render room background

	// Render player and enemy

	// Render hand of dices
}

void BattleRoom::ConfigureRoom(GameObject* player, GameObject* enemy)
{
	this->player = player;
	this->enemy = enemy;

	
}