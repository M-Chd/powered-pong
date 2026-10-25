#pragma once

#include "menu.h"
#include "core/match.h"

#include <stack>

namespace UI
{
	class MenuManager
	{
	public:

		~MenuManager()
		{
			if(font)
				TTF_CloseFont(font);
		}

		void init(SDL_Renderer*,
			Core::Rules&,
			const std::string& fontpath,
			int fontsize,
			SDL_Color);

		void initRules(SDL_Renderer* r, TTF_Font* font, SDL_Color color);

		void render(SDL_Renderer*);

		void moveUp();
		void moveDown();
		void onLeft();
		void onRight();

		Action activate();
		void returnBack();

		void addButtons(Menu&, const ButtonDescription*, size_t);

		void setCurrentMenu(MenuID id);

		Menu* getCurrentMenu() { return currentMenu; }
		MenuID getCurrentMenuID() const { return currentMenuID; }

		void setLastCurrentMenu();
	private:

		void buildMenus(Core::Rules&);

	private:
		Menu* currentMenu{ nullptr };
		std::stack<Menu*> menuHistory{};
		std::stack<MenuID> menuIDHistory{};
		MenuID currentMenuID{ MenuID::Main };

		Menu mainMenu{};
		Menu pauseMenu{};
		Menu soloMenu{};
		Menu playRulesMenu{};
		Menu multiMenu{};
		Menu optionsMenu{};
		Menu rulesMenu{};
		Menu ipMenu{};

		SDL_Texture* rulesTexture{ nullptr };
		TTF_Font* font{ nullptr };
		SDL_Rect ruleRect{};

	};
}