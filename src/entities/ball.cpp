#include "ball.h"
#include "board.h"

void Entities::Ball::move(float dt,const Core::Board& board)
{
	float bounce = -1.0f;

	switch (_effect)
	{
	case BallEffect::EXPLOSIVE_BALL:
		_center += _speed * dt;
		checkColisions(board, bounce * 2);
		break;
	case BallEffect::SPEED_BALL:
		_center += _speed * 2 * dt;
		checkColisions(board, bounce);
		break;
	case BallEffect::TELEPORT_BALL:
		break;
	default:
		_center += _speed * dt;
		checkColisions(board,bounce);
		break;
	}
}

void Entities::Ball::checkColisions(const Core::Board& board,float bounce)
{
	float edgeX = _center.x + _radius;
	float edgeMinusX = _center.x - _radius;
	float edgeY = _center.y + _radius;
	float edgeMinusY = _center.y - _radius;

	if (edgeY >= board.height)
	{
		_center = { _center.x, board.height - _radius};
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
