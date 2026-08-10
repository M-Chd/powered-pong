#pragma once

#include "view.h"
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>

namespace UI
{
	class ConnectUIElement
	{
	public:

		void init(View& view, SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
			SDL_Color color, Util::Vec2 pos)
		{
			font = std::shared_ptr<TTF_Font>(TTF_OpenFont(fontPath.c_str(), fontSize), TTF_CloseFont);
			this->color = color;
			
			auto layer = view.addLayer(std::make_unique<UILayer>(pos,LayerType::ConnectLayer));
			setLayerText(*layer, renderer, font.get(), "Connecting...", color);
		}

	private:
		std::shared_ptr<TTF_Font> font;
		SDL_Color color{};
	};
}