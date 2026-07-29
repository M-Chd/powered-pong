#pragma once
#include <SDL2/SDL.h>
#include "vector2.hpp"
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
		EXPLOSIVE_BALL
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

		Item(ItemType type,float duration, Util::Vec2 pos) : _type(type), _duration(duration), _position(pos)
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
				break;
			default:
				_color = WHITE;
				break;
			}
		}

		ItemType getType() const { return _type; }
		float getDuration() const { return _duration; }
		Util::Vec2 getPosition() const { return _position; }
		void setPosition(Util::Vec2 pos) { _position = pos; }

	private:
		ItemType _type;
		SDL_Color _color = {};
		Util::Vec2 _position{};
		float _radiusEffectSize{ 1.0f };
		float _duration{}; // in second
	};
}