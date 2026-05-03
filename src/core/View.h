#pragma once
#include "game.h"

namespace Core
{
	struct View
	{
		void displayGame(Game& g);
		void drawPlayers(Game& g);
		void drawScore(Game& g);
		//void drawTime();
		void drawBall(Entities::Ball& b);

		void drawRectangle(float length, float height);
		void drawCircel(float radius);
	};
}