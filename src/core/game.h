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
#include "match.h"
#include "difficulty.h"
#include "matchEvent.h"

namespace UI { struct View; }

constexpr float MENU_REPEAT_DELAY = 0.15f;

namespace Core
{
	struct Game
	{
		enum class GameState
		{
			PAUSE,
			MENU,
			POINT,
			PLAY
		};

		Game(const GameConfig& config) { init(); }

		void init();
		void update(float dt);
		void render();
		void handleMenuAction(UI::Action a);
		void quit();

	private:

		void updateMenu(float dt);
		void updatePlay(float dt);
		void updatePoint(float dt);
		void renderMenu();
		void renderPlay();

	public:
		WindowRenderer windowRenderer;
		GameConfig config;
		Match currentmatch;
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
		float menuInputTimer = 0.f;
		bool running{ true };

#ifdef _DEBUG
		void updateDebug(float dt);
#endif
	};

	inline GameDifficulty actionToDifficulty(UI::GameAction&);
}