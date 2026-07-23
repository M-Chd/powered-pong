#pragma once

#include "game.h"

namespace Core
{	
	class Rules
	{
	public:
		Rules(unsigned int winScore = 5, unsigned int maxItCnt = 1, unsigned int nbrPlayers = 2,
			unsigned int nbrBalls = 1, float itemRdRate = 0.10f, 
			bool allowPwUps = true) 
			: winScore(winScore), 
			maxItemCount(maxItCnt), numberOfPlayers(nbrPlayers), numberOfBalls(nbrBalls),
			itemRdmRate(itemRdRate), allowPowerUps(allowPwUps) { }

		int getWinScore() const { return winScore; }
		int getMaxItemCount() const { return maxItemCount; }
		int getNumberOfPlayer() const { return numberOfPlayers; }
		int getNumberOfBalls() const { return numberOfBalls; }
		float getItemRndmRate() const { return itemRdmRate; }
		bool isPowerUpsAllowed() const { return allowPowerUps; }

	private:
		unsigned int	winScore{5};
		unsigned int	maxItemCount{1};
		unsigned int	numberOfPlayers{ 2 };
		unsigned int	numberOfBalls{ 1 };
		float			itemRdmRate{ 0.10f };
		bool			allowPowerUps{ true };
	};

	class Match
	{
	public:

		Match(UI::GameAction&);

		void update(int);
		void render(SDL_Renderer*);

		void setPlayerTwoType(Entities::PlayerType type) { playerTwo.setType(type); }
		std::vector<Entities::Item>& getItems() { return items; }
		Entities::Item* getItemAt(int); 
		Entities::Player& getPlayerOne() { return playerOne; }
		Entities::Player& getPlayerTwo() { return playerTwo; }
		Entities::Ball& getBall() { return ball; }
		void setRules(Rules& r) { rules = r; }
		Rules& getRules() { return rules; }
		Board& getBoard() { return board; }

	private:
		Entities::Player playerOne;
		Entities::Player playerTwo;
		Entities::Ball	 ball;
		Board board;
		std::vector<Entities::Item> items;
		Rules rules;
	};
}