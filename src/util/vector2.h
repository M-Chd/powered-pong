#pragma once

namespace Util
{
	struct Vector2
	{
		float x, y = 0;

		Vector2 operator+(const Vector2& other)
		{
			return { this->x + other.x,this->y + other.y };
		}

		Vector2 operator*(const Vector2& other)
		{
			return { this->x * other.x, this->y * other.y };
		}

		Vector2 operator-(const Vector2& other)
		{
			return { this->x - other.x, this->y - other.y };
		}
	};

}