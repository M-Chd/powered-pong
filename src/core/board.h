#pragma once
#include "ball.h"
#include "player.h"

namespace Core
{
	struct Board
	{
		int h = 480;
		int l = 854;
		int offsetX = 200;
		int offsetY = 100;
		int height = h + offsetY;
		int length = l + offsetX;

		Entities::Ball b;
		Entities::PlayerStick p1;
		//Entities::PlayerStick p2;
		std::vector<Entities::Item> items;

		void drawBoard(SDL_Renderer* renderer) const;
		void drawBall(SDL_Renderer* renderer);
	};
}