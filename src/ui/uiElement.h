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
		
		UILayer(UILayer&& other) noexcept
			: position(other.position),
			  destRect(other.destRect),
			  texture(other.texture),
			  ownsTexture(other.ownsTexture)
		{
			other.texture = nullptr;
			other.ownsTexture = false;
		}
		UILayer& operator=(UILayer&& other) noexcept
		{
			if (this != &other)
			{
				if (texture && ownsTexture)
					SDL_DestroyTexture(texture);

				position = other.position;
				destRect = other.destRect;
				texture = other.texture;
				ownsTexture = other.ownsTexture;

				other.texture = nullptr;
				other.ownsTexture = false;
			}

			return *this;
		}

		void render(SDL_Renderer* r) const
		{
			if (!texture)
			{
				printf("Texture nullptr\n");
				return;
			}

			if (SDL_RenderCopy(r, texture, nullptr, &destRect) != 0)
			{
				printf("%s\n", SDL_GetError());
			}
		}

		void setTexture(SDL_Texture* tex, bool ownerShip = true)
		{
			if (texture && ownsTexture) SDL_DestroyTexture(texture);
			texture = tex;
			ownsTexture = ownerShip;
 
			if (texture)
			{
				SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
			}
			destRect.x = static_cast<int>(position.x);
			destRect.y = static_cast<int>(position.y);
		}

		void setColor(SDL_Color c)
		{
			if (texture)
				SDL_SetTextureColorMod(texture, c.r, c.g, c.b);
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