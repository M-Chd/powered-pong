#include "ball.h"

void Entities::Ball::move(float dx, float dy, float dt)
{
	switch (_effect)
	{
	case Item::EXPLOSIVE_BALL:
		break;
	case Item::SPEED_BALL:
		break;
	case Item::TELEPORT_BALL:
		break;
	default:
		this->_center = (this->_center + Util::Vec2{ dx, dy }) * _speed;
		break;
	}
}
