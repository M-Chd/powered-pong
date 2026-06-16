#include "inputManager.h"

namespace Core
{
	void InputManager::update()
	{
		_keyBoardState = SDL_GetKeyboardState(nullptr);
	}

	bool InputManager::isKeyDown(SDL_Scancode key)
	{
		return _keyBoardState[key];
	}
}