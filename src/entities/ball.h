#pragma once
#include "entities/item.h"
#include <iostream>
#include "util/vector2.h"

namespace Entities {

	class Ball
	{
	public:

		Ball(Util::Vector2 center, float radius, float speed, Item effect) :
			_center(center), _radius(radius), _speed(speed), _effect(effect)
		{
			if (radius <= 0)
			{
				throw std::runtime_error("Ball's size cannot be negative or equals to 0...");
			}
		};

		void move(float dx,float dy,float dt);

		void setEffect(Item effect) { this->_effect = effect; }
		void setSpeed(float newSpeed) { this->_speed = newSpeed; }
		void setPosition(Util::Vector2 newPos) { this->_center = newPos; }
		void setRadius(float newRadius)
		{
			if (newRadius > 0)
			{
				this->_radius = newRadius;
				this->_size = 2 * _radius;
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