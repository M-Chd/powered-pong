#pragma once
#include <SDL2/SDL.h>
#include "player.h"

namespace UI
{
	void drawBall(Entities::Ball& b);

	void drawRectangle(float length, float height);
	void drawCircle(SDL_Renderer* renderer, float radius, Util::Vec2 position, SDL_Color c);
}