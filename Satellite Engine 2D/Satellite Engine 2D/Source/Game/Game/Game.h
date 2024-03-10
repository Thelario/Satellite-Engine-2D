#pragma once

#include <SDL.h>

class Game
{
	private:
		bool isRunning;
		bool debug;

		SDL_Window* window;
		SDL_Renderer* renderer;

		void Initialize();
		void ProcessInput();
		void Update();
		void Render();

	public:
		Game();
		~Game();

		void Run();
		void Destroy();
};