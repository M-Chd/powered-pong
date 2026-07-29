#include "activeEffect.h"

namespace Entities
{
	void ActiveEffect::update(float dt)
	{
		this->remainingTime -= dt;

		if (remainingTime <= 0)
		{
			this->isFinished = true;
			reset();
		}
	}

	void ActiveEffect::apply()
	{
		if (std::holds_alternative<Ball*>(target))
		{
			Ball* ball = std::get<Ball*>(target);

			switch (effectType)
			{
			case Entities::ItemType::SPEED:
				ball->setEffect(BallEffect::SPEED_BALL);
				break;
			case Entities::ItemType::TELEPORT:
				ball->setEffect(BallEffect::TELEPORT_BALL);
				break;
			case Entities::ItemType::EXPLOSIVE:
				ball->setEffect(BallEffect::EXPLOSIVE_BALL);
				break;
			case Entities::ItemType::MULTIPLICATOR:
				ball->setEffect(BallEffect::MULTIPLICATOR);
				break;
			default:
				break;
			}
		}
		else if (std::holds_alternative<Player*>(target))
		{
			Player* player = std::get<Player*>(target);

			switch (effectType)
			{
			case Entities::ItemType::SLOWNESS:
				player->setEffect(PlayerEffect::PLAYER_SLOWNESS);
				break;
			case Entities::ItemType::POWER:
				player->setEffect(PlayerEffect::PLAYER_POWER);
				break;
			case Entities::ItemType::PLAYER_SPEED:
				player->setEffect(PlayerEffect::PLAYER_SPEED);
				break;
			default:
				break;
			}
		}
	}

	void ActiveEffect::reset()
	{
		if (std::holds_alternative<Ball*>(target))
		{
			Ball* ball = std::get<Ball*>(target);
			ball->setEffect(BallEffect::NONE);
		}
		else if (std::holds_alternative<Player*>(target))
		{
			Player* player = std::get<Player*>(target);
			player->setEffect(PlayerEffect::NONE);
		}
	}
}