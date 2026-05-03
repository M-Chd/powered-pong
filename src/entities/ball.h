#pragma once
#include "entities/item.h"
#include <iostream>
#include "util/Vector2.h"

namespace Entities {

	class Ball
	{
	public:

		Ball(Util::Vec2 center, float radius, Util::Vec2 speed, Item effect) :
			_center(center), _radius(radius), _speed(speed), _effect(effect)
		{
			if (radius <= 0)
			{
				throw std::runtime_error("Ball's size cannot be negative or equals to 0...");
			}
			this->_size = radius * 2;
		};

		void move(float dx,float dy,float dt);

		void setEffect(Item effect) { this->_effect = effect; }
		void setSpeed(Util::Vec2 newSpeed) { this->_speed = newSpeed; }
		void setPosition(Util::Vec2 newPos) { this->_center = newPos; }
		void setRadius(float newRadius)
		{
			if (newRadius > 0)
			{
				this->_radius = newRadius;
				this->_size = 2 * _radius;
			}
		}

		Util::Vec2 getCenter() const { return _center; }
		float getSize() const { return _size; }
		Util::Vec2 getSpeed() const { return _speed; }
		Item getBallEffect() const { return _effect; }
		float getRadius() const { return _radius; }

	private:

		Util::Vec2 _center = {};
		float _radius = 0.0f;
		float _size = 0.0f;
		Util::Vec2 _speed = { 1.0f,1.0f };
		Item _effect = Item::NONE;
	};
}