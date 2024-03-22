#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include "../Rendering/Texture.h"

class AssetsManager
{
	private:
		std::map<std::string, Texture*> textures;
		SDL_Renderer* renderer;

	public:
		AssetsManager(SDL_Renderer* renderer);
		~AssetsManager();

		void ClearAssets();
		void AddTexture(const std::string& asset_id, const std::string& file_path, int tile_size = 0);
		Texture* GetTexture(const std::string& asset_id) const;
};