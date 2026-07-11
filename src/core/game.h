#pragma once

#include "window.h"
#include "player.h"
#include "board.h"
#include "gameConfig.h"
#include "inputManager.h"
#include "ui/view.h"
#include "ui/scoreBoard.h"
#include "textureCache.h"
#include "util.h"
#include "debugOverlay.h"
#include "menuManager.h"

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
		UI::ScoreBoard scoreboard;
		UI::MenuManager menuManager;

#ifdef _DEBUG
		UI::DebugOverlay debugOverlay;
#endif

		System::TextureCache cache;
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

#ifdef _DEBUG
		void updateDebug(float dt);
#endif
	};
}