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
		void AddTexture(const std::string& assetId, const std::string& filePath, int width, int height, int tileSize);
		Texture* GetTexture(const std::string& assetId) const;
};