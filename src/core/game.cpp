#include "game.h"

using namespace Util;

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