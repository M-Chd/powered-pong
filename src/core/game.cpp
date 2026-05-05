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

	void Game::quit()
	{
		windowRenderer.quit();
	}
}