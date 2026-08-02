#pragma once

#include "player.h"
#include "vector2.hpp"
#include "match.h"

namespace Network
{
	enum class NetworkState
	{
		Disconnected,
		Listening,
		Connecting,
		Connected
	};

	struct InputSocket
	{
		bool up; bool down;
	};

	struct NetSocket
	{
		float ball_x;
		float ball_y;

		float p1_x;
		float p1_y;

		int scoreP1;
		int scoreP2;
	};
}