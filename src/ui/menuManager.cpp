#include "menuManager.h"

namespace UI
{
	GameAction MenuManager::activate()
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
}