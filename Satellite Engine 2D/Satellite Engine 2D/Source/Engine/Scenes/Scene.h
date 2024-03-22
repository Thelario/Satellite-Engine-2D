#pragma once

#include <vector>
#include "../GameObject/GameObject.h"

class Scene
{
	private:
		int scene_id;
		std::vector<GameObject*> game_objects;
		SDL_Renderer* renderer;

	public:
		Scene(int scene_id, SDL_Renderer* renderer);
		~Scene();

		void Start();
		void Update();
		void Render();
		void Clear();
};