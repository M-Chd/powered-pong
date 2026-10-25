#pragma once

#include "util/vector2.hpp"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace UI
{
	class IinputEntry
	{
    public:
        virtual void init(SDL_Renderer* renderer,
                  const std::string& fontPath,
                  int fontSize,
                  SDL_Color color,
                  Util::Vec2 position) = 0;

        virtual void handleEvent(const SDL_Event& e) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
        virtual void updateTexture() = 0;
        virtual void clear() = 0;
	};
}