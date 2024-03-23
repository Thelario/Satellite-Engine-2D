#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include "../Rendering/Texture.h"

class AssetsManager
{
	private:
		SDL_Renderer* renderer;
		
		std::map<std::string, Texture*> textures;

		//std::map<std::string, Face*> faces;

		//std::map<std::string, Dice*> dices;

	public:
		AssetsManager(SDL_Renderer* renderer);
		~AssetsManager();

		bool LoadAssets();

		void ClearAssets();

		void AddTexture(const std::string& asset_id, const std::string& file_path, int tile_size = 0);
		Texture* GetTexture(const std::string& asset_id) const;

		/*void AddFace(const std::string& face_name, Face* face);
		Face* GetFace(const std::string& face_name) const;

		void AddDice(const std::string& dice_name, Dice* dice);
		Dice* GetDice(const std::string& dice_name) const;*/
};