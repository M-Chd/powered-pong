#include "game.h"


//TODO Faire un systeme qui prend en compte en meme temps les inputs des joueurs
//TODO regler la physique des joueurs (positions inconstantes ect...)
//TODO Collisions avec les joueurs

int main(int argc, char* argv[])
{
    Core::GameConfig config = Core::parseArgs(argc, argv);

	Core::Game g(config);

    bool running = true;
    SDL_Event event;
    Uint64 lastTime = SDL_GetPerformanceCounter();


    auto& renderer = g.windowRenderer.renderer;

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
                    g.board.p2.move(-1.0f, dt, g.board);
                    break;
                case SDLK_DOWN:
                    g.board.p2.move(1.0f, dt, g.board);
                    break;
                case SDLK_z:
                    g.board.p1.move(-1.0f, dt, g.board);
                    break;
                case SDLK_s:
                    g.board.p1.move(1.0f, dt, g.board);
                    break;
                case SDLK_e:
                    g.board.p2.useItem(&g.board.b);
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