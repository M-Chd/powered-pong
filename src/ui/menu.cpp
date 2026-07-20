#include "menu.h"
#define Yellow SDL_Color yellow{255,255,0,255};

namespace UI
{
	Action Menu::activate()
	{

		if (selectedIndex < buttonList.size() && selectedIndex >= 0)
		{
			auto& btn = buttonList[selectedIndex];

			return { btn.getAction().menuid,btn.getAction().action };
		}
		else
			return { MenuID::None,GameAction::None };
	}

	void Menu::updateSelection()
	{
		for (size_t i = 0; i < buttonList.size(); ++i)
		{
			if (i == selectedIndex)
				buttonList[i].setSelected(true);
			else
				buttonList[i].setSelected(false);
		}
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
			selectedIndex = static_cast<short>(buttonList.size() - 1);
		}
		updateSelection();
	}

	void Button::render(SDL_Renderer* renderer)
	{
		if (selected)
		{
			txt.setColor({ 255,255,0,255 }); // yellow
			txt.render(renderer);
		}
		else
		{
			txt.setColor({ 255,255,255,255 }); // white
			txt.render(renderer);
		}
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