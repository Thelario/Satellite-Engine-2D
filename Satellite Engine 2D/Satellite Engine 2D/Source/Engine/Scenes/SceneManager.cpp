#include "SceneManager.h"

#include "../InputManager/InputManager.h"
#include "../Logger/Logger.h"

SceneManager::SceneManager(SDL_Renderer* renderer)
{
	current_scene = 0;

	this->renderer = renderer;
}

SceneManager::~SceneManager()
{
	for (auto i = 0; i < scenes.size(); i++)
	{
		delete scenes[i];
	}

	scenes.clear();
}

void SceneManager::Start(std::vector<std::vector<GameObject*>> scenes_game_objects)
{
	for (int i = 0; i < scenes_game_objects.size(); i++)
	{
		Scene* scene = new Scene(0, renderer, scenes_game_objects[i]);
		scenes.push_back(scene);
	}

	scenes[current_scene]->Start();
}

void SceneManager::Update()
{
	scenes[current_scene]->Update();
}

void SceneManager::Render()
{
	scenes[current_scene]->Render();
}

void SceneManager::ChangeScene(int newScene)
{
	scenes[current_scene]->Clear();

	current_scene = newScene;

	scenes[current_scene]->Start();
}

int SceneManager::GetCurrentScene() { return current_scene; }