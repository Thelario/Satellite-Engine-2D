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

		SDL_Texture* GenerateTexture(const std::string& file_path);
		Texture* GetTexture(const std::string& asset_id) const;
};