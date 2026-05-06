#include "Player.h"
#include "board.h"

namespace Entities
{
	void PlayerStick::useItem(Ball* b)
	{
		if (b)
		{
			if (!itemList.empty())
			{
				auto item = itemList.front();
				itemList.erase(itemList.begin());
				b->setEffect(item);
			}
			else
			{
				std::cerr << "The item inventory is empty..." << "\n";
			}
		}
	}

	void PlayerStick::move(float dy, float dt,const Core::Board& board)
	{
		switch (_effect)
		{
		case Entities::PLAYER_SPEED:
			this->_center += Util::Vec2{ 0.0f,dy } * (_speed * Util::Vec2{0.0f,2.0f}) * dt; // *2 multiplicator
			checkColisions(board);
			break;
		case Entities::PLAYER_SLOWNESS:
			this->_center += Util::Vec2{ 0.0f,dy } * (_speed * Util::Vec2{ 0.0f,0.5f }) * dt; // * 1/2 multiplicator
			checkColisions(board);
			break;
		default:
			this->_center += Util::Vec2{ 0.0f,dy } * _speed * dt;
			checkColisions(board);
			break;
		}
	}

	void PlayerStick::draw(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = { _center.x - _radiusX,_center.y - _radiusY,_length,_height };
		SDL_RenderFillRect(renderer, &rect);
	}

	void PlayerStick::checkColisions(const Core::Board& board)
	{
		if (_center.y + _radiusY >= board.height) _center = { _center.x, board.height - _radiusY };
		if (_center.y - _radiusY <= board.offsetY) _center = { _center.x,board.offsetY + _radiusY};
	}
}
