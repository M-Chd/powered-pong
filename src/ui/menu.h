#pragma once

#include "uiElement.h"
#include "buttonList.hpp"

#include <vector>

namespace UI
{
	struct Action
	{
		MenuID menuid;
		GameAction action;
	};

	class Button
	{
	public:

		Button(const ButtonDescription& desc,
			SDL_Renderer* r,
			TTF_Font* font,
			SDL_Color color) : txt(desc.position), action{ desc.menuID,desc.action }, 
			normalColor(color), selectedColor({ 255,255,0,255 })
		{
			setLayerText(txt, r, font, desc.txt.data(), color);
		}


		Action getAction() const { return action; }
		void render(SDL_Renderer* renderer);

		void setSelected(bool selected) { this->selected = selected; }

	private:
		UILayer txt;
		Action action{};
		SDL_Color normalColor{};
		SDL_Color selectedColor{};
		bool selected{ false };
	};

	class Menu
	{
	public:

		Menu()
		{
			buttonList.reserve(5);
		}

		void addBtn(Button&& b) { buttonList.emplace_back(std::move(b)); }
		std::vector<Button>& getButtonsList() { return buttonList; }

		Button* getButtonAt(int x)
		{ 
			if (x >= 0 && x < buttonList.size())
				return &buttonList[x];
			else
				return nullptr;
		}

		void render(SDL_Renderer* renderer);
		void moveUp();
		void moveDown();
		Action activate();

		void updateSelection();

	private:
		std::vector<Button> buttonList;
		short selectedIndex{ 0 };
	};
}