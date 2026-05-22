#pragma once
#include "item.h"
#include "ball.h"
#include <vector>
#include <iostream>

namespace Core { struct Board; }
	
namespace Entities
{

	enum PlayerType
	{
		HUMAN,BOT
	};

	class Player
	{
	public:

		void useItem(Ball* ball);
		void move(float dy,float dt,const Core::Board& board);
		void draw(SDL_Renderer* renderer);
		void checkColisions(const Core::Board& board);

	public:

		Player() : 
			_center(Util::Vec2{210,360}),
			_length(10.0f),
			_height(100.0f),
			_speed(Util::Vec2{ 0.0f,25000.0f }),
			_type(PlayerType::HUMAN)
		{
			_radiusX = _length / 2;
			_radiusY = _height / 2;
		}

	private:

		Util::Vec2 _center = {};
		Item* _currentItem = nullptr;

		float _length = 0.0f;
		float _radiusX = 0.0f;
		float _radiusY = 0.0f;
		float _height = 0.0f;
		float _power = 1.0f;
		PlayerEffect _effect = PlayerEffect::NONE;
		Util::Vec2 _speed = { 0.0f,1.0f };
		unsigned int _score = 0;
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
		void setPower(float newP)
		{
			if (newP > 0)
			{
				this->_power = newP;
			}
		}
		void setSpeed(Util::Vec2 newS) { this->_speed = newS; }
		void setEffect(PlayerEffect e) { this->_effect = e; }
		

		float getLength() const { return _length; }
		float getHeight() const { return _height; }
		float getRadiusX() const { return _radiusX; }
		float getRadiusY() const { return _radiusY; }
		Util::Vec2 getSpeed() const { return _speed; }
		int getScore() const { return _score; }
		PlayerEffect getEffect() const { return _effect; }
		float getPower() const { return _power; }

		Util::Vec2 getCenter() const { return _center; }
		Item* getItem() const { if (_currentItem) return _currentItem; }
	};
}

