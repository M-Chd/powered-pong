#pragma once
#include "window.h"
#include "player.h"


namespace Core
{

	enum GameMode
	{
		SINGLEPLAYER,MULTIPLAYER
	};

	struct Game
	{
		WindowRenderer windowRenderer;
		GameMode mode;
		Entities::Ball ball;
		Entities::PlayerStick player_one;
		//Entities::PlayerStick player_two; temporary
		std::vector<Entities::Item> items;

		void initBoard();
		void init();
		bool isGameFinished();
		void quit();
	};
}