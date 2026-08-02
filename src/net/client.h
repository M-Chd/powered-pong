#pragma once
#include "net_socket.h"

namespace Network
{
	class Client
	{
	public:

		void connect(const std::string& ip, unsigned int port);
		void send();
		void recieve();

		NetworkState getCurrentState() const { return currentState; }

	private:
		NetworkState currentState;
	};
}