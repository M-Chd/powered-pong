#include "core/game.h"

int main(int argc, char* argv[])
{
    Core::Game g;

    g.parseArgs(argc, argv);

    SDL_Event event;
    Uint64 lastTime = SDL_GetPerformanceCounter();

    while (g.running)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (now - lastTime) /
                   static_cast<float>(SDL_GetPerformanceFrequency());
        lastTime = now;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                g.running = false;

            if(g.textInputActive)
                g.handleEvent(event);
        }

        g.inputmngr.update();

        g.update(dt);

        g.render();
    }

    g.quit();

    return 0;
}