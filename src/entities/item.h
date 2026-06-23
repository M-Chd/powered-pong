#pragma once
#include <SDL2/SDL.h>
//##################################################################|
#define WHITE      { 255, 255, 255, 255 } // Ball default color
#define CYAN       {   0, 255, 255, 255 } // Speed ball effect color
#define RED        { 255,   0,   0, 255 } // Multiplicator
#define DEEP_RED   { 139,   0,   0, 255 } // Explosive ball color
#define PURPLE     { 128,   0, 128, 255 } // Teleport effect color
#define ORANGE     { 255, 165,   0, 255 } // Player power color
#define BLUE       {   0, 120, 255, 255 } // Player speed color
#define GRAY       { 128, 128, 128, 255 } // Slowness player color
//##################################################################|

namespace Entities {

	class Ball;

	enum class PlayerEffect
	{
		NONE,
		PLAYER_SPEED,
		PLAYER_SLOWNESS,
		PLAYER_POWER,
	};

	enum class BallEffect
	{
		NONE,
		SPEED_BALL,
		TELEPORT_BALL,
		MULTIPLICATOR,
		EXPLOSIVE_BALL,
	};

	enum class ItemType
	{
		SPEED,
		TELEPORT,
		EXPLOSIVE,
		SLOWNESS,
		POWER,
		PLAYER_SPEED,
		MULTIPLICATOR
	};

	class Item
	{
	public:

		Item(ItemType type,unsigned int duration) : _type(type), _duration(duration)
		{
			if (duration > 15) return;

			switch (type)
			{
			case ItemType::SPEED:
				_color = CYAN;
				break;
			case ItemType::TELEPORT:
				_color = PURPLE;
				break;
			case ItemType::EXPLOSIVE:
				_color = DEEP_RED;
				break;
			case ItemType::SLOWNESS:
				_color = GRAY;
				break;
			case ItemType::POWER:
				_color = ORANGE;
				break;
			case ItemType::PLAYER_SPEED:
				_color = BLUE;
				break;
			case ItemType::MULTIPLICATOR:
				_color = RED;
			default:
				_color = WHITE;
				break;
			}
		}

		void setOnBallEffect(BallEffect be, Ball* b);
		ItemType getType() const { return _type; }

	private:
		ItemType _type;
		SDL_Color _color = {};
		unsigned int _duration{}; // in second
	};
}