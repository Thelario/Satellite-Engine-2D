#pragma once

#include <vector>
#include "Scene.h"

class SceneManager
{
	private:
		int current_scene;
		std::vector<Scene*> scenes;
		SDL_Renderer* renderer;

	public:
		SceneManager(SDL_Renderer* renderer);
		~SceneManager();

		void Start();
		void Update();
		void Render();

		void ChangeScene(int newScene);
		int GetCurrentScene();
};