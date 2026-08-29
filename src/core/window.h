#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define HEIGHT_720P 720
#define WIDTH_720 1280
#define HEIGHT_1080P 1080
#define WIDTH_1080P 1920

namespace Core
{
	struct WindowRenderer
	{
		SDL_Renderer* renderer = nullptr;
		SDL_Window* window = nullptr;

		int width{ WIDTH_720 };
		int height{ HEIGHT_720P };
		// Game only works in 720p for now

		bool initRenderer();
		bool initWindow();
		void init();
		void quit() const;

		~WindowRenderer() { quit(); }
		WindowRenderer() = default;
		WindowRenderer(const WindowRenderer&) = delete;
		WindowRenderer& operator=(const WindowRenderer&) = delete;
	};
}
