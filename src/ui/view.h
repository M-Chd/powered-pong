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
			layers.reserve(6);
		}

		~View()
		{
			clear();
		}

		std::vector<std::unique_ptr<UILayer>> layers;

		UILayer* addLayer(std::unique_ptr<UILayer> layer)
		{
			layers.push_back(std::move(layer));
			return layers.back().get();
		}

		void drawAllUI(SDL_Renderer* renderer, const std::vector<LayerType>& ignoreFlags)
		{
			for (auto& l : layers)
			{
				for (auto& ignL : ignoreFlags)
				{
					if(l->getType() != ignL)
						l->render(renderer);
				}
			}
		}

		void drawThisType(SDL_Renderer* r, LayerType type)
		{
			for (auto& l : layers)
			{
				if (l->getType() == type)
					l->render(r);
			}
		}

		void clear()
		{
			layers.clear();
		}

	};
}