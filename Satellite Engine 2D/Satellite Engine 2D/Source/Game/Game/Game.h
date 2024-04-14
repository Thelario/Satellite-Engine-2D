#pragma once

#include <SDL.h>
#include <vector>

#include "../../Engine/AssetsManager/AssetsManager.h"
#include "../../Engine/Scenes/SceneManager.h"
#include "../../Engine/Utils/Random.h"

#include "FacesManager/FacesManager.h"
#include "DicesManager/DicesManager.h"

class Game
{
	private:
		Uint32 milliseconds_previous_frame;
		double delta_time;

		bool is_running;
		bool debug;

		SDL_Window* window;
		SDL_Renderer* renderer;
		
		AssetsManager* assets_manager;
		SceneManager* scene_manager;
		FacesManager* faces_manager;
		DicesManager* dices_manager;
		
		Random* unrepeatable_random;
		Random* repeatable_random;

		GameObject* battle_room;
		GameObject* inventory;

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