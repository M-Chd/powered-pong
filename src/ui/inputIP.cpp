#include "inputIP.h"
#include <cctype>
#include <vector>
#include <sstream>

namespace UI
{
    InputIP::~InputIP()
    {
        if (font)
            TTF_CloseFont(font);
        if (texture)
            SDL_DestroyTexture(texture);
    }

    void InputIP::init(SDL_Renderer* r,
                       const std::string& fontPath,
                       int fontSize,
                       SDL_Color c,
                       Util::Vec2 pos)
    {
        renderer = r;
        color = c;
        position = pos;

        font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font)
        {
            printf("InputIP: Failed to load font: %s\n", TTF_GetError());
            return;
        }

        updateTexture();
    }

    void InputIP::updateTexture()
    {
        if (!renderer || !font)
            return;

        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        std::string display = "IP: " + ip;
        SDL_Surface* surface = TTF_RenderText_Blended(font, display.c_str(), color);
        if (!surface)
        {
            printf("InputIP: TTF_RenderText_Blended error: %s\n", TTF_GetError());
            return;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            printf("InputIP: SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        }
        else
        {
            textWidth = surface->w;
            textHeight = surface->h;
        }
        SDL_FreeSurface(surface);
    }

    void InputIP::render(SDL_Renderer* r)
    {
        if (!texture)
            return;

        SDL_Rect dst = {
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            textWidth,
            textHeight
        };
        SDL_RenderCopy(r, texture, nullptr, &dst);
    }

    void InputIP::handleEvent(const SDL_Event& e)
    {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (!ip.empty())
                {
                    ip.pop_back();
                    updateTexture();
                }
            }
            else if (e.key.keysym.sym == SDLK_RETURN)
            {
                // TODO for ENTER key
            }
        }
        else if (e.type == SDL_TEXTINPUT)
        {
            const std::string& input = e.text.text;
            for (char c : input)
            {
                if (std::isalnum(c) || c == '.' || c == ':')
                {
                    if (ip.length() < 15) // IPV4 max length
                        ip.push_back(c);
                }
            }
            updateTexture();
        }
    }

    bool InputIP::isValidIP() const
    {
        if (ip == "localhost")
            return true;

        // Découper par '.'
        std::vector<std::string> parts;
        std::stringstream ss(ip);
        std::string token;
        while (std::getline(ss, token, '.'))
            parts.push_back(token);

        if (parts.size() != 4)
            return false;

        for (const auto& part : parts)
        {
            if (part.empty())
                return false;
            for (char c : part)
                if (!std::isdigit(c))
                    return false;
            int num = std::stoi(part);
            if (num < 0 || num > 255)
                return false;
        }
        return true;
    }

    void InputIP::clear()
    {
        ip.clear();
        updateTexture();
    }
}