#include "Scene.h"

#include "../Logger/Logger.h"

Scene::Scene(int scene_id, SDL_Renderer* renderer, std::vector<GameObject*> game_objects)
{
	this->scene_id = scene_id;
	this->renderer = renderer;
	this->game_objects = game_objects;

	// TODO: Instead of passing the objects through parameter,
	// it would be nice to actually load all objects containing a scene from a config file.
}

Scene::~Scene()
{
	/*
	for (auto i = 0; i < game_objects.size(); i++)
	{
		delete game_objects[i];
	}
	*/

	game_objects.clear();
}

void Scene::Start()
{
	Logger::Log("Starting scene " + std::to_string(scene_id));

	for (auto i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Start();
	}
}

void Scene::Update()
{
	for (auto i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Update();
	}
}

void Scene::Render()
{
	for (auto i = 0; i < game_objects.size(); i++)
	{
		game_objects[i]->Render(renderer);
	}
}

void Scene::Clear()
{
	Logger::Log("Clearing scene " + std::to_string(scene_id));
}