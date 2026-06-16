#pragma once
#include "window.h"
#include "player.h"
#include "board.h"
#include "gameConfig.h"
#include "inputManager.h"

namespace Core
{
	struct View;

	struct Game
	{
		WindowRenderer windowRenderer;
		GameConfig config;
		InputManager inputmngr;
		Board board;

		Game(const GameConfig& config)
		{
			init();
		}

		void init();
		void run();
		bool isGameFinished() const ;
		void quit() const;

	};
}