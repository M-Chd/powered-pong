#include "Player.h"

namespace Entities
{
	Item PlayerStick::useItem(Ball* b)
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

	}
}
