#include "item.h"
#include "ball.h"

namespace Entities
{
	void Item::setOnBallEffect(BallEffect be, Ball* b)
	{
		if (b)
		{
			b->setEffect(be);
			
			switch (b->getBallEffect())
			{
			case BallEffect::SPEED_BALL:
				b->setColor(CYAN);
				break;
			case BallEffect::TELEPORT_BALL:
				b->setColor(PURPLE);
				break;
			case BallEffect::MULTIPLICATOR:
				b->setColor(RED);
				break;
			default:
				b->setColor(WHITE);
				break;
			}
		}
	}
}