#pragma once

namespace Util
{
	struct Vec2
	{
		float x = 0.0f;
		float y = 0.0f;

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
	};

}