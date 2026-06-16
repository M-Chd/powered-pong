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
		board.b.setSpeed({ 500.0f,0.0f });

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