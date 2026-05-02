#pragma once
#include "item.h"
#include <iostream>
#include "vector2.h"

namespace Entities {

	class Ball
	{
	public:

		Ball(Util::Vector2 center, float radius, float size, float speed, Item effect) :
			_center(center), _radius(radius), _size(size), _speed(speed), _effect(effect)
		{
			if (size <= 0)
			{
				std::runtime_error("Ball's size cannot be negative or equals to 0...");
			}
			if (radius <= 0)
			{
				std::runtime_error("Ball's radius cannot be negative equals to 0...");
			}
		};

		void move(float dx,float dy,float dt);

		void setEffect(Item effect) { this->_effect = effect; }
		void setSize(float newSize) 
		{
			if (newSize > 0)
			{
				this->_size = newSize;
			}
		}
		void setSpeed(float newSpeed) { this->_speed = newSpeed; }
		void setPosition(Util::Vector2 newPos) { this->_center = newPos; }
		void setRadius(float newRadius)
		{
			if (newRadius > 0)
			{
				this->_radius = newRadius;
			}
		}

		Util::Vector2 getCenter() const { return _center; }
		float getSize() const { return _size; }
		float getSpeed() const { return _speed; }
		Item getBallEffect() const { return _effect; }
		float getRadius() const { return _radius; }

	private:

		Util::Vector2 _center = {};
		float _radius = 0.0f;
		float _size = 0.0f;
		float _speed = 0.0f;
		Item _effect = Item::NONE;
	};
}