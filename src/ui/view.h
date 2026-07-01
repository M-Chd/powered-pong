#pragma once

#include "infoLayer.h"

#include <vector>

namespace UI
{
	struct View
	{
		View()
		{
			layers.reserve(5);
		}

		std::vector<std::unique_ptr<InfoLayer>> layers;

		void drawPlayerUI(Entities::Player& player, SDL_Renderer* renderer);
		void updateScoreUI(ScoreLayer& layer, SDL_Renderer* renderer);
		void updateAllScoreUI(SDL_Renderer* renderer);
	};
}