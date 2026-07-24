#pragma once

#include "player.h"
#include "ball.h"
#include "board.h"
#include "inputManager.h"
#include "difficulty.h"
#include "matchEvent.h"

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

		unsigned int getWinScore() const { return winScore; }
		unsigned int getMaxItemCount() const { return maxItemCount; }
		unsigned int getNumberOfPlayer() const { return numberOfPlayers; }
		unsigned int getNumberOfBalls() const { return numberOfBalls; }
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

		enum class MatchType
		{
			Solo,Multi
		};

		struct MatchSettings
		{
			MatchType type{};
			GameDifficulty difficulty{};
		};

	public:

		Match(){}
		Match(MatchSettings);

		MatchEvent update(float, System::InputManager&);
		void render(SDL_Renderer*);
		bool isFinished();
		void updateAI(float);
		MatchEvent checkPoint();

		void setPlayerTwoType(Entities::PlayerType type) { playerTwo.setType(type); }
		std::vector<Entities::Item>& getItems() { return items; }
		Entities::Item* getItemAt(int); 
		Entities::Player& getPlayerOne() { return playerOne; }
		Entities::Player& getPlayerTwo() { return playerTwo; }
		Entities::Ball& getBall() { return ball; }
		Board& getBoard() { return board; }
		void setRules(Rules& r) { rules = r; }
		Rules& getRules() { return rules; }
	private:

		void setupRound(Entities::Player&,const Util::Vec2&);

	private:
		Entities::Player playerOne;
		Entities::Player playerTwo;
		Entities::Ball	 ball;
		Board board;
		std::vector<Entities::Item> items;
		Rules rules;
	};
}