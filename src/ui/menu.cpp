#include "menu.h"
constexpr SDL_Color MENU_WHITE = { 255,255,255,255 };
constexpr SDL_Color MENU_YELLOW = { 255,255,0,255 };

namespace UI
{
	Action Menu::activate()
	{

		if (selectedIndex < rows.size() && selectedIndex >= 0)
		{
			auto btn = rows[selectedIndex].item->onActivate();

			return btn;
		}
		else
			return { MenuID::None, GameAction::None };
	}


	void Menu::left()
	{
		if (!rows.empty())
			rows[selectedIndex].item->onLeft();
	}

	void Menu::right()
	{
		if (!rows.empty())
			rows[selectedIndex].item->onRight();
	}

	void Menu::moveDown()
	{
		if (rows.empty()) return;

		selectedIndex++;
		if (selectedIndex >= rows.size())
		{
			selectedIndex = 0;
		}
	}

	void Menu::moveUp()
	{
		if (rows.empty()) return;

		selectedIndex--;
		if (selectedIndex < 0)
		{
			selectedIndex = static_cast<short>(rows.size() - 1);
		}
	}

	void Menu::render(SDL_Renderer* renderer)
	{
		if (!rows.empty())
		{
			for (std::size_t i{0}; i < rows.size(); i++)
			{
				auto& r = rows[i];

				const std::string now_name = r.item->label();

				if (now_name != r.shownLabel)
				{
					setLayerText(r.text, renderer, font, now_name, MENU_WHITE);
					r.shownLabel = now_name;
				}

				if ( (int)i == selectedIndex )
				{
					r.text.setColor(MENU_YELLOW);
				}
				else
				{
					r.text.setColor(MENU_WHITE);
				}

				r.text.render(renderer);
			}
		}
	}
}