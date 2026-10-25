#include "menuManager.h"

namespace UI
{

	void MenuManager::init(SDL_Renderer* r, Core::Rules& rules, const std::string& fontPath, int fontSize, SDL_Color c)
	{
		font = TTF_OpenFont(fontPath.c_str(), fontSize);

		if (font)
		{
			mainMenu.setFont(font);
			pauseMenu.setFont(font);
			soloMenu.setFont(font);
			playRulesMenu.setFont(font);
			multiMenu.setFont(font);
			optionsMenu.setFont(font);
			rulesMenu.setFont(font);
			ipMenu.setFont(font);

			buildMenus(rules);
			initRules(r, font, c);

			currentMenu = &mainMenu;
		}
		else
		{
			printf("Error: Font didn't load for the menus");
			return;
		}
	}

	void MenuManager::render(SDL_Renderer* r)
	{
		if (!font) return;

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

		if (!surface)
		{
			printf("Failed to render rules text: %s\n", TTF_GetError());
			return;
		}

		rulesTexture = SDL_CreateTextureFromSurface(r, surface);

		if (!rulesTexture)
		{
			printf("Failed to create rules texture: %s\n", SDL_GetError());
			SDL_FreeSurface(surface);
			return;
		}

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
			currentMenu->resetSelection();
			currentMenuID = MenuID::Main;
			break;
		case UI::MenuID::Pause:
			currentMenu = &pauseMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Pause;
			break;
		case UI::MenuID::Solo:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &soloMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Solo;
			break;
		case UI::MenuID::Multiplayer:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &multiMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Multiplayer;
			break;
		case UI::MenuID::OnlineIP:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &ipMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::OnlineIP;
			break;
		case UI::MenuID::Options:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &optionsMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Options;
			break;
		case UI::MenuID::Rules:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &rulesMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Rules;
			break;
		case UI::MenuID::Play_rules:
			menuHistory.push(currentMenu);
			menuIDHistory.push(currentMenuID);
			currentMenu = &playRulesMenu;
			currentMenu->resetSelection();
			currentMenuID = MenuID::Play_rules;
			break;
		default:
			break;
		}
	}

	void MenuManager::addButtons(Menu& menu, const ButtonDescription* first, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			const auto& des = first[i];

			menu.addItem(std::make_unique<ButtonItem>(std::string(des.txt), Action{ des.menuID,des.action }), des.position);
		}
	}

	void MenuManager::setLastCurrentMenu()
	{
		if (menuHistory.empty() || menuIDHistory.empty()) return;

		currentMenu = menuHistory.top();
		currentMenu->resetSelection();
		currentMenuID = menuIDHistory.top();
		menuHistory.pop();
		menuIDHistory.pop();
	}

	void MenuManager::onLeft()
	{
		if (currentMenu)
			currentMenu->left();
	}

	void MenuManager::onRight()
	{
		if (currentMenu)
			currentMenu->right();
	}

	void MenuManager::moveUp()
	{
		if (currentMenu)
			currentMenu->moveUp();
	}

	void MenuManager::moveDown()
	{
		if (currentMenu)
			currentMenu->moveDown();
	}

	void MenuManager::buildMenus(Core::Rules& rules)
	{
		printf("Building menus...\n");

		addButtons(mainMenu, mainMenuButtons.data(), mainMenuButtons.size());
		addButtons(pauseMenu, pauseButtons.data(), pauseButtons.size());
		addButtons(soloMenu, soloMenuButtons.data(), soloMenuButtons.size());
		addButtons(multiMenu, multiPlayerButtons.data(), multiPlayerButtons.size());
		addButtons(optionsMenu, optionsButtons.data(), optionsButtons.size());
		addButtons(rulesMenu, rulesButtons.data(), rulesButtons.size());
		addButtons(ipMenu, IpMenuButtons.data(), IpMenuButtons.size());
		
		//name,value,min,max,step
		playRulesMenu.addItem(std::make_unique<RangeItem<unsigned int>>((std::string("Win score")), rules.winScore, 0u, 99u, 1u),
			{ MENU_DEFAULT_X, MENU_FIRST_Y + MENU_SPACING * 0 });
		playRulesMenu.addItem(std::make_unique<RangeItem<unsigned int>>((std::string("Max item count")), rules.maxItemCount, 0u, 5u, 1u),
			{ MENU_DEFAULT_X,MENU_FIRST_Y + MENU_SPACING * 1 });
		playRulesMenu.addItem(std::make_unique<RangeItem<unsigned int>>((std::string("Ball number")), rules.numberOfBalls, 0u, 4u, 1u),
			{ MENU_DEFAULT_X,MENU_FIRST_Y + MENU_SPACING * 2 });
		playRulesMenu.addItem(std::make_unique<ToggleItem>((std::string("Toggle item")), rules.allowPowerUps),
			{ MENU_DEFAULT_X,MENU_FIRST_Y + MENU_SPACING * 3 });
		playRulesMenu.addItem(std::make_unique<ButtonItem>((std::string("Back")), Action{ MenuID::None,GameAction::Back }),
			{ MENU_DEFAULT_X,MENU_FIRST_Y + MENU_SPACING * 4 });

		printf("Building menus done.");
	}
}