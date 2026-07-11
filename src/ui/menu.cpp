#include "menu.h"

namespace UI
{
	GameAction Menu::activate()
	{
		if (selectedIndex < buttonList.size() && selectedIndex >= 0)
			return buttonList[selectedIndex].getAction();
		else
			return GameAction::None;
	}

	void Menu::moveDown()
	{
		selectedIndex++;
		if (selectedIndex > buttonList.size())
		{
			selectedIndex = 0;
		}
	}

	void Menu::moveUp()
	{
		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = static_cast<short>(buttonList.size());
		}
	}

	void Button::render(SDL_Renderer* renderer)
	{
		txt.render(renderer);
	}

	void Menu::render(SDL_Renderer* renderer)
	{
		if (!buttonList.empty())
		{
			for (auto& b : buttonList)
			{
				b.render(renderer);
			}
		}
	}
}