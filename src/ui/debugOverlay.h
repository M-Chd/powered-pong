#pragma once

#include "view.h"
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>
#include <vector>

namespace UI
{
	class DebugOverlay
	{
	public:

		DebugOverlay()
		{
			layers.reserve(8);
		}

		void init(View& view,
			const std::string& fontPath, int fontSize, SDL_Color color,
			float x, float y, int lineCount);
 
		void update(SDL_Renderer* renderer, const std::vector<std::string>& lines);
 
	private:
		std::shared_ptr<TTF_Font> font;
		SDL_Color color{};
		std::vector<UILayer*> layers;
	};
}