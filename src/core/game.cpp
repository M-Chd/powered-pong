#include "game.h"

using namespace Util;

namespace Core
{
	void Game::init()
	{
		int height = windowRenderer.height;
		int length = windowRenderer.length;

		try {
			windowRenderer.init();
		}
		catch (std::runtime_error e)
		{
			printf("%s", e.what());
		}

		auto PlayerOnePos = Vec2{PlayerOneDefaultPos};
		auto PlayerTwoPos = Vec2{PlayerTwoDefaultPos};

		board.p1.setCenter(PlayerOnePos);
		board.p2.setCenter(PlayerTwoPos);
		board.b.setSpeed(DEFAULT_BALL_SPEED);

		scoreboard.init(view, windowRenderer.renderer,
			"../../../assets/fonts/Beach-Ball.ttf", 30, WHITE,
			{ 10,20 }, { 1100, 20 });
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

	void Game::quit()
	{
		view.clear();
		windowRenderer.quit();
	}
}