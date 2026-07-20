#include "menuManager.h"

namespace UI
{

	void MenuManager::init(SDL_Renderer* r, const std::string& fontPath, int fontSize, SDL_Color c)
	{
		auto font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if (font)
		{
			buildMenus(r, font, c);
			TTF_CloseFont(font);
			currentMenu = &mainMenu;
		}
		else
			return;
	}

	void MenuManager::render(SDL_Renderer* r)
	{
		if (currentMenu) currentMenu->render(r);
	}

	Action MenuManager::activate()
	{
		if (currentMenu)
		{
			return currentMenu->activate();
		}
		return {MenuID::None,GameAction::None};
	}

	void MenuManager::returnBack()
	{
		if(menuHistory.empty())
			return;

		auto& menu = menuHistory.top();
		currentMenu = menu;
		menuHistory.pop();
	}

	void MenuManager::setCurrentMenu(MenuID id)
	{
		switch (id)
		{
		case UI::MenuID::Main:
			menuHistory.push(currentMenu);
			currentMenu = &mainMenu;
			currentMenu->updateSelection();
			break;
		case UI::MenuID::Solo:
			menuHistory.push(currentMenu);
			currentMenu = &soloMenu;
			currentMenu->updateSelection();
			break;
		case UI::MenuID::Multiplayer:
			menuHistory.push(currentMenu);
			currentMenu = &multiMenu;
			currentMenu->updateSelection();
			break;
		case UI::MenuID::OnlineIP:
			menuHistory.push(currentMenu);
			currentMenu = &ipMenu;
			currentMenu->updateSelection();
			break;
		case UI::MenuID::Options:
			menuHistory.push(currentMenu);
			currentMenu = &optionsMenu;
			currentMenu->updateSelection();
			break;
		case UI::MenuID::Rules:
			menuHistory.push(currentMenu);
			currentMenu = &rulesMenu;
			currentMenu->updateSelection();
			break;
		default:
			break;
		}
	}

	void MenuManager::moveUp()
	{
		currentMenu->moveUp();
	}

	void MenuManager::moveDown()
	{
		currentMenu->moveDown();
	}

	void MenuManager::buildMenus(SDL_Renderer* r, TTF_Font* font, SDL_Color c)
	{
		printf("Building menus...\n");

		for (auto& desc : mainMenuButtons)
		{	
			mainMenu.addBtn(Button(desc, r, font, c));
			printf("Added : %s\n", desc.txt.data());
		}

		for (auto& desc : multiPlayerButtons)
		{
			multiMenu.addBtn(Button(desc, r, font, c));
			printf("Added : %s\n", desc.txt.data());
		}

		for (auto& desc : soloMenuButtons)
		{
			soloMenu.addBtn(Button(desc, r, font, c));
			printf("Added : %s\n", desc.txt.data());
		}

		ipMenu.addBtn(Button(IpMenuButtons[0], r, font, c));

		for (auto& desc : optionsButtons)
		{
			optionsMenu.addBtn(Button(desc, r, font, c));
			printf("Added : %s\n", desc.txt.data());
		}
	}
}