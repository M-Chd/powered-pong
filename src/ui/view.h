#pragma once

#include "infoLayer.h"

#include <vector>
#include <functional>
#include <memory>

namespace UI
{
	struct View
	{
		View()
		{
			layers.reserve(5);
		}

		std::vector<std::unique_ptr<InfoLayer>> layers;

		void initDrawPlayerUI(Entities::Player& player, SDL_Renderer* renderer, float x, float y);
		void updateScoreUI(ScoreLayer& layer, SDL_Renderer* renderer);
		void updateAllScoreUI(SDL_Renderer* renderer);
		void drawAllUI(SDL_Renderer* renderer) const;
		void clear();
	};
}