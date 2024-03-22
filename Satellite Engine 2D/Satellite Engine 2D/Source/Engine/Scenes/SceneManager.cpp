#include "SceneManager.h"
#include "../InputManager/InputManager.h"
#include "../Logger/Logger.h"

SceneManager::SceneManager(SDL_Renderer* renderer)
{
	current_scene = 0;

	this->renderer = renderer;

	Scene* sceneOne = new Scene(0, renderer);
	Scene* sceneTwo = new Scene(1, renderer);
	Scene* sceneThree = new Scene(2, renderer);

	scenes.push_back(sceneOne);
	scenes.push_back(sceneTwo);
	scenes.push_back(sceneThree);
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < scenes.size(); i++)
	{
		delete scenes[i];
	}

	scenes.clear();
}

void SceneManager::Start()
{
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