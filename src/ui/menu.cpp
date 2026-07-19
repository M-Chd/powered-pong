#include "menu.h"

namespace UI
{
	Action Menu::activate()
	{
		auto& btn = buttonList[selectedIndex];

		if (selectedIndex < buttonList.size() && selectedIndex >= 0)
			return { btn.getAction().menuid,btn.getAction().action };
		else
			return { MenuID::None,GameAction::None };
	}

	void Menu::moveDown()
	{
		selectedIndex++;
		if (selectedIndex >= buttonList.size())
		{
			selectedIndex = 0;
		}
		updateSelection();
	}

	void Menu::moveUp()
	{
		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = static_cast<short>(buttonList.size());
		}
		updateSelection();
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