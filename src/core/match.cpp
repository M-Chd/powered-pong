#include "match.h"

using namespace UI;
using namespace Entities;

namespace Core
{
	Match::Match(GameAction& gameAction)
	{
		ball.setPosition(BALL_INITIAL_POS);
		playerOne.setCenter(PlayerOneDefaultPos);
		playerTwo.setCenter(PlayerTwoDefaultPos);

		ball.setSpeed(DEFAULT_BALL_SPEED);

		items.reserve(3);

		auto difficulty = actionToDifficulty(gameAction);

		switch (difficulty)
		{
		case Game::GameDifficulty::EASY:
			setPlayerTwoType(PlayerType::BOT);
			//Ai player wip
			break;
		case Game::GameDifficulty::MEDIUM:
			setPlayerTwoType(PlayerType::BOT);
			//AI player wip
			break;
		case Game::GameDifficulty::HARD:
			setPlayerTwoType(PlayerType::BOT);
			//AI player wip
			break;
		default:
			break;
		}

		if (gameAction == GameAction::StartLocalMultiplayer)
		{
			//TODO
		}
	}

	Entities::Item* Core::Match::getItemAt(int index)
	{
		if (!items.empty() && index < items.size())
		{
			return &items[index];
		}
		return nullptr;
	}

}