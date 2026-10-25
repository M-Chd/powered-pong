#pragma once

#include "uiElement.h"
#include "buttonList.hpp"
#include "menuItem.h"

#include <vector>
#include <memory>

namespace UI
{
	class Menu
	{
	public:

		struct Row
		{
			std::unique_ptr<MenuItem> item;
			UILayer text;
			std::string shownLabel;
		};

		Menu()
		{
			rows.reserve(5);
		}

		void render(SDL_Renderer* renderer);
		void moveUp();
		void moveDown();
		void left();
		void right();
		Action activate();
		void setFont(TTF_Font* f) { font = f; }
		void addItem(std::unique_ptr<MenuItem> item, Util::Vec2 position) 
		{ 
			rows.emplace_back(Row{
				.item = std::move(item),
				.text = UILayer(position,LayerType::None),
				.shownLabel{} });
		}
		void resetSelection() { selectedIndex = 0; }

	private:
		std::vector<Row> rows;
		TTF_Font* font{ nullptr };
		short selectedIndex{ 0 };
	};
}