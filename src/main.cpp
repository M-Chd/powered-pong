#define SDL_MAIN_HANDLED
#include <iostream>
#include "game.h"

int main()
{
	Core::Game g;

    bool running = true;
    SDL_Event event;
    Uint64 lastTime = SDL_GetPerformanceCounter();


    auto& renderer = g.windowRenderer.renderer;
    g.ball.setSpeed({ 1000.0f,1000.0f });

    while (running)
    {

        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (now - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            switch (event.type)
            {
            case SDL_KEYDOWN:
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        g.ball.draw(renderer);
        g.ball.move(dt);

        SDL_RenderPresent(renderer);
    }
    g.quit();
	return 0;
}