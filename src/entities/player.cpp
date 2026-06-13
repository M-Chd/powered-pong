#include "Player.h"
#include "board.h"

namespace Entities
{
	void Player::useItem(Ball* b)
	{
		if (b)
		{
			if (_currentItem)
			{
				switch (_currentItem->getType())
				{
				case ItemType::PLAYER_SPEED:
					_effect = PlayerEffect::PLAYER_SPEED;
					break;
				case ItemType::SLOWNESS:
					_effect = PlayerEffect::PLAYER_SLOWNESS;
					break;
				case ItemType::POWER:
					_effect = PlayerEffect::PLAYER_POWER;
					break;
				case ItemType::SPEED:
					_currentItem->setOnBallEffect(BallEffect::SPEED_BALL, b);
					break;
				case ItemType::TELEPORT:
					_currentItem->setOnBallEffect(BallEffect::TELEPORT_BALL, b);
					break;
				case ItemType::EXPLOSIVE:
					_currentItem->setOnBallEffect(BallEffect::EXPLOSIVE_BALL, b);
					break;
				default:
					_effect = PlayerEffect::NONE;
					b->setEffect(BallEffect::NONE);
					break;
				}
			}
			else
			{
				std::cerr << "Player haves no Item..." << "\n";
			}
		}
	}

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

	void Player::draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = { _center.x - _radiusX,_center.y - _radiusY,_length,_height };
		SDL_RenderFillRect(renderer, &rect);
	}

	void Player::checkColisions(const Core::Board& board)
	{
		if (_center.y + _radiusY >= board.height) _center = { _center.x, board.height - _radiusY };
		if (_center.y - _radiusY <= board.offsetY) _center = { _center.x,board.offsetY + _radiusY};
	}

	void Player::AcquireItem(Item i)
	{
#ifdef DEBUG
		printf("new Item collected");
#endif // DEBUG
		if (!_currentItem) _currentItem = &i;
	}
}
