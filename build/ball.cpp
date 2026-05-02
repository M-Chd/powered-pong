#include "ball.h"

void Entities::Ball::move(float dx, float dy, float dt)
{
	switch (_effect)
	{
	case NORMAL:
		this->_center.x += dx;
		this->_center.y += dy;
		break;
	case SPEED_BOOST:
		break;
	case POWER_SHOT:
		break;
	case TELEPORT:
		break;
	default:
		break;
	}
}
