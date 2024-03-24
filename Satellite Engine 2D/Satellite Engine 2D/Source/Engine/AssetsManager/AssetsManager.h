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

	public:
		AssetsManager(SDL_Renderer* renderer);
		~AssetsManager();

		bool LoadAssets();
		void ClearAssets();

		void AddTexture(const std::string& asset_id, const std::string& file_path, int tile_size = 0);
		Texture* GetTexture(const std::string& asset_id) const;
};