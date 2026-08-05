#pragma once

#include <cstdint>

namespace Network
{
	struct NetGameState
	{
		float ballX, ballY;
		float ballSpeedX, ballSpeedY;
		float p1Y, p2Y;
		unsigned int   p1Score, p2Score;
	};
}