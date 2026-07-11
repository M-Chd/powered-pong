#pragma once

#include "uiElement.h"

#include <vector>

namespace UI
{
	enum class MenuID
	{
		Main,
		Solo,
		Multiplayer,
		OnlineIP,
		Options,
		Rules
	};

	enum class GameAction
	{
		None,

		StartSoloEasy,
		StartSoloMedium,
		StartSoloHard,

		StartLocalMultiplayer,

		Quit
	};

	class Button
	{
	public:

		GameAction getAction() const { return action; }
		MenuID getMenuID() const { return actionMenu; }
		void render(SDL_Renderer* renderer);

	private:
		UILayer txt;
		MenuID actionMenu;
		GameAction action;
	};

	class Menu
	{
	public:

		Menu()
		{
			buttonList.reserve(5);
		}

		void addBtn(Button&& b) { buttonList.emplace_back(std::move(b)); }

		void render(SDL_Renderer* renderer);
		void moveUp();
		void moveDown();
		GameAction activate();

	private:
		std::vector<Button> buttonList;
		short selectedIndex{ 0 };
	};
}