#pragma once
#include "entities/item.h"
#include <iostream>
#include "util/Vector2.hpp"
#include <SDL2/SDL.h>

namespace Core { struct Board; }

constexpr double MAX_BOUNCE_ANGLE{ 30.f * M_PI / 180.f };
constexpr Util::Vec2 BALL_INITIAL_POS{ 640,360 };
constexpr Util::Vec2 DEFAULT_BALL_SPEED{ 630.0f,0.0f };
constexpr Util::Vec2 DEFAULT_BALL_SPEED_MINUS{ -630.0f,0.0f };

namespace Entities {

	class Ball
	{
	public:

		void move(float dt,const Core::Board& board);
		void draw(SDL_Renderer* renderer);
		void checkColisions(const Core::Board& board, float bounce);
		bool isInside(const Util::Vec2& p) const;

	public:

		Ball() :
			_center(Util::Vec2{ 640, 360}),
			_radius(4.5f),
			_speed(Util::Vec2{ 0.0f, 0.0f }),
			_effect(BallEffect::NONE)
		{
			_size = _radius * 2;
		}

		void setEffect(BallEffect effect) { this->_effect = effect; }
		void setColor(SDL_Color c) { this->_color = c; }
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
		BallEffect getBallEffect() const { return _effect; }
		float getRadius() const { return _radius; }
		SDL_Color getColor() const { return _color; }

	private:

		void checkPlayerCollisions(const Core::Board& b, float bounce);

	private:

		Util::Vec2 _center = {};
		float _radius{ 0.0f };
		float _size{ 0.0f };
		Util::Vec2 _speed = { 1.0f,1.0f };
		BallEffect _effect = BallEffect::NONE;
		SDL_Color _color = WHITE;
	};
}