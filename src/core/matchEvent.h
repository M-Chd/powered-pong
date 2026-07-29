#pragma once

namespace Core
{
	enum class MatchEvent
	{
		None,
		PointScored,
		MatchFinished
	};

	enum class LastHit
	{
		None,
		PlayerOne,
		PlayerTwo
	};
}