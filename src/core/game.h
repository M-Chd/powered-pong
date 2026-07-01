#pragma once
#include "window.h"
#include "player.h"
#include "board.h"
#include "gameConfig.h"
#include "inputManager.h"
#include "ui/view.h"

namespace UI { struct View; }

namespace Core
{
	struct Game
	{
		enum class GameState
		{
			PAUSE,
			POINT,
			PLAY
		};

		WindowRenderer windowRenderer;
		GameConfig config;
		Board board;
		UI::View view;
		System::InputManager inputmngr;
		GameState state;
		float pauseTimer = 0.f;


		Game(const GameConfig& config)
		{
			init();
		}

		void init();
		void run();
		bool isGameFinished() const ;
		void quit();
		void checkPoint();

	};
}