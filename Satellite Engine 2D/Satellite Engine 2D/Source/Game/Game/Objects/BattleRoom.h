#pragma once

#include "../../../Engine/GameObject/GameObject.h"

class BattleRoom : public GameObject
{
	private:
		glm::vec2 player_position;
		glm::vec2 enemy_position;

		GameObject* player;
		GameObject* enemy;

	public:
		BattleRoom() = default;

		void Start() override;
		void Update() override;
		void Render(SDL_Renderer* renderer) override;

		void ConfigureRoom(GameObject* player, GameObject* enemy);
};