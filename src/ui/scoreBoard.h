#pragma once

#include "view.h"
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <string>

namespace UI
{
	class ScoreBoard
	{
	public:

		void init(View& view, SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
			SDL_Color color, Util::Vec2 p1_pos, Util::Vec2 p2_pos);

		void update(SDL_Renderer* r, int p1Score, int p2Score);

	private:
		std::shared_ptr<TTF_Font> font;
		SDL_Color color{};
		UILayer* p1Layer{ nullptr };
		UILayer* p2Layer{ nullptr };
	};
}