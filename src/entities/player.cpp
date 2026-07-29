#include "Player.h"
#include "board.h"

namespace Entities
{
	void Player::move(float dy, float dt,const Core::Board& board)
	{
		switch (_effect)
		{
		case PlayerEffect::PLAYER_SPEED:
			this->_center += Util::Vec2{ 0.0f,dy } * (_speed * Util::Vec2{0.0f,2.0f}) * dt; // *2 multiplicator
			checkColisions(board);
			break;
		case PlayerEffect::PLAYER_SLOWNESS:
			this->_center += Util::Vec2{ 0.0f,dy } * (_speed * Util::Vec2{ 0.0f,0.5f }) * dt; // * 1/2 multiplicator
			checkColisions(board);
			break;
		default:
			this->_center += Util::Vec2{ 0.0f,dy } * _speed * dt;
			checkColisions(board);
			break;
		}
	}

	bool Player::isInside(const Util::Vec2& p) const
	{
		return p.x >= _center.x - _radiusX &&
			   p.x <= _center.x + _radiusX &&
			   p.y >= _center.y - _radiusY &&
			   p.y <= _center.y + _radiusY;
	}

	void Player::addPoint(int n)
	{
		_score += n;
	}

	void Player::draw(SDL_Renderer* renderer) const
	{
		SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
		SDL_Rect rect = { (int)(_center.x) - (int)_radiusX,(int)_center.y - (int)_radiusY,(int)_length,(int)_height };
		SDL_RenderFillRect(renderer, &rect);
	}

	void Player::checkColisions(const Core::Board& board)
	{
		if (_center.y + _radiusY >= board.height) _center = { _center.x, board.height - _radiusY };
		if (_center.y - _radiusY <= board.offsetY) _center = { _center.x,board.offsetY + _radiusY};
	}

	void Player::AcquireItem(Item i)
	{
#ifdef _DEBUG
		printf("new Item collected");
#endif // DEBUG
		if (!_currentItem) _currentItem = &i;
	}
}
