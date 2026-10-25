#pragma once

#include "IinputButton.h"

namespace UI
{
    struct InputIP : public IinputEntry
    {
        InputIP() = default;
        ~InputIP();

        void init(SDL_Renderer* renderer,
                  const std::string& fontPath,
                  int fontSize,
                  SDL_Color color,
                  Util::Vec2 position) override;

        void handleEvent(const SDL_Event& e) override;
        void render(SDL_Renderer* renderer) override;
        void updateTexture() override;

        std::string getIP() const { return ip; }
        bool isValidIP() const;
        void clear() override;

    private:
        std::string ip{ "127.0.0.1" };
        SDL_Renderer* renderer{ nullptr };
        TTF_Font* font{ nullptr };
        SDL_Color color{255,255,255,255};
        SDL_Texture* texture{ nullptr };
        int textWidth{ 0 }, textHeight{ 0 };
        Util::Vec2 position{};
    };
}