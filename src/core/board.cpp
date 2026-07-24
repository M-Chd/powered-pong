#include "board.h"

using namespace Entities;

namespace Core
{
	void Board::drawBoard(SDL_Renderer* renderer) const
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = { offsetX,offsetY,l,h };
		SDL_RenderDrawRect(renderer, &rect);
	}

	int Board::checkBallPoint(Ball& b, Player& p1, Player& p2) const
	{
		if (b.getCenter().x < p1.getCenter().x + p1.getRadiusX())
		{
			return 1;
		}
		if (b.getCenter().x > p2.getCenter().x - p2.getRadiusX())
		{
			return -1;
		}
		return 0;
	}
}
