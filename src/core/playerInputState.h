#pragma once

#include "inputManager.h"

namespace Core
{
	struct PlayerInputState { bool moveUp{ false }; bool moveDown{ false }; };

	inline PlayerInputState buildLocalInput(SDL_Scancode upKey, SDL_Scancode downKey, System::InputManager& inputmgr)
	{
		PlayerInputState in;
		in.moveUp = inputmgr.isKeyDown(upKey);
		in.moveDown = inputmgr.isKeyDown(downKey);
		return in;
	}
}