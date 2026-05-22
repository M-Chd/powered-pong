#pragma once
#include "window.h"
#include "player.h"
#include "board.h"


namespace Core
{
	struct View;

	struct Game
	{
		WindowRenderer windowRenderer;
		Board board;

		Game()
		{
			init();
		}

		void init();
		bool isGameFinished();
		void quit() const;
	};
}