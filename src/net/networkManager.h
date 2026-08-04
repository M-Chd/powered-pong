#pragma once

#include "netCommon.h"

namespace Network
{
	class NetworkManager
	{
	public:
		void startHost(uint16_t port);
		void connectLocalClient();
		void joinServer(const std::string& ip, uint16_t port);
		void teardown();
		void processMessages();

		uint16_t getActivePort() const { return activePort; }

		void sendInput(const Core::PlayerInputState&);
		bool pollGameState(NetGameState&);
		bool pollMatchStart(int&);
		bool pollMatchEnded();
		ConnectionState getConnectionState() const;

		Core::PlayerInputState getRemoteInput(int slot);
		void broadcastGameState(const NetGameState&);

	private:
		std::unique_ptr<GameServer> server;
		std::unique_ptr<GameClient> client;
		uint16_t activePort = PONG_PORT;
	};
}