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
		Entities::PlayerStick player_one;
		//Entities::PlayerStick player_two; temporary
		Entities::Ball ball;
		std::vector<Entities::Item> items;
		GameMode mode;

		void initBoard();
		void init();
		bool isGameFinished();
		void quit();
	};
}