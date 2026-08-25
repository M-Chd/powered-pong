#pragma once

#include "util/vector2.hpp"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace UI
{
    struct InputIP
    {
        InputIP() = default;
        ~InputIP();

        void init(SDL_Renderer* renderer,
                  const std::string& fontPath,
                  int fontSize,
                  SDL_Color color,
                  Util::Vec2 position);

        void handleEvent(const SDL_Event& e);
        void render(SDL_Renderer* renderer);
        void updateTexture();

        std::string getIP() const { return ip; }
        bool isValidIP() const;
        void clear();

    private:
        SDL_Renderer* renderer = nullptr;
        TTF_Font* font = nullptr;
        SDL_Color color{255,255,255,255};
        Util::Vec2 position;
        std::string ip = "127.0.0.1";
        SDL_Texture* texture = nullptr;
        int textWidth = 0, textHeight = 0;
    };
}