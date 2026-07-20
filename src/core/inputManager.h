#pragma once
#include <unordered_map>
#include <SDL2/SDL.h>

constexpr int NUM_KEYS = 8;

namespace System
{
	class InputManager
	{
	public:

		void update();
		bool isKeyDown(SDL_Scancode key);
		bool isKeyPressed(SDL_Scancode key);

	private:
		const Uint8* currentKeys{ nullptr };
		Uint8 previousKeys[SDL_NUM_SCANCODES]{};
	};
}