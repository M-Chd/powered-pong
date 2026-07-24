#include "match.h"

using namespace Entities;
using namespace System;

namespace Core
{
	Match::Match(MatchSettings settings)
	{
		ball.setPosition(BALL_INITIAL_POS);
		playerOne.setCenter(PlayerOneDefaultPos);
		playerTwo.setCenter(PlayerTwoDefaultPos);

		ball.setSpeed(DEFAULT_BALL_SPEED);

		items.reserve(3);

		switch (settings.type)
		{
		case MatchType::Solo:

			switch (settings.difficulty)
			{
			case GameDifficulty::EASY:
				setPlayerTwoType(PlayerType::BOT);
				aiController.setDifficulty(settings.difficulty);
				break;
			case GameDifficulty::MEDIUM:
				setPlayerTwoType(PlayerType::BOT);
				aiController.setDifficulty(settings.difficulty);
				break;
			case GameDifficulty::HARD:
				setPlayerTwoType(PlayerType::BOT);
				aiController.setDifficulty(settings.difficulty);
				break;
			default:
				break;
			}
			break;
		case MatchType::Multi:
			playerTwo.setColor(GRAY);
			break;
		}
	}

	MatchEvent Match::update(float dt, System::InputManager& inputmngr)
	{
		if (inputmngr.isKeyDown(SDL_SCANCODE_Z) ||
			inputmngr.isKeyDown(SDL_SCANCODE_W))
		{
			playerOne.move(-1.0f, dt, board);
		}
		else if (inputmngr.isKeyDown(SDL_SCANCODE_S))
		{
			playerOne.move(1.0f, dt, board);
		}

		if (playerTwo.getType() == PlayerType::HUMAN)
		{
			if (inputmngr.isKeyDown(SDL_SCANCODE_UP))
				playerTwo.move(-1.0f, dt, board);
			else if (inputmngr.isKeyDown(SDL_SCANCODE_DOWN))
				playerTwo.move(1.0f, dt, board);
		}
		else if (playerTwo.getType() == PlayerType::BOT)
		{
			updateAI(dt);
		}

		ball.move(dt, *this);

		return checkPoint();
	}

	MatchEvent Match::checkPoint()
	{
		switch(board.checkBallPoint(ball, playerOne, playerTwo))
		{
        case 1:
            setupRound(playerTwo, DEFAULT_BALL_SPEED_MINUS);

            if (isFinished())
                return MatchEvent::MatchFinished;

            return MatchEvent::PointScored;

        case -1:
            setupRound(playerOne, DEFAULT_BALL_SPEED);

            if (isFinished())
                return MatchEvent::MatchFinished;

            return MatchEvent::PointScored;
		}

		return MatchEvent::None;
	}

	void Match::setupRound(Player& p, const Util::Vec2& ballSpeed)
	{
		ball.setPosition(BALL_INITIAL_POS);
		playerOne.setCenter(PlayerOneDefaultPos);
		playerTwo.setCenter(PlayerTwoDefaultPos);
		
		if (ball.getBallEffect() == Entities::BallEffect::MULTIPLICATOR)
			p.addPoint(2);
		else
			p.addPoint();

		ball.setSpeed(ballSpeed);
	}

	void Match::updateAI(float dt)
	{
		aiController.update(dt, ball, playerTwo, board);

		switch (aiController.getDecision())
		{
		case Decision::MoveUp:
			playerTwo.move(-1.0f, dt, board);
			break;
		case Decision::MoveDown:
			playerTwo.move(1.0f, dt, board);
			break;
		default:
			break;
		}
	}

	void Match::render(SDL_Renderer* r)
	{
		board.drawBoard(r);
		ball.draw(r);

		//for (auto& i : items)
			//i.draw(r);

		playerOne.draw(r);
		playerTwo.draw(r);
	}

	bool Match::isFinished()
	{
		return (playerOne.getScore() >= rules.getWinScore()) ||
			(playerTwo.getScore() >= rules.getWinScore());
	}

	Entities::Item* Core::Match::getItemAt(int index)
	{
		if (!items.empty() && index < items.size() && index > 0)
		{
			return &items[index];
		}
		return nullptr;
	}

}