#include "ball.h"
#include "board.h"

#include <algorithm>

namespace Entities
{
	void Ball::move(float dt, const Core::Board& board)
	{
		float bounce = -1.0f;

		switch (_effect)
		{
		case BallEffect::EXPLOSIVE_BALL:
			_center += _speed * dt;
			checkColisions(board, bounce * 1.1);
			break;
		case BallEffect::SPEED_BALL:
			_center += _speed * 1.5 * dt;
			checkColisions(board, bounce);
			break;
		case BallEffect::TELEPORT_BALL:
			break;
		default:
			_center += _speed * dt;
			checkColisions(board, bounce);
			break;
		}
	}

	void Ball::checkColisions(const Core::Board& board, float bounce)
	{
		float edgeX = _center.x + _radius;
		float edgeMinusX = _center.x - _radius;
		float edgeY = _center.y + _radius;
		float edgeMinusY = _center.y - _radius;

		checkPlayerCollisions(board, bounce);

		if (edgeY >= board.height)
		{
			_center = { _center.x, board.height - _radius };
			_speed.y *= bounce;
		}
		if (edgeMinusY <= board.offsetY)
		{
			_center = { _center.x, _radius + board.offsetY };
			_speed.y *= bounce;
		}
		if (edgeX >= board.length)
		{
			_center = { board.length - _radius, _center.y };
			_speed.x *= bounce;
		}
		if (edgeMinusX <= board.offsetX)
		{
			_center = { _radius + board.offsetX , _center.y };
			_speed.x *= bounce;
		}
	}

	void Ball::checkPlayerCollisions(const Core::Board& b, float bounce)
	{
		const auto& p1 = b.p1;
		float closestX = std::clamp(_center.x, p1.getCenter().x - p1.getRadiusX(), p1.getCenter().x + p1.getRadiusX());
		float closestY = std::clamp(_center.y, p1.getCenter().y - p1.getRadiusY(), p1.getCenter().y + p1.getRadiusY());

		float dx = _center.x - closestX;
		float dy = _center.y - closestY;

		if (dx * dx + dy * dy <= _radius * _radius && _speed.x < 0)
		{
			float relative = (_center.y - p1.getCenter().y) / p1.getRadiusY();
			relative = std::clamp(relative, -1.0f, 1.0f);
			double angle = relative * MAX_BOUNCE_ANGLE;
			float speed = Util::getLength(_speed) * std::abs(bounce);

			_speed.x = std::abs(speed * static_cast<float>(std::cos(angle)));
			_speed.y = speed * static_cast<float>(std::sin(angle));

			_center.x = p1.getCenter().x + p1.getRadiusX() + _radius;
		}

		const auto& p2 = b.p2;
		float closestX2 = std::clamp(_center.x, p2.getCenter().x - p2.getRadiusX(), p2.getCenter().x + p2.getRadiusX());
		float closestY2 = std::clamp(_center.y, p2.getCenter().y - p2.getRadiusY(), p2.getCenter().y + p2.getRadiusY());

		float dx2 = _center.x - closestX2;
		float dy2 = _center.y - closestY2;

		if (dx2 * dx2 + dy2 * dy2 <= _radius * _radius && _speed.x > 0)
		{
			float relative = (_center.y - p2.getCenter().y) / p2.getRadiusY();
			relative = std::clamp(relative, -1.0f, 1.0f);
			double angle = relative * MAX_BOUNCE_ANGLE;
			float speed = Util::getLength(_speed) * std::abs(bounce);

			_speed.x = -std::abs(speed * static_cast<float>(std::cos(angle)));
			_speed.y = speed * static_cast<float>(std::sin(angle));

			_center.x = p2.getCenter().x - p2.getRadiusX() - _radius;
		}
	}

	bool Ball::isInside(const Util::Vec2& p) const
	{
		return Util::distanceFrom(p,_center) <= _radius;
	}

	void Ball::draw(SDL_Renderer* renderer)
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
}
