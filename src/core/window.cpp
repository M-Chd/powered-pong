#include "window.h"

namespace Core
{
	bool WindowRenderer::initRenderer()
	{
        if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!renderer)
        {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        if (TTF_Init() < 0) {
            std::cout << "Couldn't initialize TTF lib: " << TTF_GetError() << std::endl;
            return false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        return true;
	}

    bool WindowRenderer::initWindow()
    {
        if (width <= 0 || height <= 0) return false;

        window = SDL_CreateWindow("Powered Pong",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
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
 
        if (!initWindow())
        {
            throw std::runtime_error("Error while initializating window...");
        }
        if (!initRenderer())
        {
            throw std::runtime_error("Error while initializating renderer...");
        }
    }

    void WindowRenderer::quit() const
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}