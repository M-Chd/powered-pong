#include "match.h"

#include <random>

using namespace Entities;
using namespace System;

namespace Core
{
	Match::Match(MatchSettings settings)
	{
		ball.setPosition(BALL_INITIAL_POS);
		playerOne.setCenter(PlayerOneDefaultPos);
		playerTwo.setCenter(PlayerTwoDefaultPos);

		playerOne.setScore(0);
		playerTwo.setScore(0);

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

	MatchEvent Match::update(float dt, const PlayerInputState& p1Input, const PlayerInputState& p2Input)
	{
		if (p1Input.moveUp)
			playerOne.move(-1.0f, dt, board);
		else if (p1Input.moveDown)
			playerOne.move(1.0f, dt, board);

		if (playerTwo.getType() == PlayerType::HUMAN)
		{
			if (p2Input.moveUp)
				playerTwo.move(-1.0f, dt, board);
			else if (p2Input.moveDown)
				playerTwo.move(1.0f, dt, board);

		}
		else if (playerTwo.getType() == PlayerType::BOT)
		{
			updateAI(dt);
		}

		rules.reduceItemSpawnTimer(dt);

		if (items.empty())
		{
			if (rules.getItemSpawnTimer() <= 0.f)
			{
				itemSpawn();
				rules.resetItemSpwnTimer();
			}
		}

		updateItems(dt);

		ball.move(dt, *this);
		checkItemCollisions();

		return checkPoint();
	}

	void Match::checkItemCollisions()
	{
		for (auto it = items.begin(); it != items.end();)
		{
			if (!it->isInside(ball.getCenter()))
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
		playerOne.setEffect(PlayerEffect::NONE);
		playerTwo.setEffect(PlayerEffect::NONE);

		ball.resetLastHit();
		playerOne.setCenter(PlayerOneDefaultPos);
		playerTwo.setCenter(PlayerTwoDefaultPos);
		
		if (ball.getBallEffect() == Entities::BallEffect::MULTIPLICATOR)
			p.addPoint(2);
		else
			p.addPoint();

		ball.setEffect(BallEffect::NONE);
		ball.setSpeed(ballSpeed);

		rules.resetItemSpwnTimer();
		items.clear();
		activeEffects.clear();
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
			for (auto it = activeEffects.begin(); it != activeEffects.end();)
			{
				it->update(dt);

				if (it->isEffectFinished())
				{
					it = activeEffects.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}

	void Match::itemSpawn()
	{
		if (!rules.isPowerUpsAllowed())
        return;

		if (items.size() >= rules.getMaxItemCount())
			return;

		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<size_t> spawnDist(0, ITEM_SPAWNS.size() - 1);
		std::uniform_int_distribution<size_t> typeDist(0, ITEM_DURATIONS.size() - 1);

		size_t typeIndex = typeDist(gen);

		ItemType type = static_cast<ItemType>(typeIndex);

		items.emplace_back(
			type,
			ITEM_DURATIONS[typeIndex],
			ITEM_SPAWNS[spawnDist(gen)]
		);
	}

	void Match::render(SDL_Renderer* r)
	{
		board.drawBoard(r);
		ball.draw(r);

		for (auto& i : items)
			i.draw(r);

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
		if (!items.empty() && index < items.size() && index >= 0)
		{
			return &items[index];
		}
		return nullptr;
	}

}