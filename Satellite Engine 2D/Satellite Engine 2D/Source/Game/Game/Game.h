#pragma once

#include <SDL.h>
#include "../../Engine/AssetsManager/AssetsManager.h"

class Game
{
	private:
		bool isRunning;
		bool debug;

		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetsManager* assetsManager;

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