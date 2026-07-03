#pragma once

#include <string>

namespace Util
{
	static std::string fmt(float v)
	{
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", v);
		return buf;
	}
}