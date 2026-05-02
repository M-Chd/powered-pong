#include "window.h"

namespace Core
{
	bool WindowRenderer::initRenderer()
	{
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer)
        {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        return true;
	}

    bool WindowRenderer::initWindow()
    {
        if (height <= 0 || length <= 0) return false;

        window = SDL_CreateWindow("Powered Pong",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            height,
            length,
            0);

        if (!window)
        {
            SDL_Quit();
            return false;
        }

        return true;
    }

    void WindowRenderer::init()
    {
 
        if (!initRenderer())
        {
            throw std::runtime_error("Error while initializating renderer...");
        }
        if (!initWindow())
        {
            throw std::runtime_error("Error while initializating window...");
        }
    }
}