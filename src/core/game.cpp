#include "game.h"
#include "game.h"
#include "game.h"

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

		//TODO

	}

	bool Game::isGameFinished() const
	{
		return board.p1.getScore() > board.winscore; // return (board.p1.getScore() > board.winscore) || (board.p2.getScore() > board.winscore); 
	}

	void Game::quit() const
	{
		windowRenderer.quit();
	}
}