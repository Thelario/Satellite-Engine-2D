#pragma once

#include "../../../Engine/GameObject/GameObject.h"

class Dice : public GameObject
{
	protected:
		int face;
		Uint32 timeRate;
		Uint32 time;

	public:
		Dice(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0, std::string assetId = "", int width = 0,
			int height = 0, int zIndex = 0, Color color = Color(255, 255, 255, 255), bool flipX = false, AssetsManager* assetsManager = nullptr,
			int face = 0, Uint32 timeRate = 0);

		void Start() override;
		void Update() override;
		void Render(SDL_Renderer* renderer) override;
};