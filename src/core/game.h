#pragma once
#include "window.h"
#include "player.h"


namespace Core
{
	struct View;

	enum GameMode
	{
		SINGLEPLAYER,MULTIPLAYER
	};

	struct Game
	{
		WindowRenderer windowRenderer;
		GameMode mode;
		Entities::Ball ball;
		//Entities::PlayerStick player_one;
		//Entities::PlayerStick player_two; temporary
		std::vector<Entities::Item> items;

		Game()
		{
			init();
		}

		void initBoard();
		void init();
		bool isGameFinished();
		void quit();
	};
}