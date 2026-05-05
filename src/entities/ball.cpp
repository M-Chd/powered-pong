#include "ball.h"

void Entities::Ball::move(float dt)
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
		_center += _speed * dt;
		checkColisions();
		break;
	}
}

void Entities::Ball::checkColisions()
{
	float edgeX = _center.x + _radius;
	float edgeMinusX = _center.x - _radius;
	float edgeY = _center.y + _radius;
	float edgeMinusY = _center.y - _radius;

	float bounce = -1.0f;

	if (edgeY >= 720)
	{
		_center = { _center.x, 720 - _radius };
		_speed.y *= bounce;
	}
	if (edgeMinusY <= 0)
	{
		_center = { _center.x, _radius };
		_speed.y *= bounce;
	}
	if (edgeX >= 1280)
	{
		_center = { 1280 - _radius, _center.y };
		_speed.x *= bounce;
	}
	if (edgeMinusX <= 0)
	{
		_center = { _radius, _center.y };
		_speed.x *= bounce;
	}
}

void Entities::Ball::draw(SDL_Renderer* renderer)
{

	auto& c = _color;

	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);

	int cx = static_cast<int>(_center.x);
	int cy = static_cast<int>(_center.y);
	int r = static_cast<int>(_radius);

	for (int w = -r; w <= r; w++)
	{
		for (int h = -r; h <= r; h++)
		{
			if (w * w + h * h <= r * r)
			{
				SDL_RenderDrawPoint(renderer, cx + w, cy + h);
			}
		}
	}
}
