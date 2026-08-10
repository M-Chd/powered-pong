#include "scoreBoard.h"

namespace UI
{
	void ScoreBoard::init(View& view, SDL_Renderer* renderer,
		const std::string& fontPath, int fontSize, SDL_Color color,
		Util::Vec2 p1_pos, Util::Vec2 p2_pos)
	{
		this->color = color;
		font = std::shared_ptr<TTF_Font>(TTF_OpenFont(fontPath.c_str(), fontSize), TTF_CloseFont);
 
		p1Layer = view.addLayer(std::make_unique<UILayer>(p1_pos,LayerType::P1_score));
		p2Layer = view.addLayer(std::make_unique<UILayer>(p2_pos,LayerType::P2_score));
 
		update(renderer, 0, 0);
	}
 
	void ScoreBoard::update(SDL_Renderer* renderer, int p1Score, int p2Score)
	{
		setLayerText(*p1Layer, renderer, font.get(), "Score: " + std::to_string(p1Score), color);
		setLayerText(*p2Layer, renderer, font.get(), "Score: " + std::to_string(p2Score), color);
	}
}