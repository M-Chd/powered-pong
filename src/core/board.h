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

		std::vector<Entities::Item> items;
		Entities::Ball b;
		Entities::Player p1;
		Entities::Player p2;

		void drawBoard(SDL_Renderer* renderer) const; //TODO View methods in a View class
		void drawBall(SDL_Renderer* renderer);
		void drawPlayers(SDL_Renderer* renderer);
		void drawItems(SDL_Renderer* renderer);
		void drawPlayerUI(SDL_Renderer* r, Entities::Player& p, int x, int y);
		int checkBallPoint() const;
		void setupRound(Entities::Player& p, Util::Vec2 speed);
	};
}