#pragma once

#include "difficulty.h"
#include "entities/ball.h"
#include "entities/player.h"

namespace Core
{
	struct Board;

	enum class Decision
	{
		None,
		MoveUp,
		MoveDown,
	};

	class AIController
	{
	public:

		void setDifficulty(GameDifficulty);
		void update(float dt, Entities::Ball&, Entities::Player&, Board&);
		void chooseTarget(Entities::Ball&, Entities::Player&);
		void predictBallPosition(Entities::Ball&);
		void computeError();
		void makeDecision(Entities::Player&);
		void reset();
		Decision getDecision() const { return decision; }

	private:
		static float randomError(float range);

		GameDifficulty difficulty{ GameDifficulty::NONE };
		float reactionTimer{ 0.0f };
		float reactionDelay{ 0.0f };
		float predictionErrorRange{ 0.0f };
		float currentError{ 0.0f };
		float predictedY{ 0.0f };
		float targetY{ 0.0f };
		float deadZone{ 6.0f };
		bool hasCommittedThisRally{ false };

		Decision decision{ Decision::None };
	};
}