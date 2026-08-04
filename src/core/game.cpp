#include "game.h"

using namespace Util;
using namespace UI;

namespace Core
{
	void Game::init()
	{
		int width = windowRenderer.width;
		int height = windowRenderer.height;

		try
		{
			windowRenderer.init();
		}
		catch (std::runtime_error e)
		{
			printf("%s", e.what());
		}

		menuManager.init(windowRenderer.renderer,"../../../assets/fonts/IMPACT.ttf",50,WHITE);

		scoreboard.init(view, windowRenderer.renderer,
			"../../../assets/fonts/Beach-Ball.ttf", 30, WHITE,
			{ 10,20 }, { 1100, 20 });

		debugOverlay.init(view,
			"../../../assets/fonts/Beach-Ball.ttf", 14, SDL_Color{200,200,200,255},
			10, static_cast<float>(windowRenderer.height) - 15, 8);

		state = GameState::MENU;
	}

	void Game::update(float dt)
	{
		switch (state)
		{
		case Core::Game::GameState::PAUSE:
			//TODO
			break;
		case Core::Game::GameState::MENU:
			updateMenu(dt);
			break;
		case Core::Game::GameState::POINT:
			updatePoint(dt);
			break;
		case Core::Game::GameState::PLAY:
			updatePlay(dt);
			break;
		case Core::Game::GameState::CONNECTING:
			updateConnecting(dt);
			break;
		default:
			break;
		}

#ifdef _DEBUG
		updateDebug(dt);
#endif
	}

	void Game::updateMenu(float dt)
	{
		menuInputTimer -= dt;

		if (menuInputTimer <= 0.f)
		{
			if (inputmngr.isKeyDown(SDL_SCANCODE_UP))
			{
				menuManager.moveUp();
				menuInputTimer = MENU_REPEAT_DELAY;
			}
			else if (inputmngr.isKeyDown(SDL_SCANCODE_DOWN))
			{
				menuManager.moveDown();
				menuInputTimer = MENU_REPEAT_DELAY;
			}
			else if (inputmngr.isKeyDown(SDL_SCANCODE_RETURN))
			{
				 handleMenuAction(menuManager.activate());
				 menuInputTimer = MENU_REPEAT_DELAY;
			}
		}
	}

	void Game::updatePlay(float dt)
	{
		switch (netRole)
		{
		case Core::Game::NetRole::Offline: updatePlayOffline(dt); break;
		case Core::Game::NetRole::Host:    updatePlayHost(dt);	  break;
		case Core::Game::NetRole::Client:  updatePlayClient(dt);  break;
		default:
			break;
		}
	}

	void Game::updateConnecting(float dt)
	{
		networkManager.processMessages();

		if (networkManager.getConnectionState() == Network::ConnectionState::Failed)
		{
			netRole = NetRole::Offline;
			state = GameState::MENU;
			return;
		}

		int slot;
		if (networkManager.pollMatchStart(slot))
		{
			localPlayerSlot = slot;
			state = GameState::PLAY;
		}
	}

	void Game::applyMatchEvent(MatchEvent e)
	{
		switch (e)
		{
		case MatchEvent::PointScored:
			scoreboard.update(windowRenderer.renderer,
				currentmatch.getPlayerOne().getScore(),
				currentmatch.getPlayerTwo().getScore());
			pauseTimer = 1.f;
			state = GameState::POINT;
			break;

		case MatchEvent::MatchFinished:
			scoreboard.update(windowRenderer.renderer,
				currentmatch.getPlayerOne().getScore(),
				currentmatch.getPlayerTwo().getScore());
			state = GameState::MENU;
			if (netRole != NetRole::Offline)
				networkManager.teardown();
			break;

		default:
			break;
		}
	}

	void Game::applySnapshotToMatch(const Network::NetGameState& s)
	{
		auto x = currentmatch.getPlayerOne().getCenter().x;

		currentmatch.getBall().setPosition({ s.ballX, s.ballY });
		currentmatch.getPlayerOne().setCenter({ x , s.p1Y });
		currentmatch.getPlayerTwo().setCenter({ x , s.p2Y });
		currentmatch.getPlayerOne().setScore(s.p1Score);
		currentmatch.getPlayerTwo().setScore(s.p2Score);
	}

	Network::NetGameState& Game::buildNetGameState(Match& match)
	{
		auto& ball = match.getBall();
		auto& p1 = match.getPlayerOne();
		auto& p2 = match.getPlayerTwo();

		Network::NetGameState state = {
			.ballX = ball.getCenter().x,
			.ballY = ball.getCenter().y,
			.ballSpeedX = ball.getSpeed().x,
			.ballSpeedY = ball.getSpeed().y,
			.p1Y = p1.getCenter().y,
			.p2Y = p2.getCenter().y,
			.p1Score = p1.getScore(),
			.p2Score = p2.getScore()
		};

		return state;
	}

	void Game::updatePlayClient(float dt)
	{
		PlayerInputState localInput = buildLocalInput(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, inputmngr);
		networkManager.sendInput(localInput);

		Network::NetGameState snapshot;
		if (networkManager.pollGameState(snapshot))
			applySnapshotToMatch(snapshot);

		if (networkManager.pollMatchEnded())
		{
			state = GameState::MENU;
			networkManager.teardown();
			netRole = NetRole::Offline;
		}
	}

	void Game::updatePlayHost(float dt)
	{
		PlayerInputState p1 = buildLocalInput(SDL_SCANCODE_Z, SDL_SCANCODE_S, inputmngr);

		networkManager.processMessages();

		hostTickAccumulator += dt;
		const float TICK = 1.f / 30.f;

		while (hostTickAccumulator >= TICK)
		{
			PlayerInputState p2 = networkManager.getRemoteInput(2);
			MatchEvent e = currentmatch.update(TICK, p1, p2);
			networkManager.broadcastGameState(buildNetGameState(currentmatch));
			applyMatchEvent(e);
			hostTickAccumulator -= TICK;
		}
	}

	void Game::updatePlayOffline(float dt)
	{
		PlayerInputState p1 = buildLocalInput(SDL_SCANCODE_Z, SDL_SCANCODE_S, inputmngr);
		PlayerInputState p2 = buildLocalInput(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, inputmngr);
		applyMatchEvent(currentmatch.update(dt, p1, p2));
	}

	void Game::updatePoint(float dt)
	{
		pauseTimer -= dt;

		if (pauseTimer <= 0.f)
			state = GameState::PLAY;
	}

	void Game::render()
	{
		SDL_SetRenderDrawColor(windowRenderer.renderer, 0, 0, 0, 255);
		SDL_RenderClear(windowRenderer.renderer);

		switch (state)
		{
		case GameState::MENU:
			renderMenu();
			break;

		case GameState::PLAY:
			renderPlay();
			break;

		case GameState::POINT:
			renderPlay();
			break;

		case GameState::PAUSE:
			//renderPause(); TODO
			break;

		case GameState::CONNECTING:
			//renderConnecting(); TODO
			break;

		default:
			break;
		}

		SDL_RenderPresent(windowRenderer.renderer);
	}

	void Game::renderMenu()
	{
		menuManager.render(windowRenderer.renderer);
	}

	void Game::renderPlay()
	{
		currentmatch.render(windowRenderer.renderer);

		view.drawAllUI(windowRenderer.renderer);
	}

	inline GameDifficulty actionToDifficulty(GameAction& a)
	{
		switch (a)
		{
		case GameAction::StartSoloEasy:
			return GameDifficulty::EASY;
			break;
		case GameAction::StartSoloMedium:
			return GameDifficulty::MEDIUM;
			break;
		case GameAction::StartSoloHard:
			return GameDifficulty::HARD;
			break;
		default:
			return GameDifficulty::EASY;
			break;
		}
	}

	void Game::handleMenuAction(UI::Action a)
	{
		if (a.menuid != MenuID::None)
		{
			menuManager.setCurrentMenu(a.menuid);
		}
		else
		{
			switch (a.action)
			{
			case GameAction::StartSoloEasy:
				currentmatch = Match(
					Match::MatchSettings{
						.type = Match::MatchType::Solo,
						.difficulty = GameDifficulty::EASY
					});
				state = GameState::PLAY;
				break;
			case GameAction::StartSoloMedium:
				currentmatch = Match(
					Match::MatchSettings{
						.type = Match::MatchType::Solo,
						.difficulty = GameDifficulty::MEDIUM
					});
				state = GameState::PLAY;
				break;
			case GameAction::StartSoloHard:
				currentmatch = Match(
					Match::MatchSettings{
						.type = Match::MatchType::Solo,
						.difficulty = GameDifficulty::HARD
					});
				state = GameState::PLAY;
				break;
			case GameAction::StartLocalMultiplayer:
				currentmatch = Match(
					Match::MatchSettings{
						.type = Match::MatchType::Multi,
						.difficulty = GameDifficulty::NONE
					});
				state = GameState::PLAY;
				break;

			case GameAction::HostGame:
				netRole = NetRole::Host;
				localPlayerSlot = 1;
				networkManager.startHost(networkManager.getActivePort());
				networkManager.connectLocalClient();

				currentmatch = Match(
					Match::MatchSettings{
						.type = Match::MatchType::Multi,
						.difficulty = GameDifficulty::NONE
					});
				state = GameState::CONNECTING;
				break;

			case GameAction::JoinGame:
				netRole = NetRole::Client;
				networkManager.joinServer(hostIpFromUI, networkManager.getActivePort());
				state = GameState::CONNECTING;
				break;

			case GameAction::Back:
				menuManager.returnBack();
				break;
			case GameAction::Quit:
				running = false;
				break;
			default:
				break;
			}
		}
	}

#ifdef _DEBUG
	void Game::updateDebug(float dt)
	{
		auto& ball = currentmatch.getBall();
		auto& p_one = currentmatch.getPlayerOne();
		auto& p_two = currentmatch.getPlayerTwo();

		auto ballPos = ball.getCenter();
		auto p1Pos = p_one.getCenter();
		auto p2Pos = p_two.getCenter();

		debugOverlay.update(windowRenderer.renderer, {
			"Ball pos: (" + fmt(ballPos.x) + ", " + fmt(ballPos.y) + ")",
			"Ball speed X: " + fmt(ball.getSpeed().x),
			"Ball speed Y: " + fmt(ball.getSpeed().y),
			"P1 pos: (" + fmt(p1Pos.x) + ", " + fmt(p1Pos.y) + ")",
			"P2 pos: (" + fmt(p2Pos.x) + ", " + fmt(p2Pos.y) + ")",
			"State: " + std::to_string(static_cast<int>(state)),
			"frame time: " + fmt(1.0f / static_cast<float>(dt)),
			"Current Ball effect: " + std::to_string(static_cast<int>(ball.getBallEffect()))
		});
	}
#endif 

	void Game::quit()
	{
		view.clear();
		windowRenderer.quit();
	}
}