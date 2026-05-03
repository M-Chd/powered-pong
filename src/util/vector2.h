#pragma once

namespace Util
{
	struct Vec2
	{
		float x, y = 0;

		Vec2 operator+(const Vec2& other)
		{
			return { this->x + other.x,this->y + other.y };
		}

		Vec2 operator*(const Vec2& other)
		{
			return { this->x * other.x, this->y * other.y };
		}

		Vec2 operator-(const Vec2& other)
		{
			return { this->x - other.x, this->y - other.y };
		}

		Vec2 operator=(const Vec2& other)
		{
			return { this->x = other.x, this->y = other.y };
		}
	};

}