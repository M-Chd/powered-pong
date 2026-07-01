#include "view.h"

namespace UI
{
	void View::drawPlayerUI(Entities::Player& player, SDL_Renderer* renderer)
	{
		ScoreLayer layer = {"C:\\Users\\mouad\\Desktop\\powered-pong\\assets\\fonts\\Beach-Ball.ttf",20,10,20,WHITE,player};
		layers.emplace_back(std::make_unique<ScoreLayer>(layer));
		layer.setText();
		layer.Render(renderer);
	}

	void View::updateScoreUI(ScoreLayer& layer, SDL_Renderer* renderer)
	{
		layer.updateTexture(renderer);
	}

	void View::updateAllScoreUI(SDL_Renderer* renderer)
	{
		if (!layers.empty())
		{
			for (auto& l : layers)
			{
				l->updateTexture(renderer);
			}
		}
	}
}