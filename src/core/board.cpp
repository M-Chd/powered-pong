#include "board.h"
#include "board.h"

namespace Core
{
	void Board::drawBoard(SDL_Renderer* renderer) const
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = { offsetX,offsetY,l,h };
		SDL_RenderDrawRect(renderer, &rect);
	}

	void Board::drawBall(SDL_Renderer* renderer)
	{
		b.draw(renderer);
	}

	void Board::drawPlayers(SDL_Renderer* renderer)
	{
		p1.draw(renderer);
		p2.draw(renderer);
	}

	int Board::checkBallPoint() const
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

	void Board::setupRound(Entities::Player& p, Util::Vec2 speed)
	{
		b.setPosition(BALL_INITIAL_POS);
		p1.setCenter(PlayerOneDefaultPos);
		p2.setCenter(PlayerTwoDefaultPos);
		
		if (b.getBallEffect() == Entities::BallEffect::MULTIPLICATOR)
			p.addPoint(2);
		else
			p.addPoint();

		b.setSpeed(speed);
	}
}
