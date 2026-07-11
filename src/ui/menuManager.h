#pragma once

#include "menu.h"

#include <stack>

namespace UI
{
	class MenuManager
	{
	public:

		GameAction activate();
		void setCurrentMenu(MenuID id);

		Menu* getCurrentMenu() { if (currentMenu) return currentMenu; }

	private:
		Menu* currentMenu{ nullptr };
		std::stack<Menu*> menuHistory{};

		Menu mainMenu{};
		Menu soloMenu{};
		Menu multiMenu{};
		Menu optionsMenu{};
		Menu rulesMenu{};
		Menu ipMenu{};

	};
}