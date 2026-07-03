#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

namespace Core
{
	struct WindowRenderer
	{
		SDL_Renderer* renderer = nullptr;
		SDL_Window* window = nullptr;

		int width{ 1280 };
		int height{ 720 };

		bool initRenderer();
		bool initWindow();
		void init();
		void quit() const;
	};
}
