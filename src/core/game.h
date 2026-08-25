#pragma once

#include "window.h"
#include "player.h"
#include "board.h"
#include "inputManager.h"
#include "ui/view.h"
#include "ui/scoreBoard.h"
#include "textureCache.h"
#include "util.h"
#include "debugOverlay.h"
#include "connectUi.h"
#include "menuManager.h"
#include "match.h"
#include "difficulty.h"
#include "matchEvent.h"
#include "net/networkManager.h"
#include "inputIP.h"

namespace UI { struct View; }

#define DEBUG 1 // change this to 0 for usual mode, 1 to play on debug mode

constexpr float MENU_REPEAT_DELAY = 0.15f;

namespace Core
{
	struct Game
	{
		enum class GameState { PAUSE, MENU, POINT, PLAY, CONNECTING };

		enum class NetRole { Offline, Host, Client };

		Game() { init(); }

		void init();
		void update(float dt);
		void render();
		void handleMenuAction(UI::Action);
		void handleEvent(const SDL_Event&);
		void quit();

	private:

		void updateMenu(float dt);
		void updatePlay(float dt);
		void updatePoint(float dt);
		void updatePlayOffline(float dt);
		void updatePlayHost(float dt);
		void updatePlayClient(float dt);
		void updateConnecting(float dt);

		void applyMatchEvent(MatchEvent);
		void applySnapshotToMatch(const Network::NetGameState&);
		Network::NetGameState buildNetGameState(Match&);

		void renderMenu();
		void renderPlay();
		void renderPause();
		void renderConnecting();

	public:
		WindowRenderer windowRenderer;
		Match currentmatch;
		UI::View view;
		UI::ScoreBoard scoreboard;
		UI::MenuManager menuManager;
		UI::ConnectUIElement connectUI;
		Network::NetworkManager networkManager;
		UI::InputIP inputIp;
		UI::DebugOverlay debugOverlay;
		System::TextureCache cache;
		System::InputManager inputmngr;
		GameState state;
		NetRole netRole{ NetRole::Offline };
		float pauseTimer{ 0.f };
		float menuInputTimer{ 0.f };
		float hostTickAccumulator{};
		int localPlayerSlot{ 1 };
		bool running{ true };
		bool textInputActive{ false };

#if DEBUG
		void updateDebug(float dt);
#endif
	};

	inline std::string game_state_to_string(Game::GameState&);
	inline static std::string netRole_to_string(Game::NetRole&);
}