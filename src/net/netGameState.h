#pragma once

#include <cstdint>

namespace Network
{
	struct NetGameState
	{
		uint32_t frame;
		float ballX, ballY;
		float ballSpeedX, ballSpeedY;
		float p1Y, p2Y;
		int   p1Score, p2Score;
	};
}