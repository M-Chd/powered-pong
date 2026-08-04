#pragma once

#include "netCommon.h"

namespace Network
{
	class GameClient : public pong::net::client_interface<MessageType>
	{
	public:
		void processIncoming();

		bool pollMatchStart(int& slotOut);
		bool pollGameState(NetGameState& out);
		bool pollMatchEnded();
		Network::ConnectionState getConnectionState();
	private:
		ConnectionState connState = ConnectionState::NotConnected;
		std::optional<int> assignedSlot;
		std::optional<NetGameState> latestState;
		bool matchEndedFlag = false;
	};
}