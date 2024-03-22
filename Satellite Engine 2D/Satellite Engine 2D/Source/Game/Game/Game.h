#pragma once

#include <SDL.h>
#include <vector>
#include "../Engine.h"

class Game
{
	private:
		bool is_running;
		bool debug;

		SDL_Window* window;
		SDL_Renderer* renderer;
		AssetsManager* assets_manager;
		SceneManager* scene_manager;
		std::vector<GameObject*> game_objects;

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