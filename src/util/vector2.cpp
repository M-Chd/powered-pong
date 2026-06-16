#include "vector2.hpp"

namespace Util
{
	double distanceFrom(const Vec2& src, const Vec2& dst)
	{
		return sqrt(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
	}

	float getLength(const Vec2& vec)
	{
		return static_cast<float>(sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
	}
}