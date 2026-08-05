#pragma once

#include "menu.h"

#include <stack>

namespace UI
{
	class MenuManager
	{
	public:

		void init(SDL_Renderer*,
			const std::string& fontpath,
			int fontsize,
			SDL_Color);

		void render(SDL_Renderer*);

		void moveUp();
		void moveDown();

		Action activate();
		void returnBack();

		void setCurrentMenu(MenuID id);

		Menu* getCurrentMenu() { if (currentMenu) return currentMenu; }
		MenuID getCurrentMenuID() const { return currentMenuID; }

	private:

		void buildMenus(SDL_Renderer*,
			TTF_Font*,
			SDL_Color);

	private:
		Menu* currentMenu{ nullptr };
		std::stack<Menu*> menuHistory{};
		MenuID currentMenuID{ MenuID::Main };

		Menu mainMenu{};
		Menu soloMenu{};
		Menu multiMenu{};
		Menu optionsMenu{};
		Menu rulesMenu{};
		Menu ipMenu{};

	};
}