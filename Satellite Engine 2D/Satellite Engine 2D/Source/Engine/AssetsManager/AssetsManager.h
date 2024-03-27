#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../Rendering/Texture.h"

class AssetsManager
{
	private:
		SDL_Renderer* renderer;
		
		std::map<std::string, Texture*> textures;
		std::map<std::string, TTF_Font*> fonts;

	public:
		AssetsManager(SDL_Renderer* renderer);
		~AssetsManager();

		bool LoadAssets();
		void ClearAssets();

		SDL_Texture* GenerateTexture(const std::string& file_path);
		Texture* GetTexture(const std::string& asset_id) const;

		void AddFont(const std::string& asset_id, const std::string& file_path, int font_size);
		TTF_Font* GetFont(const std::string& asset_id) const;
};