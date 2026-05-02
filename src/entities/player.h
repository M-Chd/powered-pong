#pragma once
#include "item.h"
#include "ball.h"
#include <vector>
#include <iostream>
	
namespace Entities
{

	enum PlayerType
	{
		HUMAN,BOT
	};

	class PlayerStick
	{
	public:

		PlayerStick(Util::Vector2 center, float length, float height, float speed, PlayerType type) :
			_center(center), _length(length), _height(height), _speed(speed), _type(type)
		{
			if (length <= 0 || height <= 0)
			{
				throw std::runtime_error("Lenght or height cannot be negative or equals to 0...");
			}
			itemList.reserve(3);
			_radiusX = length / 2;
			_radiusY = height / 2;
		}

		void useItem(Ball* ball);
		void move(float dy,float dt);

	private:

		Util::Vector2 _center = {};
		std::vector<Item> itemList = {};
		const int itemlistSize = 3;

		float _length = 0.0f;
		float _radiusX = 0.0f;
		float _radiusY = 0.0f;
		float _height = 0.0f;
		float _speed = 0.0f;
		int _score = 0;
		PlayerType _type = HUMAN;

	public:
		void setLength(float newL)
		{
			if (newL > 0)
			{
				this->_length = newL;
				this->_radiusX = _length / 2;
			}
		}
		void setHeight(float newH)
		{
			if (newH > 0)
			{
				this->_height = newH;
				this->_radiusY = _height / 2;
			}
		}
		void setSpeed(float newS) { this->_speed = newS; }

		float getLength() const { return _length; }
		float getHeight() const { return _height; }
		float getRadiusX() const { return _radiusX; }
		float getRadiusY() const { return _radiusY; }
		float getSpeed() const { return _speed; }
		int getScore() const { return _score; }

		Util::Vector2 getCenter() const { return _center; }
		std::vector<Item> getItems() const { if (!itemList.empty()) return itemList; }
	};
}

