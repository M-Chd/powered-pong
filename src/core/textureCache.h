#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

namespace System
{
	class TextureCache
	{
	public:

		SDL_Texture* get(SDL_Renderer* renderer, const std::string& path)
		{
			auto it = cache.find(path);
			if (it != cache.end()) return it->second;
 
			SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
			if (!tex)
				printf("Error loading texture '%s': %s\n", path.c_str(), IMG_GetError());
 
			cache[path] = tex;
			return tex;
		}
 
		~TextureCache()
		{
			for (auto& [path, tex] : cache)
				if (tex) SDL_DestroyTexture(tex);
		}

	private:
		std::unordered_map<std::string, SDL_Texture*> cache;
	};
}