#include "game.h"

namespace Core
{
	void Game::init()
	{
		float height = windowRenderer.height;
		float length = windowRenderer.length;

		ball = Entities::Ball(Util::Vector2{ height / 2, length / 2 }, 1.0, 1.0, Entities::NONE);

		//TODO

	}
}