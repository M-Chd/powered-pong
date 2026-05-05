#pragma once
#include <SDL2/SDL.h>
#include <iostream>

namespace Core
{
	struct WindowRenderer
	{
		SDL_Renderer* renderer = nullptr;
		SDL_Window* window = nullptr;

		float height = 1280;
		float length = 720;

		bool initRenderer();
		bool initWindow();
		void init();
		void quit() const;
	};
}
