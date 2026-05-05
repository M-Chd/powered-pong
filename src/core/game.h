#pragma once
#include "window.h"
#include "player.h"
#include "board.h"


namespace Core
{
	struct View;

	enum GameMode
	{
		SINGLEPLAYER,MULTIPLAYER
	};

	struct Game
	{
		WindowRenderer windowRenderer;
		GameMode mode;
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