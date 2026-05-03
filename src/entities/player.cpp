#include "Player.h"

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

	void PlayerStick::move(float dy, float dt)
	{
		switch (_effect)
		{
		case Entities::PLAYER_SPEED:
			this->_center = (this->_center + Util::Vec2{ 0.0f,dy }) * (_speed * Util::Vec2{0.0f,2.0f}); // *2 multiplicator
			break;
		case Entities::PLAYER_SLOWNESS:
			this->_center = (this->_center + Util::Vec2{ 0.0f,dy }) * (_speed * Util::Vec2{ 0.0f,0.5f }); // * 1/2 multiplicator
			break;
		default:
			this->_center = (this->_center + Util::Vec2{ 0.0f,dy }) * _speed;
			break;
		}
	}
}
