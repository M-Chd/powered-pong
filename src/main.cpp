#define SDL_MAIN_HANDLED
#include <iostream>
#include "game.h"

int main()
{
	Core::Game g;

    bool running = true;
    SDL_Event event;

    auto& renderer = g.windowRenderer.renderer;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        UI::drawCircle(renderer, 10.0f, { 640.0f,360.0f },SDL_Color{255,255,255,255});

        SDL_RenderPresent(renderer);
    }
    g.quit();
	return 0;
}