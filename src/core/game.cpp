#include "game.h"

using namespace Util;

namespace Core
{
	void Game::init()
	{
		float height = windowRenderer.height;
		float length = windowRenderer.length;

		try {
			windowRenderer.init();
		}
		catch (std::runtime_error e)
		{
			printf("%s", e.what());
		}

		auto PlayerOnePos = Vec2{ 207.0f, 360.0f };
		auto PlayerTwoPos = Vec2{ 1047.0f, 360.0f };

		board.p1.setCenter(PlayerOnePos);
		board.p2.setCenter(PlayerTwoPos);
		board.b.setSpeed(DEFAULT_BALL_SPEED);

	}

	void Game::checkPoint()
	{
		switch (board.checkBallPoint())
		{
		case 1:
			board.setupRound(board.p1, DEFAULT_BALL_SPEED_MINUS);
			//update all the UI
			state = GameState::POINT;
			pauseTimer = 1.0f;
			break;
		case -1:
			board.setupRound(board.p2, DEFAULT_BALL_SPEED);
			//update all the UI
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

	void Game::quit() const
	{
		windowRenderer.quit();
	}
}