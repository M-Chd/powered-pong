#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "vector2.hpp"

namespace UI
{
	class UILayer
	{
	public:

		UILayer(Util::Vec2 position) : position(position)
		{
			destRect.x = static_cast<int>(position.x);
			destRect.y = static_cast<int>(position.y);
		}

		~UILayer()
		{
			if (texture && ownsTexture) SDL_DestroyTexture(texture);
		}

		UILayer(const UILayer&) = delete;
		UILayer& operator=(const UILayer&) = delete;
		UILayer(UILayer&&) = default;
		UILayer& operator=(UILayer&&) = default;

		void render(SDL_Renderer* r) const
		{
			if (!texture) return;
			SDL_RenderCopy(r, texture, nullptr, &destRect);
		}

		void setTexture(SDL_Texture* tex, bool ownerShip = true)
		{
			if (texture && ownsTexture) SDL_DestroyTexture(texture);
			texture = tex;
			ownsTexture = ownerShip;
 
			if (texture)
				SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
 
			destRect.x = static_cast<int>(position.x);
			destRect.y = static_cast<int>(position.y);
		}

		void setPosition(Util::Vec2 pos)
		{
			position = pos;
			destRect.x = static_cast<int>(position.x);
			destRect.y = static_cast<int>(position.y);
		}

		Util::Vec2 getPos() const { return position; }

	private:
		Util::Vec2 position{};
		SDL_Rect destRect{};
		SDL_Texture* texture{ nullptr };
		bool ownsTexture{ true };
	};

	inline void setLayerText(UILayer& layer, SDL_Renderer* r, TTF_Font* font, const std::string& text, SDL_Color c)
	{
		if (!font) return;
 
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), c);
		if (!surface)
		{
			printf("Error while creating surface: %s\n", TTF_GetError());
			return;
		}
 
		SDL_Texture* tex = SDL_CreateTextureFromSurface(r, surface);
		SDL_FreeSurface(surface);
 
		if (!tex)
		{
			printf("Error while creating texture: %s\n", SDL_GetError());
			return;
		}
 
		layer.setTexture(tex);
	}
}