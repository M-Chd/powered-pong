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
    g.board.b.setSpeed({ 500.0f,0.0f });

    while (running)
    {

        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (now - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    g.board.p1.move(-1.0f, dt, g.board);
                    break;
                case SDLK_DOWN:
                    g.board.p1.move(1.0f, dt, g.board);
                    break;
                case SDLK_e:
                    g.board.p1.useItem(&g.board.b);
                    break;
                case SDLK_f:
                    g.board.p1.AcquireItem(Entities::Item(Entities::ItemType::SPEED, 10));
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        g.board.drawBoard(renderer);
        g.board.b.draw(renderer);
        g.board.drawPlayers(renderer);
        g.board.b.move(dt,g.board);

        SDL_RenderPresent(renderer);
    }
    g.quit();
	return 0;
}