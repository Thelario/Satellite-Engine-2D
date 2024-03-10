#pragma once

#include <map>
#include <string>
#include <SDL.h>

class AssetsManager
{
	private:
		std::map<std::string, SDL_Texture*> textures;
		SDL_Renderer* renderer;

	public:
		AssetsManager(SDL_Renderer* renderer);
		~AssetsManager();

		void ClearAssets();
		void AddTexture(const std::string& assetId, const std::string& filePath);
		SDL_Texture* GetTexture(const std::string& assetId) const;
};