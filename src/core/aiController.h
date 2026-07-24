#pragma once

#include <random>

#include "difficulty.h"
#include "ball.h"
#include "player.h"

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
		GameDifficulty difficulty{ GameDifficulty::NONE };
		float reactionTimer{ 0.0f };
		float reactionDelay{ 0.0f };
		float predictionErrorRange{ 0.0f };
		float currentError{ 0.0f };
		float predictedY{ 0.0f };
		float targetY{ 0.0f };
		float deadZone{ 6.0f };
		bool hasCommittedThisRally{ false };

		std::mt19937 randomGenerator{ std::random_device{}() };
		std::uniform_real_distribution<float> errorDist{ -1.0f, 1.0f };

		Decision decision{ Decision::None };
	};
}