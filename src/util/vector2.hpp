#pragma once
#include <math.h>

namespace Util
{
	struct Vec2
	{
		float x{ 0.0f };
		float y{ 0.0f };

		Vec2 operator+(const Vec2& other)
		{
			return { this->x + other.x,this->y + other.y };
		}

		Vec2 operator*(const Vec2& other)
		{
			return { this->x * other.x, this->y * other.y };
		}

		Vec2 operator*(float n)
		{
			return { this->x * n, this->y * n };
		}

		Vec2 operator-(const Vec2& other)
		{
			return { this->x - other.x, this->y - other.y };
		}

		Vec2& operator=(const Vec2& other)
		{
			this->x = other.x;
			this->y = other.y;
			
			return *this;
		}

		Vec2& operator+=(const Vec2& other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vec2& operator*=(float n)
		{
			this->x *= n;
			this->y *= n;

			return *this;
		}

		bool operator>(const Vec2& other) const
		{
			return this->x > other.x && this->y > other.y;
		}

		bool operator<(const Vec2& other) const
		{
			return this->x < other.x && this->y < other.y;
		}
	};

	double distanceFrom(const Vec2& src, const Vec2& dst);
	float getLength(const Vec2& vec);

}