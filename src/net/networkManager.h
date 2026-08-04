#pragma once

#include "netCommon.h"

namespace Network
{
	
	class NetworkManager
	{
	public:
		void connect();
		void disconnect();
		void update();
		void sendPlayerInput();
		void processMessages();
	private:
		pong::net::client_interface<MessageType> client;
		pong::net::server_interface<MessageType> server;

	};
}