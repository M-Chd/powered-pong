#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include "player.h"

namespace UI
{
	class InfoLayer
	{
	public:

		InfoLayer(const std::string& fontPath, float x, float y, const std::string& text, SDL_Color c, int size);
		virtual ~InfoLayer();

		void Render(SDL_Renderer* r);
		void updateTexture(SDL_Renderer* r);
		void setPosition(float x, float y);
		std::string getText() const;

		virtual void setText(std::string* text) = 0;

	protected:

		float x{}, y{};
        SDL_Rect destRect{};
		std::string path{};
        SDL_Texture* texture{nullptr};
        std::shared_ptr<TTF_Font> font{nullptr};
		std::string text{};
        SDL_Color color{};
	};

	class ScoreLayer : public InfoLayer
	{
	public:

		ScoreLayer(const std::string& fontPath, int fontSize, float x, float y, SDL_Color c, Entities::Player* playerPtr);
		
		void setText(std::string* text) override;

	private:
		Entities::Player* playerPtr{ nullptr };
	};
}