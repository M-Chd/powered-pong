#include "board.h"

void Core::Board::drawBoard(SDL_Renderer* renderer) const

{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect = { offsetX,offsetY,l,h };
	SDL_RenderDrawRect(renderer, &rect);
}

void Core::Board::drawBall(SDL_Renderer* renderer)
{
	b.draw(renderer);
}