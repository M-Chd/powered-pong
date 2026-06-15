#include "vector2.hpp"

namespace Util
{
	double distanceFrom(const Vec2& src, const Vec2& dst)
	{
		return sqrt(pow(src.x - dst.x, 2) + pow(src.y - dst.y, 2));
	}

	double getLength(const Vec2& vec)
	{
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	}
}