#include "menuManager.h"

namespace UI
{
	Action MenuManager::activate()
	{
		if (currentMenu)
		{
			return currentMenu->activate();
		}
	}

	void MenuManager::setCurrentMenu(MenuID id)
	{
		switch (id)
		{
		case UI::MenuID::Main:
			menuHistory.push(currentMenu);
			currentMenu = &mainMenu;
			break;
		case UI::MenuID::Solo:
			menuHistory.push(currentMenu);
			currentMenu = &soloMenu;
			break;
		case UI::MenuID::Multiplayer:
			menuHistory.push(currentMenu);
			currentMenu = &multiMenu;
			break;
		case UI::MenuID::OnlineIP:
			menuHistory.push(currentMenu);
			currentMenu = &ipMenu;
			break;
		case UI::MenuID::Options:
			menuHistory.push(currentMenu);
			currentMenu = &optionsMenu;
			break;
		case UI::MenuID::Rules:
			menuHistory.push(currentMenu);
			currentMenu = &rulesMenu;
			break;
		default:
			break;
		}
	}

	void MenuManager::createButtons(SDL_Renderer* r, TTF_Font* font, SDL_Color c)
	{
		for (auto& desc : mainMenuButtons)
		{	
			mainMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : multiPlayerButtons)
		{
			multiMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : soloMenuButtons)
		{
			soloMenu.addBtn(Button(desc, r, font, c));
		}

		ipMenu.addBtn(Button(IpMenuButtons[0], r, font, c));

		for (auto& desc : optionsButtons)
		{
			optionsMenu.addBtn(Button(desc, r, font, c));
		}
	}
}