#pragma once

#include "netCommon.h"

namespace Network
{
	class GameClient : public pong::net::client_interface<MessageType>
	{
	public:
		void sendInput(bool up, bool down, uint32_t frame);
		bool pollGameState(NetGameState& out);
		bool pollMatchStart(int& assignedPlayerSlot);
	};
}