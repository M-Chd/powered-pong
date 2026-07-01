#include "infoLayer.h"

namespace UI
{
	InfoLayer::InfoLayer(const std::string& fontPath, float x, float y, const std::string& text, SDL_Color c, int size)
		: x(x), y(y), text(text), color(c)
	{
		font = TTF_OpenFont(fontPath.c_str(), size);

		if (!font)
		{
			printf("Error loading font: %s\n", TTF_GetError());
			TTF_CloseFont(font);
			return;
		}
	}

	void InfoLayer::Render(SDL_Renderer* r)
	{
		if (SDL_RenderCopy(r, texture, NULL, &destRect) != 0)
		{
			printf("%s\n",SDL_GetError());
			return;
		}
	}

	InfoLayer::~InfoLayer()
	{
		TTF_CloseFont(font);
		SDL_DestroyTexture(texture);
	}

	void InfoLayer::updateTexture(SDL_Renderer* r)
	{
		SDL_DestroyTexture(texture);

		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (!surface)
		{
			printf("Error while creating surface...\n");
			return;
		}

		texture = SDL_CreateTextureFromSurface(r, surface);

		if (!texture)
		{
			printf("Error while loading Texture...\n");
			SDL_FreeSurface(surface);
			return;
		}

		destRect.w = surface->w;
		destRect.h = surface->h;
		destRect.x = x;
		destRect.y = y;

		SDL_FreeSurface(surface);
	}

	void InfoLayer::setPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
		destRect.x = x;
		destRect.y = y;
	}

	std::string InfoLayer::getText() const
	{
		return text;
	}

	ScoreLayer::ScoreLayer(const std::string& fontPath, int fontSize, float x, float y, SDL_Color c, Entities::Player& playerPtr)
		: InfoLayer(fontPath, x, y, "", c, fontSize)
	{
		this->playerPtr = &playerPtr;
		setText();
	}

	void ScoreLayer::setText()
	{
		this->text = "Score: " + std::to_string(playerPtr->getScore());
	}
}