#include "view.h"

namespace UI
{
	void View::initDrawPlayerUI(Entities::Player& player, SDL_Renderer* renderer, float x , float y)
	{
		std::unique_ptr<ScoreLayer> newLayer(new ScoreLayer(
        "../../../assets/fonts/Beach-Ball.ttf", 
        30, x, y, WHITE, &player
		));
		
		newLayer->updateTexture(renderer);
		layers.emplace_back(std::move(newLayer));
	}

	void View::updateScoreUI(ScoreLayer& layer, SDL_Renderer* renderer)
	{
		layer.setText(nullptr);
		layer.updateTexture(renderer);
	}

	void View::updateAllScoreUI(SDL_Renderer* renderer)
	{
		if (!layers.empty())
		{
			for (auto& l : layers)
			{
				ScoreLayer* scoreLayer = dynamic_cast<ScoreLayer*>(l.get());
				
				if (scoreLayer)
				{
					scoreLayer->setText(nullptr);
				}
				
				l->updateTexture(renderer);
			}
		}
	}

	void View::drawAllUI(SDL_Renderer* renderer) const
	{
		if (!layers.empty())
		{
			for (auto& l : layers)
			{
				l->Render(renderer);
			}
		}
	}

	void View::clear()
	{
		layers.clear();
	}
}