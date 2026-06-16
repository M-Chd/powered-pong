#pragma once
#include <unordered_map>
#include <SDL2/SDL.h>

constexpr int NUM_KEYS = 8;

namespace Core
{
	class InputManager
	{
	public:

		void update();
		bool isKeyDown(SDL_Scancode key);

	private:
		const Uint8* _keyBoardState = nullptr;
	};
}