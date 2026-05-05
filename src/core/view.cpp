#include "view.h"

void UI::drawCircle(SDL_Renderer* renderer,float radius, Util::Vec2 position, SDL_Color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

    int cx = static_cast<int>(position.x);
    int cy = static_cast<int>(position.y);
    int r = static_cast<int>(radius);

    for (int w = -r; w <= r; w++)
    {
        for (int h = -r; h <= r; h++)
        {
            if (w * w + h * h <= r * r)
            {
                SDL_RenderDrawPoint(renderer, cx + w, cy + h);
            }
        }
    }
}
