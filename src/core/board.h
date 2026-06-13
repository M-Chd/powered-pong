#pragma once
#include "ball.h"
#include "player.h"

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
		unsigned int winscore{ 5 };

		std::vector<Entities::Item> items;
		Entities::Ball b;
		Entities::Player p1;
		Entities::Player p2;

		void drawBoard(SDL_Renderer* renderer) const;
		void drawBall(SDL_Renderer* renderer);
		void drawPlayers(SDL_Renderer* renderer);
		void drawItems(SDL_Renderer* renderer);
	};
}