#pragma once
#include "ball.h"
#include "player.h"

constexpr int winscore{ 5 };

namespace Core
{
	struct Board
	{
		int h{ 480 };
		int l{ 854 };
		int offsetX{ 200 };
		int offsetY{ 100 };
		int height = h + offsetY;
		int length = l + offsetX;

		void drawBoard(SDL_Renderer* renderer) const;
		int checkBallPoint(Entities::Ball&,Entities::Player&,
			Entities::Player&) const;
	};
}