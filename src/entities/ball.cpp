#include "ball.h"

void Entities::Ball::move(float dx, float dy, float dt)
{
	switch (_effect)
	{
	case Item::NONE:
		this->_center.x += dx;
		this->_center.y += dy;
		break;
	case Item::EXPLOSIVE_BALL:
		break;
	case Item::SPEED_BALL:
		break;
	case Item::TELEPORT_BALL:
		break;
	default:
		break;
	}
}
