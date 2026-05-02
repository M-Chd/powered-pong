#pragma once
#include <SDL2/SDL.h>
#include <iostream>

namespace Core
{
	struct WindowRenderer
	{
	public:

		int height = 1920;
		int length = 1080;

		bool initRenderer();
		bool initWindow();
		void init();
	private:
		SDL_Renderer* renderer = nullptr;
		SDL_Window* window = nullptr;
	};
}
