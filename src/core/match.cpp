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

		items.reserve(4);

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
		checkItemCollisions();

		return checkPoint();
	}

	void Match::checkItemCollisions()
	{
		for (auto it = items.begin(); it != items.end();)
		{
			if (!ball.isInside(it->getPosition()))
			{
				++it;
				continue;
			}

			ActiveEffect* effect = nullptr;

			switch (it->getType())
			{
			case ItemType::SPEED:
			case ItemType::TELEPORT:
			case ItemType::EXPLOSIVE:
			case ItemType::MULTIPLICATOR:
			{
				activeEffects.emplace_back(
					it->getType(),
					it->getDuration(),
					&ball);

				effect = &activeEffects.back();
				break;
			}
			case ItemType::PLAYER_SPEED:
			case ItemType::POWER:
			{
				Player* target =
					(ball.getLastHit() == LastHit::PlayerOne)
					? &playerOne
					: &playerTwo;

				activeEffects.emplace_back(
					it->getType(),
					it->getDuration(),
					target);

				effect = &activeEffects.back();
				break;
			}
			case ItemType::SLOWNESS:
			{
				Player* target =
					(ball.getLastHit() == LastHit::PlayerOne)
					? &playerTwo
					: &playerOne;

				activeEffects.emplace_back(
					it->getType(),
					it->getDuration(),
					target);

				effect = &activeEffects.back();
				break;
			}

			default:
				break;
			}

			if (effect)
				effect->apply();

			it = items.erase(it);
		}
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
		ball.resetLastHit();
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

	void Match::updateItems(float dt)
	{
		if (!activeEffects.empty())
		{
			for (auto it = activeEffects.begin(); it != activeEffects.end(); it++)
			{
				it->update(dt);

				if (it->isEffectFinished())
				{
					activeEffects.erase(it);
				}
			}
		}
	}

	void Match::itemSpawn()
	{

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