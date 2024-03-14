#pragma once

#include <glm/glm.hpp>
#include <string>
#include "../AssetsManager/AssetsManager.h"
#include "../Utils/Color.h"

class GameObject
{
	protected:
		glm::vec2 position;
		glm::vec2 scale;
		double rotation;
		std::string assetId;
		int width;
		int height;
		int zIndex;
		bool flipX;
		Color color;
		Texture* texture;

	public:
		GameObject(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0, std::string assetId = "", int width = 0,
			int height = 0, int zIndex = 0, Color color = Color(255, 255, 255, 255), bool flipX = false, AssetsManager* assetsManager = nullptr);
		virtual ~GameObject() = default;

		virtual void Start();
		virtual void Update();
		virtual void Render(SDL_Renderer* renderer);
};