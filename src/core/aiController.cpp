#include "aiController.h"
#include "board.h"

namespace Core
{
	void AIController::setDifficulty(GameDifficulty diff)
	{
		difficulty = diff;

		switch (difficulty)
		{
		case GameDifficulty::EASY:
			reactionDelay = 0.45f;
			predictionErrorRange = 45.0f;
			break;
		case GameDifficulty::MEDIUM:
			reactionDelay = 0.22f;
			predictionErrorRange = 20.0f;
			break;
		case GameDifficulty::HARD:
			reactionDelay = 0.06f;
			predictionErrorRange = 6.0f;
			break;
		default:
			reactionDelay = 0.25f;
			predictionErrorRange = 25.0f;
			break;
		}

		reset();
	}

	void AIController::reset()
	{
		reactionTimer = reactionDelay;
		currentError = 0.0f;
		decision = Decision::None;
	}

	void AIController::update(float dt, Entities::Ball& ball, Entities::Player& player, Board& board)
	{
		reactionTimer -= dt;

		if (reactionTimer <= 0.0f)
		{
			reactionTimer = reactionDelay;

			chooseTarget(ball, player);
			predictBallPosition(ball);
			makeDecision(player);
		}
	}

	void AIController::chooseTarget(Entities::Ball& ball, Entities::Player& player)
	{
		 bool ballComingTowardsUs = ball.getSpeed().x > 0.0f;

		if (ballComingTowardsUs)
		{
			if (!hasCommittedThisRally)
			{
				computeError();
				hasCommittedThisRally = true;
			}
			targetY = ball.getCenter().y;
		}
		else
		{
			targetY = player.getCenter().y;
			hasCommittedThisRally = false;
		}
	}

	void AIController::predictBallPosition(Entities::Ball& ball)
	{
		predictedY = targetY + ball.getSpeed().y * reactionDelay;
	}

	void AIController::computeError()
	{
		currentError = errorDist(randomGenerator) * predictionErrorRange;
	}

	void AIController::makeDecision(Entities::Player& player)
	{
		float aimY = predictedY + currentError;
		float diff = aimY - player.getCenter().y;

		if (diff > deadZone)
			decision = Decision::MoveDown;
		else if (diff < -deadZone)
			decision = Decision::MoveUp;
		else
			decision = Decision::None;
	}
}