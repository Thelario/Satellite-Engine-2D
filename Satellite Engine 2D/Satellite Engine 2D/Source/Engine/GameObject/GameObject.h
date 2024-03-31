#pragma once

#include <glm/glm.hpp>
#include <string>
#include "../AssetsManager/AssetsManager.h"
#include "../Utils/Color.h"

class GameObject
{
	protected:

		// Transform data

		glm::vec2 position;
		glm::vec2 scale;
		double rotation;

		// Sprite data

		std::string asset_id;
		int width;
		int height;
		int z_index;
		bool flip_x;
		Color color;
		AssetsManager* assets_manager;

	public:
		GameObject(glm::vec2 position = glm::vec2(0), glm::vec2 scale = glm::vec2(0), double rotation = 0,
			const std::string& asset_id = "", int width = 0, int height = 0, int z_index = 0,
			Color color = Color(255, 255, 255, 255),bool flip_x = false, AssetsManager* assets_manager = nullptr);
		
		virtual ~GameObject() = default;

		virtual void Start();
		virtual void Update(double delta_time);
		virtual void Render(SDL_Renderer* renderer);

		virtual void SetPosition(glm::vec2 position);
};