#include "game.h"

namespace Core
{
	void Game::init()
	{
		float height = windowRenderer.height;
		float length = windowRenderer.length;

		ball = Entities::Ball{ Util::Vec2{ height / 2, length / 2 }, 1.0, Util::Vec2{1.0f,1.0f}, Entities::Item::NONE};

		//TODO

	}
}