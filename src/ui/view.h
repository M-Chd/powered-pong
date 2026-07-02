#pragma once

#include "uiElement.h"

#include <vector>
#include <memory>

namespace UI
{
	struct View
	{
		View()
		{
			layers.reserve(5);
		}

		std::vector<std::unique_ptr<UILayer>> layers;

		UILayer* addLayer(std::unique_ptr<UILayer> layer)
		{
			layers.push_back(std::move(layer));
			return layers.back().get();
		}

		void drawAllUI(SDL_Renderer* renderer) const
		{
			for (auto& l : layers)
				l->render(renderer);
		}

		void clear()
		{
			layers.clear();
		}

	};
}