#include "game.h"
#include "layout.hpp"

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

		/////// LOCAL MULTIPLAYER LAYOUT ////////
		auto PlayerOnePos = Vec2{ PlayerOneDefaultPos };
		auto PlayerTwoPos = Vec2{ PlayerTwoDefaultPos };

		board.p1.setCenter(PlayerOnePos);
		board.p2.setCenter(PlayerTwoPos);
		board.b.setSpeed(DEFAULT_BALL_SPEED);

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
		if (inputmngr.isKeyDown(SDL_SCANCODE_UP))
			board.p2.move(-1.f, dt, board);
		else if (inputmngr.isKeyDown(SDL_SCANCODE_DOWN))
			board.p2.move(1.f, dt, board);

		if (inputmngr.isKeyDown(SDL_SCANCODE_Z) ||
			inputmngr.isKeyDown(SDL_SCANCODE_W))
			board.p1.move(-1.f, dt, board);

		else if (inputmngr.isKeyDown(SDL_SCANCODE_S))
			board.p1.move(1.f, dt, board);

		board.b.move(dt, board);

		checkPoint();
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
		board.drawBoard(windowRenderer.renderer);

		board.b.draw(windowRenderer.renderer);

		board.drawPlayers(windowRenderer.renderer);

		view.drawAllUI(windowRenderer.renderer);
	}

	void Game::checkPoint()
	{
		switch (board.checkBallPoint())
		{
		case 1:
			board.setupRound(board.p2, DEFAULT_BALL_SPEED_MINUS);
			scoreboard.update(windowRenderer.renderer, board.p1.getScore(), board.p2.getScore());
			state = GameState::POINT;
			pauseTimer = 1.0f;
			break;
		case -1:
			board.setupRound(board.p1, DEFAULT_BALL_SPEED);
			scoreboard.update(windowRenderer.renderer, board.p1.getScore(), board.p2.getScore());
			state = GameState::POINT;
			pauseTimer = 1.0f;
			break;
		default:
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
				// creer une partie Easy;
				state = GameState::PLAY;
				break;
			case GameAction::StartSoloMedium:
				// creer une partie Medium;
				state = GameState::PLAY;
				break;
			case GameAction::StartSoloHard:
				// creer une partie hard;
				state = GameState::PLAY;
				break;
			case GameAction::StartLocalMultiplayer:
				// creer une partie standard;
				state = GameState::PLAY;
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

	bool Game::isGameFinished() const
	{
		return (board.p1.getScore() > winscore) || (board.p2.getScore() > winscore);
	}

#ifdef _DEBUG
	void Game::updateDebug(float dt)
	{
		auto ballPos = board.b.getCenter();
		auto p1Pos = board.p1.getCenter();
		auto p2Pos = board.p2.getCenter();

		debugOverlay.update(windowRenderer.renderer, {
			"Ball pos: (" + fmt(ballPos.x) + ", " + fmt(ballPos.y) + ")",
			"Ball speed X: " + fmt(board.b.getSpeed().x),
			"Ball speed Y: " + fmt(board.b.getSpeed().y),
			"P1 pos: (" + fmt(p1Pos.x) + ", " + fmt(p1Pos.y) + ")",
			"P2 pos: (" + fmt(p2Pos.x) + ", " + fmt(p2Pos.y) + ")",
			"State: " + std::to_string(static_cast<int>(state)),
			"frame time: " + fmt(1.0 / static_cast<float>(dt)),
			"Current Ball effect: " + std::to_string(static_cast<int>(board.b.getBallEffect()))
		});
	}
#endif 


	void Game::quit()
	{
		view.clear();
		windowRenderer.quit();
	}
}