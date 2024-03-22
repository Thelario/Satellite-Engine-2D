#include "Scene.h"
#include "../Logger/Logger.h"

Scene::Scene(int scene_id, SDL_Renderer* renderer)
{
	this->scene_id = scene_id;
	this->renderer = renderer;
}

Scene::~Scene()
{
	for (int i = 0; i < game_objects.size(); i++)
	{
		delete game_objects[i];
	}

	game_objects.clear();
}

void Scene::Start()
{
	Logger::Log("Starting scene " + std::to_string(scene_id));

	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Start();
	}
}

void Scene::Update()
{
	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Update();
	}
}

void Scene::Render()
{
	for (int i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Render(renderer);
	}
}

void Scene::Clear()
{
	Logger::Log("Clearing scene " + std::to_string(scene_id));
}