#include "menuManager.h"

namespace UI
{

	void MenuManager::init(SDL_Renderer* r, const std::string& fontPath, int fontSize, SDL_Color c)
	{
		auto font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if (font)
		{
			buildMenus(r, font, c);

			initRules(r, font, c);

			TTF_CloseFont(font);

			currentMenu = &mainMenu;
			currentMenu->getButtonAt(0)->setSelected(true);
		}
		else
			return;
	}

	void MenuManager::render(SDL_Renderer* r)
	{
		if (currentMenu) currentMenu->render(r);

		if (currentMenuID == MenuID::Rules)
		{
			SDL_RenderCopy(
			r,
			rulesTexture,
			nullptr,
			&ruleRect
			);
		}

	}

	void MenuManager::initRules(
		SDL_Renderer* r,
		TTF_Font* font,
		SDL_Color color)
	{
		static const char* RulesText =
		R"(|Movements:| Z or W to go UP, S to go DOWN if you play in Local Multiplayer or Online Multiplayer, the inputs for the second player are KEY UP and KEY DOWN
|Items:| Items can spawn on the map if allowed within a specific cooldown time.)";

		SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(
			font,
			RulesText,
			color,
			1000
		);

		rulesTexture = SDL_CreateTextureFromSurface(r, surface);

		ruleRect = {
			100,
			150,
			surface->w,
			surface->h
		};

		SDL_FreeSurface(surface);
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
		auto& menuId = menuIDHistory.top();
		currentMenu = menu;
		currentMenuID = menuId;
		menuHistory.pop();
		menuIDHistory.pop();
	}

	void MenuManager::setCurrentMenu(MenuID id)
	{
		switch (id)
		{
		case UI::MenuID::Main:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &mainMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Main;
			break;
		case UI::MenuID::Pause:
			currentMenu = &pauseMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Pause;
			break;
		case UI::MenuID::Solo:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &soloMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Solo;
			break;
		case UI::MenuID::Multiplayer:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &multiMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Multiplayer;
			break;
		case UI::MenuID::OnlineIP:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &ipMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::OnlineIP;
			break;
		case UI::MenuID::Options:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &optionsMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Options;
			break;
		case UI::MenuID::Rules:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &rulesMenu;
			currentMenu->updateSelection();
			currentMenuID = MenuID::Rules;
			break;
		default:
			break;
		}
	}

	void MenuManager::setLastCurrentMenu()
	{
		currentMenu = menuHistory.top();
		currentMenu->updateSelection();
		currentMenuID = menuIDHistory.top();
		menuHistory.pop();
		menuIDHistory.pop();
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
		}

		for (auto& desc : multiPlayerButtons)
		{
			multiMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : soloMenuButtons)
		{
			soloMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : IpMenuButtons)
		{
			ipMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : optionsButtons)
		{
			optionsMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : pauseButtons)
		{
			pauseMenu.addBtn(Button(desc, r, font, c));
		}

		for (auto& desc : rulesButton)
		{
			rulesMenu.addBtn(Button(desc, r, font, c));
		}

	}
}