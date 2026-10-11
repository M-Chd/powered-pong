#pragma once

#include "entities/player.h"
#include "entities/ball.h"
#include "board.h"
#include "difficulty.h"
#include "matchEvent.h"
#include "aiController.h"
#include "entities/activeEffect.h"
#include "playerInputState.h"

namespace Core
{	
	struct Rules
	{
		unsigned int	winScore{ 5 };
		unsigned int	maxItemCount{ 1 };
		unsigned int	numberOfPlayers{ 2 };
		unsigned int	numberOfBalls{ 1 };
		float			itemSpawnTimer{ 10.f };
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
			Rules rules{};
		};

	public:

		Match(){}
		Match(MatchSettings settings)
		{
			rules = settings.rules;
			itemspawnTimer = 0.f;
		}

		MatchEvent update(float, const PlayerInputState&, const PlayerInputState&);
		void render(SDL_Renderer*);
		bool isFinished();
		void updateAI(float);
		void updateItems(float);
		MatchEvent checkPoint();
		void checkItemCollisions();
		void itemSpawn();

		void setPlayerTwoType(Entities::PlayerType type) { playerTwo.setType(type); }
		std::vector<Entities::Item>& getItems() { return items; }
		Entities::Item* getItemAt(int); 
		Entities::Player& getPlayerOne() { return playerOne; }
		Entities::Player& getPlayerTwo() { return playerTwo; }
		Entities::Ball& getBall() { return ball; }
		Board& getBoard() { return board; }
		void setRules(Rules r) { rules = r; }
		Rules& getRules() { return rules; }

	private:

		void setupRound(Entities::Player&,const Util::Vec2&);

	private:
		Entities::Player playerOne;
		Entities::Player playerTwo;
		Entities::Ball	 ball;
		Board board;
		std::vector<Entities::Item> items;
		std::vector<Entities::ActiveEffect> activeEffects;
		Rules rules;
		AIController aiController;
		float itemspawnTimer;
	};
}