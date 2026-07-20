#include "inputManager.h"

namespace System
{
	void InputManager::update()
	{
		if (!currentKeys)
        currentKeys = SDL_GetKeyboardState(nullptr);

		memcpy(previousKeys, currentKeys, SDL_NUM_SCANCODES);

		SDL_PumpEvents();
		currentKeys = SDL_GetKeyboardState(nullptr);
	}

	bool InputManager::isKeyDown(SDL_Scancode key)
	{
		return currentKeys && currentKeys[key];
	}

	bool InputManager::isKeyPressed(SDL_Scancode key)
	{
		return currentKeys && currentKeys[key] && !previousKeys[key];
	}
}