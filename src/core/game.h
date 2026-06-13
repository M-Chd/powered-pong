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
		void run();
		bool isGameFinished() const ;
		void quit() const;
	};
}