#pragma once

#include <SDL.h>
#include <vector>
#include "../../Engine/AssetsManager/AssetsManager.h"
#include "../../Engine/GameObject/GameObject.h"

class Game
{
	private:
		bool isRunning;
		bool debug;

		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetsManager* assetsManager;
		std::vector<GameObject*> gameObjects;

		void Initialize();
		void Setup();
		void ProcessInput();
		void Update();
		void Render();

	public:
		Game();
		~Game();

		void Run();
		void Destroy();
};